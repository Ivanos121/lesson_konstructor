#include "add_lesson.h"
#include "ui_add_lesson.h"

Add_lesson::Add_lesson(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Add_lesson)
{
    ui->setupUi(this);
    connect(ui->applyButton, &QPushButton::clicked, this, &Add_lesson::onAccept);
}

Add_lesson::~Add_lesson()
{
    delete ui;

}

void Add_lesson::on_pushButton_2_clicked()
{
    close();
}


void Add_lesson::on_pushButton_clicked()
{
    close();
}

void Add_lesson::onAccept()
{
    text11 = ui->lineEdit->text();
    text22 = ui->lineEdit_2->text();
    text33 = ui->lineEdit_3->text();
    text44 = ui->comboBox->currentText();

    accept(); // Закрывает диалог
}

