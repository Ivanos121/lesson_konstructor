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
    bool saveLesson();
    bool print_lesson(QTableWidget *table, QPrinter *printer);

    Ui::LessonView *ui;

    void vertikalHeader();
protected:
    void closeEvent(QCloseEvent *event) override;

protected slots:
    void ClickedLeftButton(int row, int column);
    void showPrintPreview(QWidget *parent, QTableWidget *table, const QString &str);
    void newLesson();
    void aboutLessons();
    void printLessonDialog();
    void notEditTable(bool checked);
    void onItemChanged();

    void openLesson();
    void deleteLesson();
    void medgeLesson();
    void loadAndAutoMergeFromDb(QSqlDatabase &db, QTableWidget *tableWidget, const QString &controlString);
private:
    QSqlDatabase sdb;
    QString dataSourceFilename;
    QTableWidget* table;
    QString str;
     bool editingEnabled = false;
    bool isModified = false;
    QSet<QPair<int,int>> mergedLefts_;
    QMap<QPair<int,int>, QString> savedCells_;

private:
    QWidget *m_parent;
    QTableWidget *m_table;
    QString m_str;
    QString controlString;

};
#endif // LESSONVIEW_H
