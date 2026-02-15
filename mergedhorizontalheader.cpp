// MergedHeader.cpp
#include "mergedhorizontalheader.h"
#include <QPainter>
#include <QPaintEvent>
#include <QDebug>
#include <QStyleOptionHeader>
#include <QAbstractItemModel>

void MergedHorizontalHeader::paintSection(QPainter *painter, const QRect &rect, int logicalIndex) const
{
    // Только для вертикального заголовка
    if (orientation() == Qt::Vertical) {
        int start = mergedStartFor(logicalIndex);
        if (start >= 0) {
            // высота объединённой пары
            int h = sectionSize(start);
            if (start + 1 < QHeaderView::count()) h += sectionSize(start + 1);
            int y = sectionPosition(start);
            QRect mergedRect(rect.x(), y, rect.width(), h);

            QRect visible = mergedRect.intersected(this->rect());
            if (visible.isEmpty()) return;

            // Рисуем фон и текст (без рамок)
            painter->save();
            painter->setClipRect(visible);
            painter->fillRect(mergedRect, palette().button());

            QString text;
            if (model()) text = model()->headerData(start, Qt::Vertical).toString();

            // Отступы и элизация (чтобы текст не обрезался жёстко)
            QRect textRect = mergedRect.adjusted(2, 2, -2, -2);
            QFontMetrics fm(painter->font());
            QString elided = fm.elidedText(text, Qt::ElideRight, textRect.width());

            painter->setPen(palette().color(QPalette::ButtonText));
            painter->drawText(textRect, Qt::AlignCenter, elided);
            painter->restore();
            return; // предотвращаем стандартную отрисовку обеих секций пары
        }
    }

    QHeaderView::paintSection(painter, rect, logicalIndex);
}

void MergedHorizontalHeader::paintEvent(QPaintEvent *event)
{
    QHeaderView::paintEvent(event);

    QPainter painter(viewport());
    painter.setRenderHint(QPainter::Antialiasing, false);
    painter.setPen(QPen(palette().color(QPalette::Mid), 1));

    const int rows = QHeaderView::count();
    // Проходим по парам строк: 0,2,4,...
    for (int start = 0; start < rows; start += 2) {
        int top = sectionPosition(start);
        int h = sectionSize(start);
        if (start + 1 < rows) h += sectionSize(start + 1);
        QRect mergedRect(0, top, width(), h);

        QRect r = mergedRect.intersected(event->rect());
        if (r.isEmpty()) continue;

        // левая и правая границы (вертикальные линии) в пределах r
        painter.drawLine(r.left(), r.top(), r.left(), r.bottom() - 1);
        painter.drawLine(r.right() - 1, r.top(), r.right() - 1, r.bottom() - 1);

        // верхняя внешняя граница (если видима)
        int topY = mergedRect.top();
        if (r.top() <= topY && r.bottom() > topY) {
            painter.drawLine(r.left(), topY, r.right() - 1, topY);
        }

        // нижняя внешняя граница (если видима)
        int bottomY = mergedRect.bottom() - 1;
        if (r.bottom() >= bottomY && r.top() <= bottomY) {
            painter.drawLine(r.left(), bottomY, r.right() - 1, bottomY);
        }

        // НЕ рисуем внутреннюю горизонтальную линию между start и start+1
    }
}
