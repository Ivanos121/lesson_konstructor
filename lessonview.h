#ifndef LESSONVIEW_H
#define LESSONVIEW_H

#include "aboutlesson.h"
#include "add_lesson.h"
#include "start_lesson.h"

#include <QMainWindow>
#include <QPrinter>
#include <QSqlDatabase>
#include <QStandardItemModel>
#include <QTableWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
class LessonView;
}
QT_END_NAMESPACE

class LessonView : public QMainWindow
{
    Q_OBJECT

public:
    LessonView(QWidget *parent = nullptr);
    ~LessonView();
    Add_lesson *rsc;
    start_lesson *rsc2;
    aboutLesson *rsc3;

    bool connectToDatabase(QSqlDatabase &db, QString path);
    void loadDataToTable(QSqlDatabase &db, QTableWidget *tableWidget);
    void saveLesson();
    bool print_lesson(QTableWidget *table, QPrinter *printer);

    Ui::LessonView *ui;

protected slots:
    void ClickedLeftButton(int row, int column);
    void showPrintPreview(QWidget *parent, QTableWidget *table, const QString &str);
    void newLesson();
    void aboutLessons();
    void printLessonDialog();
    void notEditTable(bool checked);
private:
    QSqlDatabase sdb;
    QString dataSourceFilename;
    QTableWidget* table;
    QString str;
     bool editingEnabled = false;
};
#endif // LESSONVIEW_H
