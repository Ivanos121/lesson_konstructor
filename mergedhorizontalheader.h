#ifndef MERGEDHORIZONTALHEADER_H
#define MERGEDHORIZONTALHEADER_H

// MergedHeader.h
#pragma once

#include <QHeaderView>

class MergedHorizontalHeader : public QHeaderView
{
    Q_OBJECT
public:
    explicit MergedHorizontalHeader(Qt::Orientation orientation, QWidget *parent = nullptr)
        : QHeaderView(orientation, parent) {}

protected:
    void paintSection(QPainter *painter, const QRect &rect, int logicalIndex) const override;
    void paintEvent(QPaintEvent *event) override;

private:
    // Возвращает индекс верхней (начальной) секции для объединения,
    // либо -1 если секция не входит в объединение.
    // В этом примере объединяем пары (0+1, 2+3, ...).
    int mergedStartFor(int logicalIndex) const {
        if (logicalIndex < 0) return -1;
        int start = (logicalIndex / 2) * 2; // верхняя секция пары
        // Проверим, что logicalIndex действительно в пределах пары start..start+1
        if (logicalIndex == start || logicalIndex == start + 1) return start;
        return -1;
    }
};

#endif // MERGEDHORIZONTALHEADER_H
