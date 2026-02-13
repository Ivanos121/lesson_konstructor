/********************************************************************************
** Form generated from reading UI file 'add_lesson.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADD_LESSON_H
#define UI_ADD_LESSON_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
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
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QPushButton *applyButton;
    QPushButton *closeButton;
    QFormLayout *formLayout;
    QLabel *label;
    QLineEdit *lineEdit;
    QLabel *label_2;
    QLineEdit *lineEdit_2;
    QLabel *label_3;
    QLineEdit *lineEdit_3;
    QComboBox *comboBox;
    QLabel *label_4;

    void setupUi(QDialog *Add_lesson)
    {
        if (Add_lesson->objectName().isEmpty())
            Add_lesson->setObjectName("Add_lesson");
        Add_lesson->resize(370, 216);
        gridLayout = new QGridLayout(Add_lesson);
        gridLayout->setObjectName("gridLayout");
        widget = new QWidget(Add_lesson);
        widget->setObjectName("widget");
        widget->setMinimumSize(QSize(0, 10));
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setObjectName("horizontalLayout");
        applyButton = new QPushButton(widget);
        applyButton->setObjectName("applyButton");

        horizontalLayout->addWidget(applyButton);

        closeButton = new QPushButton(widget);
        closeButton->setObjectName("closeButton");

        horizontalLayout->addWidget(closeButton);


        gridLayout->addWidget(widget, 1, 0, 1, 1);

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

        comboBox = new QComboBox(Add_lesson);
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->setObjectName("comboBox");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(comboBox->sizePolicy().hasHeightForWidth());
        comboBox->setSizePolicy(sizePolicy);

        formLayout->setWidget(3, QFormLayout::ItemRole::FieldRole, comboBox);

        label_4 = new QLabel(Add_lesson);
        label_4->setObjectName("label_4");

        formLayout->setWidget(3, QFormLayout::ItemRole::LabelRole, label_4);


        gridLayout->addLayout(formLayout, 0, 0, 1, 1);


        retranslateUi(Add_lesson);

        QMetaObject::connectSlotsByName(Add_lesson);
    } // setupUi

    void retranslateUi(QDialog *Add_lesson)
    {
        Add_lesson->setWindowTitle(QCoreApplication::translate("Add_lesson", "Dialog", nullptr));
        applyButton->setText(QCoreApplication::translate("Add_lesson", "\320\237\321\200\320\270\320\275\321\217\321\202\321\214", nullptr));
        closeButton->setText(QCoreApplication::translate("Add_lesson", "\320\227\320\260\320\272\321\200\321\213\321\202\321\214", nullptr));
        label->setText(QCoreApplication::translate("Add_lesson", "\320\237\321\200\320\265\320\264\320\274\320\265\321\202", nullptr));
        label_2->setText(QCoreApplication::translate("Add_lesson", "\320\223\321\200\321\203\320\277\320\277\320\260", nullptr));
        label_3->setText(QCoreApplication::translate("Add_lesson", "\320\220\321\203\320\264\320\270\321\202\320\276\321\200\320\270\321\217", nullptr));
        comboBox->setItemText(0, QCoreApplication::translate("Add_lesson", "\320\233\320\265\320\272\321\206\320\270\321\217", nullptr));
        comboBox->setItemText(1, QCoreApplication::translate("Add_lesson", "\320\237\321\200\320\260\320\272\321\202\320\270\321\207\320\265\321\201\320\272\320\276\320\265 \320\267\320\260\320\275\321\217\321\202\320\270\320\265", nullptr));
        comboBox->setItemText(2, QCoreApplication::translate("Add_lesson", "\320\233\320\260\320\261\320\276\321\200\320\260\321\202\320\276\321\200\320\275\320\276\320\265 \320\267\320\260\320\275\321\217\321\202\320\270\320\265", nullptr));

        label_4->setText(QCoreApplication::translate("Add_lesson", "TextLabel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Add_lesson: public Ui_Add_lesson {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADD_LESSON_H
