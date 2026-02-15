#ifndef MERGEDHEADER_H
#define MERGEDHEADER_H

#include <QApplication>
#include <QTableWidget>
#include <QHeaderView>
#include <QPainter>

class MergedHeader : public QHeaderView {
    Q_OBJECT
public:
    explicit MergedHeader(Qt::Orientation orient, QWidget *parent = nullptr);

protected:
    void paintSection(QPainter *painter, const QRect &rect, int logicalIndex) const override;
    void paintEvent(QPaintEvent *event) override;

private:
    int mergedStartFor(int logicalIndex) const;
};

#endif // MERGEDHEADER_H
