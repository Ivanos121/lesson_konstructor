#include "lessonview.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    LessonView w;
    w.showMaximized();
    return a.exec();
}
