QT       += core gui
QT += qml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++1z

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += $$_PRO_FILE_PWD_/ImgOrganizer/Dependencies/include


LIBS +=     $$_PRO_FILE_PWD_/ImgOrganizer/Dependencies/lib/*.lib



SOURCES += \
    ImgOrganizer/BitExactImgFinder.cpp \
    ImgOrganizer/ImgFileScanner.cpp \
    ImgOrganizer/ImgMatchFinderBase.cpp \
    ImgOrganizer/SimilarImgFinder.cpp \
    MyStandardItemModel.cpp \
    MyTreeView.cpp \
    ScanController.cpp \
    ImgOrganizer/OrbMatcher.cpp \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    ImgOrganizer/ImgFileScanner.h \
    ImgOrganizer/ImgMatchFinderBase.h \
    MyStandardItemModel.h \
    MyTreeView.h \
    ScanController.h \
    mainwindow.h \
    ImgOrganizer/COLOR.h \
    ImgOrganizer/BitExactImgFinder.h \
    ImgOrganizer/OrbMatcher.h \
    ImgOrganizer/SimilarImgFinder.h

FORMS += \
    mainwindow.ui

TRANSLATIONS += \
    project2020_he_IL.ts

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Images.qrc
