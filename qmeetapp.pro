QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++20

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    src/main.cxx \
    src/ui/mainwindow.cxx \
    src/ui/createmeetingdialog.cxx \
    src/ui/logindialog.cxx \
    src/ui/signupdialog.cxx \
    src/ui/joinmeetingdialog.cxx \
    src/ui/meetingwindow.cxx \
    src/ui/camerawidget.cxx \
    src/ui/popupdialog.cxx \
    src/io/camera.cxx \
    src/controller/controllermgr.cxx \
    src/controller/meetingctrl.cxx \
    src/controller/accountctrl.cxx \
    src/controller/clientctrl.cxx \
    src/types/user.cxx \
    src/types/meetinginfo.cxx \
    src/hash/sha256.cxx \
    src/db/rtdb.cxx \
    src/net/curlclient.cxx

HEADERS += \
    inc/ui/logindialog.hxx \
    inc/ui/mainwindow.hxx \
    inc/ui/signupdialog.hxx \
    inc/ui/createmeetingdialog.hxx \
    inc/ui/joinmeetingdialog.hxx \
    inc/ui/meetingwindow.hxx \
    inc/ui/camerawidget.hxx \
    inc/ui/popupdialog.hxx

FORMS += \
    res/createmeetingdialog.ui \
    res/joinmeetingdialog.ui \
    res/logindialog.ui \
    res/mainwindow.ui \
    res/meetingwindow.ui \
    res/popupdialog.ui \
    res/signupdialog.ui

INCLUDEPATH += "inc/"
INCLUDEPATH += "/usr/include/opencv4/"
LIBS += $$system(pkg-config --libs opencv4)
LIBS += $$system(pkg-config --libs libcurl)

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    res/qresource.qrc
