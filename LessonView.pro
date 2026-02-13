QT       += core gui sql printsupport \
    core5compat
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    aboutlesson.cpp \
    add_lesson.cpp \
    main.cpp \
    lessonview.cpp \
    start_lesson.cpp

HEADERS += \
    aboutlesson.h \
    add_lesson.h \
    lessonview.h \
    start_lesson.h

FORMS += \
    aboutlesson.ui \
    add_lesson.ui \
    lessonview.ui \
    start_lesson.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
