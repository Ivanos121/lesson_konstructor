/********************************************************************************
** Form generated from reading UI file 'lessonview.ui'
**
** Created by: Qt User Interface Compiler version 6.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LESSONVIEW_H
#define UI_LESSONVIEW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_LessonView
{
public:
    QAction *action;
    QAction *action_2;
    QAction *action_3;
    QAction *action_4;
    QAction *action_5;
    QAction *action_6;
    QAction *action_7;
    QAction *action_8;
    QAction *action_9;
    QAction *action_10;
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QTableWidget *tableWidget;
    QWidget *widget;
    QMenuBar *menubar;
    QMenu *menu;
    QMenu *menu_2;
    QMenu *menu_3;
    QStatusBar *statusbar;
    QToolBar *toolBar;

    void setupUi(QMainWindow *LessonView)
    {
        if (LessonView->objectName().isEmpty())
            LessonView->setObjectName("LessonView");
        LessonView->resize(800, 600);
        action = new QAction(LessonView);
        action->setObjectName("action");
        QIcon icon(QIcon::fromTheme(QIcon::ThemeIcon::DocumentOpen));
        action->setIcon(icon);
        action_2 = new QAction(LessonView);
        action_2->setObjectName("action_2");
        QIcon icon1(QIcon::fromTheme(QIcon::ThemeIcon::Printer));
        action_2->setIcon(icon1);
        action_3 = new QAction(LessonView);
        action_3->setObjectName("action_3");
        action_4 = new QAction(LessonView);
        action_4->setObjectName("action_4");
        action_5 = new QAction(LessonView);
        action_5->setObjectName("action_5");
        action_6 = new QAction(LessonView);
        action_6->setObjectName("action_6");
        QIcon icon2(QIcon::fromTheme(QIcon::ThemeIcon::DocumentSave));
        action_6->setIcon(icon2);
        action_7 = new QAction(LessonView);
        action_7->setObjectName("action_7");
        QIcon icon3(QIcon::fromTheme(QIcon::ThemeIcon::DocumentPrint));
        action_7->setIcon(icon3);
        action_8 = new QAction(LessonView);
        action_8->setObjectName("action_8");
        QIcon icon4(QIcon::fromTheme(QIcon::ThemeIcon::DocumentPrintPreview));
        action_8->setIcon(icon4);
        action_9 = new QAction(LessonView);
        action_9->setObjectName("action_9");
        QIcon icon5(QIcon::fromTheme(QIcon::ThemeIcon::DocumentNew));
        action_9->setIcon(icon5);
        action_9->setMenuRole(QAction::MenuRole::NoRole);
        action_10 = new QAction(LessonView);
        action_10->setObjectName("action_10");
        QIcon icon6(QIcon::fromTheme(QIcon::ThemeIcon::MediaPlaybackPause));
        action_10->setIcon(icon6);
        action_10->setMenuRole(QAction::MenuRole::NoRole);
        centralwidget = new QWidget(LessonView);
        centralwidget->setObjectName("centralwidget");
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName("gridLayout");
        tableWidget = new QTableWidget(centralwidget);
        tableWidget->setObjectName("tableWidget");

        gridLayout->addWidget(tableWidget, 0, 0, 1, 1);

        widget = new QWidget(centralwidget);
        widget->setObjectName("widget");
        widget->setMinimumSize(QSize(0, 40));

        gridLayout->addWidget(widget, 1, 0, 1, 1);

        LessonView->setCentralWidget(centralwidget);
        menubar = new QMenuBar(LessonView);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 30));
        menu = new QMenu(menubar);
        menu->setObjectName("menu");
        menu_2 = new QMenu(menubar);
        menu_2->setObjectName("menu_2");
        menu_3 = new QMenu(menubar);
        menu_3->setObjectName("menu_3");
        LessonView->setMenuBar(menubar);
        statusbar = new QStatusBar(LessonView);
        statusbar->setObjectName("statusbar");
        LessonView->setStatusBar(statusbar);
        toolBar = new QToolBar(LessonView);
        toolBar->setObjectName("toolBar");
        LessonView->addToolBar(Qt::ToolBarArea::TopToolBarArea, toolBar);

        menubar->addAction(menu->menuAction());
        menubar->addAction(menu_2->menuAction());
        menubar->addAction(menu_3->menuAction());
        menu->addAction(action);
        menu->addAction(action_8);
        menu->addAction(action_7);
        menu->addAction(action_2);
        menu_2->addAction(action_3);
        menu_2->addAction(action_6);
        menu_3->addAction(action_4);
        menu_3->addAction(action_5);
        toolBar->addAction(action_9);
        toolBar->addAction(action);
        toolBar->addSeparator();
        toolBar->addAction(action_6);
        toolBar->addAction(action_8);
        toolBar->addAction(action_7);
        toolBar->addSeparator();
        toolBar->addAction(action_10);

        retranslateUi(LessonView);

        QMetaObject::connectSlotsByName(LessonView);
    } // setupUi

    void retranslateUi(QMainWindow *LessonView)
    {
        LessonView->setWindowTitle(QCoreApplication::translate("LessonView", "LessonView", nullptr));
        action->setText(QCoreApplication::translate("LessonView", "\320\236\321\202\320\272\321\200\321\213\321\202\321\214", nullptr));
        action_2->setText(QCoreApplication::translate("LessonView", "\320\222\321\213\321\205\320\276\320\264", nullptr));
        action_3->setText(QCoreApplication::translate("LessonView", "\320\227\320\260\320\263\321\200\321\203\320\267\320\270\321\202\321\214", nullptr));
        action_4->setText(QCoreApplication::translate("LessonView", "\320\241\320\277\321\200\320\260\320\262\320\272\320\260", nullptr));
        action_5->setText(QCoreApplication::translate("LessonView", "\320\236 \320\277\321\200\320\276\320\263\321\200\320\260\320\274\320\274\320\265", nullptr));
        action_6->setText(QCoreApplication::translate("LessonView", "\320\241\320\276\321\205\321\200\320\260\320\275\320\270\321\202\321\214", nullptr));
        action_7->setText(QCoreApplication::translate("LessonView", "\320\237\320\265\321\207\320\260\321\202\321\214", nullptr));
        action_8->setText(QCoreApplication::translate("LessonView", "\320\237\321\200\320\265\320\264\320\276\321\201\320\274\320\276\321\202\321\200 \320\277\320\265\321\207\320\260\321\202\320\270", nullptr));
        action_9->setText(QCoreApplication::translate("LessonView", "\320\241\320\276\320\267\320\264\320\260\321\202\321\214", nullptr));
        action_10->setText(QCoreApplication::translate("LessonView", "\320\227\320\260\320\277\321\200\320\265\321\202 \320\275\320\260 \321\200\320\265\320\264\320\260\320\272\321\202\320\270\321\200\320\276\320\262\320\260\320\275\320\270\320\265 \321\202\320\260\320\261\320\273\320\270\321\206\321\213", nullptr));
        menu->setTitle(QCoreApplication::translate("LessonView", "\320\244\320\260\320\271\320\273", nullptr));
        menu_2->setTitle(QCoreApplication::translate("LessonView", "\320\237\321\200\320\260\320\262\320\272\320\260", nullptr));
        menu_3->setTitle(QCoreApplication::translate("LessonView", "\320\241\320\277\321\200\320\260\320\262\320\272\320\260", nullptr));
        toolBar->setWindowTitle(QCoreApplication::translate("LessonView", "toolBar", nullptr));
    } // retranslateUi

};

namespace Ui {
    class LessonView: public Ui_LessonView {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LESSONVIEW_H
