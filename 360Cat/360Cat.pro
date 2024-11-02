#-------------------------------------------------
#
# Project created by QtCreator 2024-10-29T18:08:11
#
#-------------------------------------------------

QT       += core gui\
            widgets\
           network
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = 360Cat
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        main.cpp \
        widget.cpp \
    win/loginwin.cpp \
    controller/logincontroller.cpp \
    common/verificationcodelabel.cpp \
    win/registerwin.cpp \
    controller/registercontroller.cpp \
    win/startupanimation.cpp \
    win/menulist.cpp \
    service/settingservice.cpp \
    controller/settingcontroller.cpp

HEADERS += \
        widget.h \
    win/loginwin.h \
    controller/logincontroller.h \
    common/commondefs.h \
    common/singleton.h \
    common/verificationcodelabel.h \
    win/registerwin.h \
    controller/registercontroller.h \
    win/startupanimation.h \
    win/menulist.h \
    service/settingservice.h \
    controller/settingcontroller.h

FORMS += \
        widget.ui \
    win/registerwin.ui \
    win/menulist.ui \
    win/settingwin.ui

INCLUDEPATH +=$$PWD/ffmpeglib/include

LIBS += $$PWD/ffmpeglib/lib/avcodec.lib \
        $$PWD/ffmpeglib/lib/avdevice.lib \
        $$PWD/ffmpeglib/lib/avfilter.lib \
        $$PWD/ffmpeglib/lib/avformat.lib \
        $$PWD/ffmpeglib/lib/avutil.lib \
        $$PWD/ffmpeglib/lib/postproc.lib \
        $$PWD/ffmpeglib/lib/swresample.lib \
        $$PWD/ffmpeglib/lib/swscale.lib
# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
INCLUDEPATH +=D:/QT/opencv_3.4.2_Qt/include
LIBS +=D:/QT/opencv_3.4.2_Qt/x86/bin/libopencv_*.dll \
D:/QT/opencv_3.4.2_Qt/x86/bin/opencv_ffmpeg342.dll

