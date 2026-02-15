#include "mergedheader.h"
#include "qevent.h"

MergedHeader::MergedHeader(Qt::Orientation orient, QWidget *parent) : QHeaderView(orient, parent)
{
    setSectionsClickable(false);
    connect(this, &QHeaderView::sectionResized, this, [this](int, int, int){ viewport()->update(); });
    connect(this, &QHeaderView::sectionMoved, this, [this](int, int, int){ viewport()->update(); });
}

int MergedHeader::mergedStartFor(int logicalIndex) const
{
    if (orientation() != Qt::Horizontal) return -1;
    return (logicalIndex >= 1 && (logicalIndex % 2 == 1)) ? logicalIndex : -1;
}

void MergedHeader::paintSection(QPainter *painter, const QRect &rect, int logicalIndex) const
{
    // предотвращаем стандартную отрисовку правой части пары (2,4,6...)
    if (orientation() == Qt::Horizontal && logicalIndex >= 2 && (logicalIndex % 2 == 0)) {
        return;
    }

    int start = mergedStartFor(logicalIndex);
    if (start >= 0) {
        // ширина пары
        int width = sectionSize(start);
        if (start + 1 < QHeaderView::count()) width += sectionSize(start + 1);
        int x = sectionPosition(start);
        QRect mergedRect(x, rect.y(), width, rect.height());

        // видимая часть mergedRect в пределах header
        QRect visible = mergedRect.intersected(this->rect());
        if (visible.isEmpty()) return;

        // Рисуем только фон и текст (без рамок)
        painter->save();
        painter->setClipRect(visible);
        painter->fillRect(mergedRect, palette().button());

        QString text;
        if (model()) text = model()->headerData(start, Qt::Horizontal).toString();

        painter->setPen(palette().color(QPalette::ButtonText));
        painter->drawText(mergedRect, Qt::AlignCenter, text);
        painter->restore();
        return;
    }

    // Обычная отрисовка для остальных секций (например, колонка 0)
    QHeaderView::paintSection(painter, rect, logicalIndex);
}

void MergedHeader::paintEvent(QPaintEvent *event)
{
    // стандартная отрисовка (вызовет paintSection для видимых секций)
    QHeaderView::paintEvent(event);

    // Затем дорисуем только внешние рамки объединённых областей ровно один раз
    QPainter painter(viewport());
    painter.setRenderHint(QPainter::Antialiasing, false);
    painter.setPen(QPen(palette().color(QPalette::Mid), 1));

    const int cols = QHeaderView::count();
    for (int start = 1; start < cols; start += 2) {
        int left = sectionPosition(start);
        int w = sectionSize(start);
        if (start + 1 < cols) w += sectionSize(start + 1);
        QRect mergedRect(left, 0, w, height());

        // пересечение с областью repaint
        QRect r = mergedRect.intersected(event->rect());
        if (r.isEmpty()) continue;

        // верхняя и нижняя границы (в пределах r)
        painter.drawLine(r.left(), r.top(), r.right()-1, r.top());
        painter.drawLine(r.left(), r.bottom()-1, r.right()-1, r.bottom()-1);

        // левая внешняя граница (если видима в r)
        int leftX = mergedRect.left();
        if (r.left() <= leftX && r.right() > leftX) {
            painter.drawLine(leftX, r.top(), leftX, r.bottom()-1);
        }

        // правая внешняя граница (если видима в r)
        int rightX = mergedRect.right() - 1;
        if (r.right() >= rightX && r.left() <= rightX) {
            painter.drawLine(rightX, r.top(), rightX, r.bottom()-1);
        }

        // Важно: НЕ рисуем внутреннюю границу между start и start+1 — её
        // либо не рисует paintSection для правой секции (мы вернули в начале),
        // либо она уже нарисована стандартным кодом; поэтому здесь её опускаем.
    }
}
