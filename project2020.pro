########   For Static Linking ################
QT       += core gui
QT += qml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += \
        c++1z \
        static
# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ImgOrganizer/BitExactImgFinder.cpp \
    ImgOrganizer/ImgFileScanner.cpp \
    ImgOrganizer/ImgMatchFinderBase.cpp \
    ImgOrganizer/SimilarImgFinder.cpp \
    ImgOrganizer/advancedimgsearch.cpp \
    ImgOrganizer/ImgSearch.cpp \
    ImgOrganizer/FaceDetection/FaceDetector.cpp \
    ImgOrganizer/FaceDetection/FacesCropped.cpp \
    addimgthread.cpp \
    MyStandardItemModel.cpp \
    MyTreeView.cpp \
    ImgOrganizer/OrbMatcher.cpp \
    getfacedialog.cpp \
    getnumberdialog.cpp \
    main.cpp \
    mainwindow.cpp \
    scanhandler.cpp \
    settingsdialog.cpp

HEADERS += \
    ImgOrganizer/ImgFileScanner.h \
    ImgOrganizer/ImgMatchFinderBase.h \
    ImgOrganizer/advancedimgsearch.h \
    ImgOrganizer/FaceDetection/FaceDetector.h \
    ImgOrganizer/FaceDetection/FacesCropped.h \
    ImgOrganizer/ImgSearch.h \
    addimgthread.h \
    MyStandardItemModel.h \
    MyTreeView.h \
    getfacedialog.h \
    getnumberdialog.h \
    mainwindow.h \
    ImgOrganizer/COLOR.h \
    ImgOrganizer/BitExactImgFinder.h \
    ImgOrganizer/OrbMatcher.h \
    ImgOrganizer/SimilarImgFinder.h \
    scanhandler.h \
    settingsdialog.h

FORMS += \
    getfacedialog.ui \
    getnumberdialog.ui \
    mainwindow.ui \
    settings.ui \
    settingsdialog.ui

TRANSLATIONS += \
    project2020_he_IL.ts

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Images.qrc

INCLUDEPATH += $$PWD/ImgOrganizer/Dependencies/include

DEPENDPATH += $$PWD/ImgOrganizer/Dependencies/include

LIBS +=  \
        -L$$PWD/ImgOrganizer/Dependencies/lib/   -lopencv_core420 \
        -L$$PWD/ImgOrganizer/Dependencies/lib/   -lopencv_highgui420 \
        -L$$PWD/ImgOrganizer/Dependencies/lib/   -lopencv_flann420  \
        -L$$PWD/ImgOrganizer/Dependencies/lib/   -lopencv_imgcodecs420 \
        -L$$PWD/ImgOrganizer/Dependencies/lib/   -lopencv_imgproc420 \
        -L$$PWD/ImgOrganizer/Dependencies/lib/   -lopencv_photo420 \
        -L$$PWD/ImgOrganizer/Dependencies/lib/   -lopencv_reg420 \
        -L$$PWD/ImgOrganizer/Dependencies/lib/   -lopencv_ximgproc420 \
        -L$$PWD/ImgOrganizer/Dependencies/lib/   -lopencv_objdetect420 \
        -L$$PWD/ImgOrganizer/Dependencies/lib/   -lopencv_videoio420 \
        -L$$PWD/ImgOrganizer/Dependencies/lib/   -lopencv_xobjdetect420 \
        -L$$PWD/ImgOrganizer/Dependencies/lib/   -lopencv_shape420 \
        -L$$PWD/ImgOrganizer/Dependencies/lib/   -lopencv_img_hash420 \
        -L$$PWD/ImgOrganizer/Dependencies/lib/   -lopencv_features2d420 \
        -L$$PWD/ImgOrganizer/Dependencies/lib/   -lopencv_xfeatures2d420 \
        -L$$PWD/ImgOrganizer/Dependencies/lib/   -lopencv_face420 \
        -L$$PWD/ImgOrganizer/Dependencies/lib/   -lIlmImf \
        -L$$PWD/ImgOrganizer/Dependencies/lib/   -lippiw \
        -L$$PWD/ImgOrganizer/Dependencies/lib/   -littnotify \
        -L$$PWD/ImgOrganizer/Dependencies/lib/   -llibjasper \
        -L$$PWD/ImgOrganizer/Dependencies/lib/   -llibjpeg-turbo \
        -L$$PWD/ImgOrganizer/Dependencies/lib/   -llibpng \
        -L$$PWD/ImgOrganizer/Dependencies/lib/   -llibprotobuf \
        -L$$PWD/ImgOrganizer/Dependencies/lib/   -llibtiff \
        -L$$PWD/ImgOrganizer/Dependencies/lib/   -llibwebp \
        -L$$PWD/ImgOrganizer/Dependencies/lib/   -lquirc \
        -L$$PWD/ImgOrganizer/Dependencies/lib/   -lzlib \
        -L$$PWD/ImgOrganizer/Dependencies/lib/   -lippicvmt \
        -luser32 \
        -lgdi32 \
        -lAdvapi32 \
        -lComdlg32 \
        -lMfPlat \
        -lMf \
        -lMFREADWRITE \
        -lD3D11\
        -lSHLWAPI \
        -lOLE32 \
        -lKernel32 \
        -lShell32


QMAKE_CXXFLAGS_RELEASE += /MT

###### WITH SHARED LIBS ##################
#QT       += core gui
#QT += qml

#greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

#CONFIG += \
#        c++1z \


## The following define makes your compiler emit warnings if you use
## any Qt feature that has been marked deprecated (the exact warnings
## depend on your compiler). Please consult the documentation of the
## deprecated API in order to know how to port your code away from it.
#DEFINES += QT_DEPRECATED_WARNINGS

## You can also make your code fail to compile if it uses deprecated APIs.
## In order to do so, uncomment the following line.
## You can also select to disable deprecated APIs only up to a certain version of Qt.
##DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


#SOURCES += \
#    ImgOrganizer/BitExactImgFinder.cpp \
#    ImgOrganizer/ImgFileScanner.cpp \
#    ImgOrganizer/ImgMatchFinderBase.cpp \
#    ImgOrganizer/SimilarImgFinder.cpp \
#    MyStandardItemModel.cpp \
#    MyTreeView.cpp \
#    ScanController.cpp \
#    ImgOrganizer/OrbMatcher.cpp \
#    main.cpp \
#    mainwindow.cpp

#HEADERS += \
#    ImgOrganizer/ImgFileScanner.h \
#    ImgOrganizer/ImgMatchFinderBase.h \
#    MyStandardItemModel.h \
#    MyTreeView.h \
#    ScanController.h \
#    mainwindow.h \
#    ImgOrganizer/COLOR.h \
#    ImgOrganizer/BitExactImgFinder.h \
#    ImgOrganizer/OrbMatcher.h \
#    ImgOrganizer/SimilarImgFinder.h

#FORMS += \
#    mainwindow.ui

#TRANSLATIONS += \
#    project2020_he_IL.ts

## Default rules for deployment.
#qnx: target.path = /tmp/$${TARGET}/bin
#else: unix:!android: target.path = /opt/$${TARGET}/bin
#!isEmpty(target.path): INSTALLS += target

#RESOURCES += \
#    Images.qrc

#LIBS += $$PWD/ImgOrganizer/Dependencies/shared_libs/*


#INCLUDEPATH += $$PWD/ImgOrganizer/Dependencies/include
#DEPENDPATH += $$PWD/ImgOrganizer/Dependencies/include

#PRE_TARGETDEPS += $$PWD/ImgOrganizer/Dependencies/shared_libs/*
