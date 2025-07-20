QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    src/main.cxx \
    src/ui/mainwindow.cxx \
    src/ui/loginpopup.cxx \
    src/ui/signuppopup.cxx \
    src/io/camera.cxx \
    src/sys/exception.cxx

HEADERS += \
    inc/ui/mainwindow.hxx \
    inc/ui/loginpopup.hxx \
    inc/ui/signuppopup.hxx \
    inc/io/camera.hxx \
    inc/sys/exception.hxx \
    inc/sys/macro.hxx

FORMS += \
    res/loginpopup.ui \
    res/mainwindow.ui \
    res/signuppopup.ui

INCLUDEPATH += "inc/"
INCLUDEPATH += "/usr/include/opencv4/"
LIBS += $$system(pkg-config --libs opencv4)

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res/qresource.qrc
