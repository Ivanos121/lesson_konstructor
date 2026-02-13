#ifndef START_LESSON_H
#define START_LESSON_H

class LessonView;

#include <QDialog>

namespace Ui {
class start_lesson;
}

class start_lesson : public QDialog
{
    Q_OBJECT

public:
    explicit start_lesson(QWidget *parent = nullptr);
    ~start_lesson();
    LessonView *wf;

protected slots:
    void open_base();
private slots:
    void on_pushButton_2_clicked();

    void on_pushButton_clicked();

private:
    Ui::start_lesson *ui;
};

#endif // START_LESSON_H
