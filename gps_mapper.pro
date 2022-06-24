#-------------------------------------------------
#
# Project created by QtCreator 2012-11-28T14:29:06
#
#------------------------------------------------


QT += core gui
QT += widgets
QT += sql
#QT += webview
#QT += webkitwidgets
QT += webenginewidgets
QT += webchannel
QT += network
QT += xml


macos: {
  VERSION = $${THE_APP_VERSION}.$${THE_APP_BUILD}
  QMAKE_MACOSX_DEPLOYMENT_TARGET = 10.12

  # Only Intel binaries are accepted so force this
  CONFIG += x86

  # Copy the custom Info.plist to the app bundle
  plist.path = "$$DESTDIR/$$join(TARGET,,,.app)/Contents"
  plist.files = Info.plist
  QMAKE_INFO_PLIST = macos/Info.plist
  INSTALLS += plist

  ICON = macos/mapper_icon.icns
}

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = gps_mapper
TEMPLATE = app


SOURCES += main.cpp\
    mainwindow.cpp \
    preferencesdialog.cpp \
    recorddialog.cpp \
    querydialog.cpp \
    editdialog.cpp \
    dbDialog.cpp \
    nmeaDialog.cpp \
    welcomeDialog.cpp

HEADERS  += \
    mainwindow.h \
    preferencesdialog.h \
    recorddialog.h \
    querydialog.h \
    editdialog.h \
    dbDialog.h \
    nmeaDialog.h \
    welcomeDialog.h

FORMS    += \
    mainwindow.ui \
    preferencesdialog.ui \
    recorddialog.ui \
    querydialog.ui \
    editdialog.ui \
    dbDialog.ui \
    nmeaDialog.ui \
    welcomeDialog.ui

QT += opengl
#CONFIG += QwtDll

RESOURCES += \
    resrcs/res.qrc

OTHER_FILES += \
    gmapsCode.js \
    resrcs/gmapsCode.js

DISTFILES +=
