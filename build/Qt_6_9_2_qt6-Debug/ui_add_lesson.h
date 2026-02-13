/********************************************************************************
** Form generated from reading UI file 'add_lesson.ui'
**
** Created by: Qt User Interface Compiler version 6.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADD_LESSON_H
#define UI_ADD_LESSON_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Add_lesson
{
public:
    QGridLayout *gridLayout;
    QFormLayout *formLayout;
    QLabel *label;
    QLineEdit *lineEdit;
    QLabel *label_2;
    QLineEdit *lineEdit_2;
    QLabel *label_3;
    QLineEdit *lineEdit_3;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton;
    QPushButton *pushButton_2;

    void setupUi(QDialog *Add_lesson)
    {
        if (Add_lesson->objectName().isEmpty())
            Add_lesson->setObjectName("Add_lesson");
        Add_lesson->resize(370, 181);
        gridLayout = new QGridLayout(Add_lesson);
        gridLayout->setObjectName("gridLayout");
        formLayout = new QFormLayout();
        formLayout->setObjectName("formLayout");
        label = new QLabel(Add_lesson);
        label->setObjectName("label");

        formLayout->setWidget(0, QFormLayout::ItemRole::LabelRole, label);

        lineEdit = new QLineEdit(Add_lesson);
        lineEdit->setObjectName("lineEdit");

        formLayout->setWidget(0, QFormLayout::ItemRole::FieldRole, lineEdit);

        label_2 = new QLabel(Add_lesson);
        label_2->setObjectName("label_2");

        formLayout->setWidget(1, QFormLayout::ItemRole::LabelRole, label_2);

        lineEdit_2 = new QLineEdit(Add_lesson);
        lineEdit_2->setObjectName("lineEdit_2");

        formLayout->setWidget(1, QFormLayout::ItemRole::FieldRole, lineEdit_2);

        label_3 = new QLabel(Add_lesson);
        label_3->setObjectName("label_3");

        formLayout->setWidget(2, QFormLayout::ItemRole::LabelRole, label_3);

        lineEdit_3 = new QLineEdit(Add_lesson);
        lineEdit_3->setObjectName("lineEdit_3");

        formLayout->setWidget(2, QFormLayout::ItemRole::FieldRole, lineEdit_3);


        gridLayout->addLayout(formLayout, 0, 0, 1, 1);

        widget = new QWidget(Add_lesson);
        widget->setObjectName("widget");
        widget->setMinimumSize(QSize(0, 10));
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setObjectName("horizontalLayout");
        pushButton = new QPushButton(widget);
        pushButton->setObjectName("pushButton");

        horizontalLayout->addWidget(pushButton);

        pushButton_2 = new QPushButton(widget);
        pushButton_2->setObjectName("pushButton_2");

        horizontalLayout->addWidget(pushButton_2);


        gridLayout->addWidget(widget, 1, 0, 1, 1);


        retranslateUi(Add_lesson);

        QMetaObject::connectSlotsByName(Add_lesson);
    } // setupUi

    void retranslateUi(QDialog *Add_lesson)
    {
        Add_lesson->setWindowTitle(QCoreApplication::translate("Add_lesson", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("Add_lesson", "\320\237\321\200\320\265\320\264\320\274\320\265\321\202", nullptr));
        label_2->setText(QCoreApplication::translate("Add_lesson", "\320\223\321\200\321\203\320\277\320\277\320\260", nullptr));
        label_3->setText(QCoreApplication::translate("Add_lesson", "\320\220\321\203\320\264\320\270\321\202\320\276\321\200\320\270\321\217", nullptr));
        pushButton->setText(QCoreApplication::translate("Add_lesson", "\320\237\321\200\320\270\320\275\321\217\321\202\321\214", nullptr));
        pushButton_2->setText(QCoreApplication::translate("Add_lesson", "\320\227\320\260\320\272\321\200\321\213\321\202\321\214", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Add_lesson: public Ui_Add_lesson {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADD_LESSON_H
