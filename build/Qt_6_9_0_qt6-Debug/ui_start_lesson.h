/********************************************************************************
** Form generated from reading UI file 'start_lesson.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_START_LESSON_H
#define UI_START_LESSON_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_start_lesson
{
public:
    QGridLayout *gridLayout_2;
    QGridLayout *gridLayout;
    QLabel *label;
    QLineEdit *lineEdit;
    QLabel *label_2;
    QLineEdit *lineEdit_2;
    QLabel *label_3;
    QLineEdit *lineEdit_3;
    QLabel *label_4;
    QLineEdit *lineEdit_4;
    QLabel *label_7;
    QComboBox *comboBox;
    QLabel *label_6;
    QLineEdit *lineEdit_5;
    QLabel *label_8;
    QComboBox *comboBox_2;
    QLabel *label_5;
    QPushButton *pushButton_2;
    QPushButton *pushButton;

    void setupUi(QDialog *start_lesson)
    {
        if (start_lesson->objectName().isEmpty())
            start_lesson->setObjectName("start_lesson");
        start_lesson->resize(413, 356);
        gridLayout_2 = new QGridLayout(start_lesson);
        gridLayout_2->setObjectName("gridLayout_2");
        gridLayout = new QGridLayout();
        gridLayout->setObjectName("gridLayout");
        label = new QLabel(start_lesson);
        label->setObjectName("label");

        gridLayout->addWidget(label, 0, 0, 1, 1);

        lineEdit = new QLineEdit(start_lesson);
        lineEdit->setObjectName("lineEdit");

        gridLayout->addWidget(lineEdit, 0, 1, 1, 1);

        label_2 = new QLabel(start_lesson);
        label_2->setObjectName("label_2");

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        lineEdit_2 = new QLineEdit(start_lesson);
        lineEdit_2->setObjectName("lineEdit_2");

        gridLayout->addWidget(lineEdit_2, 1, 1, 1, 1);

        label_3 = new QLabel(start_lesson);
        label_3->setObjectName("label_3");

        gridLayout->addWidget(label_3, 2, 0, 1, 1);

        lineEdit_3 = new QLineEdit(start_lesson);
        lineEdit_3->setObjectName("lineEdit_3");

        gridLayout->addWidget(lineEdit_3, 2, 1, 1, 1);

        label_4 = new QLabel(start_lesson);
        label_4->setObjectName("label_4");

        gridLayout->addWidget(label_4, 3, 0, 1, 1);

        lineEdit_4 = new QLineEdit(start_lesson);
        lineEdit_4->setObjectName("lineEdit_4");

        gridLayout->addWidget(lineEdit_4, 3, 1, 1, 1);

        label_7 = new QLabel(start_lesson);
        label_7->setObjectName("label_7");

        gridLayout->addWidget(label_7, 4, 0, 1, 1);

        comboBox = new QComboBox(start_lesson);
        comboBox->setObjectName("comboBox");

        gridLayout->addWidget(comboBox, 4, 1, 1, 1);

        label_6 = new QLabel(start_lesson);
        label_6->setObjectName("label_6");

        gridLayout->addWidget(label_6, 5, 0, 1, 1);

        lineEdit_5 = new QLineEdit(start_lesson);
        lineEdit_5->setObjectName("lineEdit_5");

        gridLayout->addWidget(lineEdit_5, 5, 1, 1, 1);

        label_8 = new QLabel(start_lesson);
        label_8->setObjectName("label_8");

        gridLayout->addWidget(label_8, 6, 0, 1, 1);

        comboBox_2 = new QComboBox(start_lesson);
        comboBox_2->setObjectName("comboBox_2");

        gridLayout->addWidget(comboBox_2, 6, 1, 1, 1);


        gridLayout_2->addLayout(gridLayout, 0, 0, 2, 3);

        label_5 = new QLabel(start_lesson);
        label_5->setObjectName("label_5");

        gridLayout_2->addWidget(label_5, 1, 1, 1, 1);

        pushButton_2 = new QPushButton(start_lesson);
        pushButton_2->setObjectName("pushButton_2");

        gridLayout_2->addWidget(pushButton_2, 2, 2, 1, 1);

        pushButton = new QPushButton(start_lesson);
        pushButton->setObjectName("pushButton");

        gridLayout_2->addWidget(pushButton, 2, 1, 1, 1);


        retranslateUi(start_lesson);

        QMetaObject::connectSlotsByName(start_lesson);
    } // setupUi

    void retranslateUi(QDialog *start_lesson)
    {
        start_lesson->setWindowTitle(QCoreApplication::translate("start_lesson", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("start_lesson", "\321\204. \320\230. \320\236. \320\277\321\200\320\265\320\277\320\276\320\264\320\260\320\262\320\260\321\202\320\265\320\273\321\217", nullptr));
        label_2->setText(QCoreApplication::translate("start_lesson", "\320\224\320\276\320\273\320\266\320\275\320\276\321\201\321\202\321\214", nullptr));
        label_3->setText(QCoreApplication::translate("start_lesson", "\320\243\321\207\320\265\320\261\320\275\321\213\320\271 \320\263\320\276\320\264", nullptr));
        label_4->setText(QCoreApplication::translate("start_lesson", "\320\235\320\260\320\263\321\200\321\203\320\267\320\272\320\260, \320\240\320\221", nullptr));
        label_7->setText(QCoreApplication::translate("start_lesson", "\320\242\320\270\320\277 \320\275\320\260\320\263\321\200\321\203\320\267\320\272\320\270", nullptr));
        label_6->setText(QCoreApplication::translate("start_lesson", "\320\235\320\260\320\263\321\200\321\203\320\267\320\272\320\260, \320\240\320\244", nullptr));
        label_8->setText(QCoreApplication::translate("start_lesson", "\320\242\320\270\320\277 \320\275\320\260\320\263\321\200\321\203\320\267\320\272\320\270", nullptr));
        label_5->setText(QString());
        pushButton_2->setText(QCoreApplication::translate("start_lesson", "\320\236\321\202\320\274\320\265\320\275\320\260", nullptr));
        pushButton->setText(QCoreApplication::translate("start_lesson", "\320\237\321\200\320\270\320\274\320\265\320\275\320\270\321\202\321\214", nullptr));
    } // retranslateUi

};

namespace Ui {
    class start_lesson: public Ui_start_lesson {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_START_LESSON_H
