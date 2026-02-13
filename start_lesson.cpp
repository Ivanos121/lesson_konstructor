#include "start_lesson.h"
#include "ui_start_lesson.h"
#include "lessonview.h"
#include "ui_lessonview.h"

#include <QSqlDatabase>
#include <QTableWidget>

start_lesson::start_lesson(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::start_lesson)
{
    wf = (LessonView*)parent;
    ui->setupUi(this);

    QStringList items = {"Основная", "Совмещение"};
    ui->comboBox->addItems(items);

    QStringList items2 = {"Основная", "Совмещение"};
    ui->comboBox_2->addItems(items2);
    connect(ui->pushButton, &QPushButton::clicked, this, &start_lesson::open_base);
}

start_lesson::~start_lesson()
{
    delete ui;
}

void start_lesson::open_base()
{
    QSqlDatabase db;
    if (!wf->connectToDatabase(db, "/home/elf/Programs/lesson/LessonView/lesson_blanc.db"))
        return;

    // Предположим, у вас есть указатель на QTableWidget в UI
    QTableWidget *tableWidget = wf->ui->tableWidget;
    wf->loadDataToTable(db, tableWidget);
}

void start_lesson::on_pushButton_2_clicked()
{
    close();
}


void start_lesson::on_pushButton_clicked()
{
    close();
}

