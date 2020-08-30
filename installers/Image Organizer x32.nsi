############################################################################################
#      NSIS Installation Script created by NSIS Quick Setup Script Generator v1.09.18
#               Entirely Edited with NullSoft Scriptable Installation System                
#              by Vlasis K. Barkas aka Red Wine red_wine@freemail.gr Sep 2006               
############################################################################################

!define APP_NAME "Image Organizer x32"
!define COMP_NAME "EfrayimSztokman"
!define VERSION "01.00.00.00"
!define COPYRIGHT ""
!define DESCRIPTION ""
!define INSTALLER_NAME "C:\Users\effi\Desktop\NSIS\Output\Image Organizer x32\setup.exe"
!define MAIN_APP_EXE "Image_Organizer_x32_win.exe"
!define INSTALL_TYPE "SetShellVarContext current"
!define REG_ROOT "HKCU"
!define REG_APP_PATH "Software\Microsoft\Windows\CurrentVersion\App Paths\${MAIN_APP_EXE}"
!define UNINSTALL_PATH "Software\Microsoft\Windows\CurrentVersion\Uninstall\${APP_NAME}"

!define REG_START_MENU "Start Menu Folder"

var SM_Folder

######################################################################

VIProductVersion  "${VERSION}"
VIAddVersionKey "ProductName"  "${APP_NAME}"
VIAddVersionKey "CompanyName"  "${COMP_NAME}"
VIAddVersionKey "LegalCopyright"  "${COPYRIGHT}"
VIAddVersionKey "FileDescription"  "${DESCRIPTION}"
VIAddVersionKey "FileVersion"  "${VERSION}"

######################################################################

SetCompressor ZLIB
Name "${APP_NAME}"
Caption "${APP_NAME}"
OutFile "${INSTALLER_NAME}"
BrandingText "${APP_NAME}"
XPStyle on
InstallDirRegKey "${REG_ROOT}" "${REG_APP_PATH}" ""
InstallDir "$PROGRAMFILES\Image Organizer x32"

######################################################################

!include "MUI.nsh"

!define MUI_ABORTWARNING
!define MUI_UNABORTWARNING

!insertmacro MUI_PAGE_WELCOME

!ifdef LICENSE_TXT
!insertmacro MUI_PAGE_LICENSE "${LICENSE_TXT}"
!endif

!insertmacro MUI_PAGE_DIRECTORY

!ifdef REG_START_MENU
!define MUI_STARTMENUPAGE_NODISABLE
!define MUI_STARTMENUPAGE_DEFAULTFOLDER "Image Organizer x32"
!define MUI_STARTMENUPAGE_REGISTRY_ROOT "${REG_ROOT}"
!define MUI_STARTMENUPAGE_REGISTRY_KEY "${UNINSTALL_PATH}"
!define MUI_STARTMENUPAGE_REGISTRY_VALUENAME "${REG_START_MENU}"
!insertmacro MUI_PAGE_STARTMENU Application $SM_Folder
!endif

!insertmacro MUI_PAGE_INSTFILES

!define MUI_FINISHPAGE_RUN "$INSTDIR\${MAIN_APP_EXE}"
!insertmacro MUI_PAGE_FINISH

!insertmacro MUI_UNPAGE_CONFIRM

!insertmacro MUI_UNPAGE_INSTFILES

!insertmacro MUI_UNPAGE_FINISH

!insertmacro MUI_LANGUAGE "English"

######################################################################

Section -MainProgram
${INSTALL_TYPE}
SetOverwrite ifnewer
SetOutPath "$INSTDIR"
File "C:\Users\effi\Documents\build-Image_Organizer_x32_win-Desktop_Qt_5_14_2_MSVC2017_32bit-Release\release\addimgthread.obj"
File "C:\Users\effi\Documents\build-Image_Organizer_x32_win-Desktop_Qt_5_14_2_MSVC2017_32bit-Release\release\advancedimgsearch.obj"
File "C:\Users\effi\Documents\build-Image_Organizer_x32_win-Desktop_Qt_5_14_2_MSVC2017_32bit-Release\release\BitExactImgFinder.obj"
File "C:\Users\effi\Documents\build-Image_Organizer_x32_win-Desktop_Qt_5_14_2_MSVC2017_32bit-Release\release\D3Dcompiler_47.dll"
File "C:\Users\effi\Documents\build-Image_Organizer_x32_win-Desktop_Qt_5_14_2_MSVC2017_32bit-Release\release\FaceDetector.obj"
File "C:\Users\effi\Documents\build-Image_Organizer_x32_win-Desktop_Qt_5_14_2_MSVC2017_32bit-Release\release\FacesCropped.obj"
File "C:\Users\effi\Documents\build-Image_Organizer_x32_win-Desktop_Qt_5_14_2_MSVC2017_32bit-Release\release\getfacedialog.obj"
File "C:\Users\effi\Documents\build-Image_Organizer_x32_win-Desktop_Qt_5_14_2_MSVC2017_32bit-Release\release\getnumberdialog.obj"
File "C:\Users\effi\Documents\build-Image_Organizer_x32_win-Desktop_Qt_5_14_2_MSVC2017_32bit-Release\release\Image_Organizer_x32_win.exe"
File "C:\Users\effi\Documents\build-Image_Organizer_x32_win-Desktop_Qt_5_14_2_MSVC2017_32bit-Release\release\ImgFileScanner.obj"
File "C:\Users\effi\Documents\build-Image_Organizer_x32_win-Desktop_Qt_5_14_2_MSVC2017_32bit-Release\release\ImgMatchFinderBase.obj"
File "C:\Users\effi\Documents\build-Image_Organizer_x32_win-Desktop_Qt_5_14_2_MSVC2017_32bit-Release\release\ImgSearch.obj"
File "C:\Users\effi\Documents\build-Image_Organizer_x32_win-Desktop_Qt_5_14_2_MSVC2017_32bit-Release\release\libEGL.dll"
File "C:\Users\effi\Documents\build-Image_Organizer_x32_win-Desktop_Qt_5_14_2_MSVC2017_32bit-Release\release\libGLESv2.dll"
File "C:\Users\effi\Documents\build-Image_Organizer_x32_win-Desktop_Qt_5_14_2_MSVC2017_32bit-Release\release\main.obj"
File "C:\Users\effi\Documents\build-Image_Organizer_x32_win-Desktop_Qt_5_14_2_MSVC2017_32bit-Release\release\mainwindow.obj"
File "C:\Users\effi\Documents\build-Image_Organizer_x32_win-Desktop_Qt_5_14_2_MSVC2017_32bit-Release\release\moc_addimgthread.cpp"
File "C:\Users\effi\Documents\build-Image_Organizer_x32_win-Desktop_Qt_5_14_2_MSVC2017_32bit-Release\release\moc_addimgthread.obj"
File "C:\Users\effi\Documents\build-Image_Organizer_x32_win-Desktop_Qt_5_14_2_MSVC2017_32bit-Release\release\moc_getfacedialog.cpp"
File "C:\Users\effi\Documents\build-Image_Organizer_x32_win-Desktop_Qt_5_14_2_MSVC2017_32bit-Release\release\moc_getfacedialog.obj"
File "C:\Users\effi\Documents\build-Image_Organizer_x32_win-Desktop_Qt_5_14_2_MSVC2017_32bit-Release\release\moc_getnumberdialog.cpp"
File "C:\Users\effi\Documents\build-Image_Organizer_x32_win-Desktop_Qt_5_14_2_MSVC2017_32bit-Release\release\moc_getnumberdialog.obj"
File "C:\Users\effi\Documents\build-Image_Organizer_x32_win-Desktop_Qt_5_14_2_MSVC2017_32bit-Release\release\moc_mainwindow.cpp"
File "C:\Users\effi\Documents\build-Image_Organizer_x32_win-Desktop_Qt_5_14_2_MSVC2017_32bit-Release\release\moc_mainwindow.obj"
File "C:\Users\effi\Documents\build-Image_Organizer_x32_win-Desktop_Qt_5_14_2_MSVC2017_32bit-Release\release\moc_MyTreeView.cpp"
File "C:\Users\effi\Documents\build-Image_Organizer_x32_win-Desktop_Qt_5_14_2_MSVC2017_32bit-Release\release\moc_MyTreeView.obj"
File "C:\Users\effi\Documents\build-Image_Organizer_x32_win-Desktop_Qt_5_14_2_MSVC2017_32bit-Release\release\moc_predefs.h"
File "C:\Users\effi\Documents\build-Image_Organizer_x32_win-Desktop_Qt_5_14_2_MSVC2017_32bit-Release\release\moc_scanhandler.cpp"
File "C:\Users\effi\Documents\build-Image_Organizer_x32_win-Desktop_Qt_5_14_2_MSVC2017_32bit-Release\release\moc_scanhandler.obj"
File "C:\Users\effi\Documents\build-Image_Organizer_x32_win-Desktop_Qt_5_14_2_MSVC2017_32bit-Release\release\moc_settingsdialog.cpp"
File "C:\Users\effi\Documents\build-Image_Organizer_x32_win-Desktop_Qt_5_14_2_MSVC2017_32bit-Release\release\moc_settingsdialog.obj"
File "C:\Users\effi\Documents\build-Image_Organizer_x32_win-Desktop_Qt_5_14_2_MSVC2017_32bit-Release\release\MyStandardItemModel.obj"
File "C:\Users\effi\Documents\build-Image_Organizer_x32_win-Desktop_Qt_5_14_2_MSVC2017_32bit-Release\release\MyTreeView.obj"
File "C:\Users\effi\Documents\build-Image_Organizer_x32_win-Desktop_Qt_5_14_2_MSVC2017_32bit-Release\release\opencv_aruco420.dll"
File "C:\Users\effi\Documents\build-Image_Organizer_x32_win-Desktop_Qt_5_14_2_MSVC2017_32bit-Release\release\opencv_bgsegm420.dll"
File "C:\Users\effi\Documents\build-Image_Organizer_x32_win-Desktop_Qt_5_14_2_MSVC2017_32bit-Release\release\opencv_bioinspired420.dll"
File "C:\Users\effi\Documents\build-Image_Organizer_x32_win-Desktop_Qt_5_14_2_MSVC2017_32bit-Release\release\opencv_calib3d420.dll"
File "C:\Users\effi\Documents\build-Image_Organizer_x32_win-Desktop_Qt_5_14_2_MSVC2017_32bit-Release\release\opencv_ccalib420.dll"
File "C:\Users\effi\Documents\build-Image_Organizer_x32_win-Desktop_Qt_5_14_2_MSVC2017_32bit-Release\release\opencv_core420.dll"
File "C:\Users\effi\Documents\build-Image_Organizer_x32_win-Desktop_Qt_5_14_2_MSVC2017_32bit-Release\release\opencv_datasets420.dll"
File "C:\Users\effi\Documents\build-Image_Organizer_x32_win-Desktop_Qt_5_14_2_MSVC2017_32bit-Release\release\opencv_dnn420.dll"
File "C:\Users\effi\Documents\build-Image_Organizer_x32_win-Desktop_Qt_5_14_2_MSVC2017_32bit-Release\release\opencv_dnn_objdetect420.dll"
File "C:\Users\effi\Documents\build-Image_Organizer_x32_win-Desktop_Qt_5_14_2_MSVC2017_32bit-Release\release\opencv_dnn_superres420.dll"
File "C:\Users\effi\Documents\build-Image_Organizer_x32_win-Desktop_Qt_5_14_2_MSVC2017_32bit-Release\release\opencv_dpm420.dll"
File "C:\Users\effi\Documents\build-Image_Organizer_x32_win-Desktop_Qt_5_14_2_MSVC2017_32bit-Release\release\opencv_face420.dll"
File "C:\Users\effi\Documents\build-Image_Organizer_x32_win-Desktop_Qt_5_14_2_MSVC2017_32bit-Release\release\opencv_features2d420.dll"
File "C:\Users\effi\Documents\build-Image_Organizer_x32_win-Desktop_Qt_5_14_2_MSVC2017_32bit-Release\release\opencv_flann420.dll"
File "C:\Users\effi\Documents\build-Image_Organizer_x32_win-Desktop_Qt_5_14_2_MSVC2017_32bit-Release\release\opencv_fuzzy420.dll"
File "C:\Users\effi\Documents\build-Image_Organizer_x32_win-Desktop_Qt_5_14_2_MSVC2017_32bit-Release\release\opencv_gapi420.dll"
File "C:\Users\effi\Documents\build-Image_Organizer_x32_win-Desktop_Qt_5_14_2_MSVC2017_32bit-Release\release\opencv_hfs420.dll"
File "C:\Users\effi\Documents\build-Image_Organizer_x32_win-Desktop_Qt_5_14_2_MSVC2017_32bit-Release\release\opencv_highgui420.dll"
File "C:\Users\effi\Documents\build-Image_Organizer_x32_win-Desktop_Qt_5_14_2_MSVC2017_32bit-Release\release\opencv_imgcodecs420.dll"
File "C:\Users\effi\Documents\build-Image_Organizer_x32_win-Desktop_Qt_5_14_2_MSVC2017_32bit-Release\release\opencv_imgproc420.dll"
File "C:\Users\effi\Documents\build-Image_Organizer_x32_win-Desktop_Qt_5_14_2_MSVC2017_32bit-Release\release\opencv_img_hash420.dll"
File "C:\Users\effi\Documents\build-Image_Organizer_x32_win-Desktop_Qt_5_14_2_MSVC2017_32bit-Release\release\opencv_line_descriptor420.dll"
File "C:\Users\effi\Documents\build-Image_Organizer_x32_win-Desktop_Qt_5_14_2_MSVC2017_32bit-Release\release\opencv_ml420.dll"
File "C:\Users\effi\Documents\build-Image_Organizer_x32_win-Desktop_Qt_5_14_2_MSVC2017_32bit-Release\release\opencv_objdetect420.dll"
File "C:\Users\effi\Documents\build-Image_Organizer_x32_win-Desktop_Qt_5_14_2_MSVC2017_32bit-Release\release\opencv_optflow420.dll"
File "C:\Users\effi\Documents\build-Image_Organizer_x32_win-Desktop_Qt_5_14_2_MSVC2017_32bit-Release\release\opencv_phase_unwrapping420.dll"
File "C:\Users\effi\Documents\build-Image_Organizer_x32_win-Desktop_Qt_5_14_2_MSVC2017_32bit-Release\release\opencv_photo420.dll"
File "C:\Users\effi\Documents\build-Image_Organizer_x32_win-Desktop_Qt_5_14_2_MSVC2017_32bit-Release\release\opencv_plot420.dll"
File "C:\Users\effi\Documents\build-Image_Organizer_x32_win-Desktop_Qt_5_14_2_MSVC2017_32bit-Release\release\opencv_quality420.dll"
File "C:\Users\effi\Documents\build-Image_Organizer_x32_win-Desktop_Qt_5_14_2_MSVC2017_32bit-Release\release\opencv_reg420.dll"
File "C:\Users\effi\Documents\build-Image_Organizer_x32_win-Desktop_Qt_5_14_2_MSVC2017_32bit-Release\release\opencv_rgbd420.dll"
File "C:\Users\effi\Documents\build-Image_Organizer_x32_win-Desktop_Qt_5_14_2_MSVC2017_32bit-Release\release\opencv_saliency420.dll"
File "C:\Users\effi\Documents\build-Image_Organizer_x32_win-Desktop_Qt_5_14_2_MSVC2017_32bit-Release\release\opencv_shape420.dll"
File "C:\Users\effi\Documents\build-Image_Organizer_x32_win-Desktop_Qt_5_14_2_MSVC2017_32bit-Release\release\opencv_stereo420.dll"
File "C:\Users\effi\Documents\build-Image_Organizer_x32_win-Desktop_Qt_5_14_2_MSVC2017_32bit-Release\release\opencv_stitching420.dll"
File "C:\Users\effi\Documents\build-Image_Organizer_x32_win-Desktop_Qt_5_14_2_MSVC2017_32bit-Release\release\opencv_structured_light420.dll"
File "C:\Users\effi\Documents\build-Image_Organizer_x32_win-Desktop_Qt_5_14_2_MSVC2017_32bit-Release\release\opencv_superres420.dll"
File "C:\Users\effi\Documents\build-Image_Organizer_x32_win-Desktop_Qt_5_14_2_MSVC2017_32bit-Release\release\opencv_surface_matching420.dll"
File "C:\Users\effi\Documents\build-Image_Organizer_x32_win-Desktop_Qt_5_14_2_MSVC2017_32bit-Release\release\opencv_text420.dll"
File "C:\Users\effi\Documents\build-Image_Organizer_x32_win-Desktop_Qt_5_14_2_MSVC2017_32bit-Release\release\opencv_tracking420.dll"
File "C:\Users\effi\Documents\build-Image_Organizer_x32_win-Desktop_Qt_5_14_2_MSVC2017_32bit-Release\release\opencv_video420.dll"
File "C:\Users\effi\Documents\build-Image_Organizer_x32_win-Desktop_Qt_5_14_2_MSVC2017_32bit-Release\release\opencv_videoio420.dll"
File "C:\Users\effi\Documents\build-Image_Organizer_x32_win-Desktop_Qt_5_14_2_MSVC2017_32bit-Release\release\opencv_videoio_ffmpeg420.dll"
File "C:\Users\effi\Documents\build-Image_Organizer_x32_win-Desktop_Qt_5_14_2_MSVC2017_32bit-Release\release\opencv_videostab420.dll"
File "C:\Users\effi\Documents\build-Image_Organizer_x32_win-Desktop_Qt_5_14_2_MSVC2017_32bit-Release\release\opencv_xfeatures2d420.dll"
File "C:\Users\effi\Documents\build-Image_Organizer_x32_win-Desktop_Qt_5_14_2_MSVC2017_32bit-Release\release\opencv_ximgproc420.dll"
File "C:\Users\effi\Documents\build-Image_Organizer_x32_win-Desktop_Qt_5_14_2_MSVC2017_32bit-Release\release\opencv_xobjdetect420.dll"
File "C:\Users\effi\Documents\build-Image_Organizer_x32_win-Desktop_Qt_5_14_2_MSVC2017_32bit-Release\release\opencv_xphoto420.dll"
File "C:\Users\effi\Documents\build-Image_Organizer_x32_win-Desktop_Qt_5_14_2_MSVC2017_32bit-Release\release\opengl32sw.dll"
File "C:\Users\effi\Documents\build-Image_Organizer_x32_win-Desktop_Qt_5_14_2_MSVC2017_32bit-Release\release\OrbMatcher.obj"
File "C:\Users\effi\Documents\build-Image_Organizer_x32_win-Desktop_Qt_5_14_2_MSVC2017_32bit-Release\release\qrc_Images.cpp"
File "C:\Users\effi\Documents\build-Image_Organizer_x32_win-Desktop_Qt_5_14_2_MSVC2017_32bit-Release\release\qrc_Images.obj"
File "C:\Users\effi\Documents\build-Image_Organizer_x32_win-Desktop_Qt_5_14_2_MSVC2017_32bit-Release\release\Qt5Core.dll"
File "C:\Users\effi\Documents\build-Image_Organizer_x32_win-Desktop_Qt_5_14_2_MSVC2017_32bit-Release\release\Qt5Gui.dll"
File "C:\Users\effi\Documents\build-Image_Organizer_x32_win-Desktop_Qt_5_14_2_MSVC2017_32bit-Release\release\Qt5Svg.dll"
File "C:\Users\effi\Documents\build-Image_Organizer_x32_win-Desktop_Qt_5_14_2_MSVC2017_32bit-Release\release\Qt5Widgets.dll"
File "C:\Users\effi\Documents\build-Image_Organizer_x32_win-Desktop_Qt_5_14_2_MSVC2017_32bit-Release\release\scanhandler.obj"
File "C:\Users\effi\Documents\build-Image_Organizer_x32_win-Desktop_Qt_5_14_2_MSVC2017_32bit-Release\release\settingsdialog.obj"
File "C:\Users\effi\Documents\build-Image_Organizer_x32_win-Desktop_Qt_5_14_2_MSVC2017_32bit-Release\release\SimilarImgFinder.obj"
SetOutPath "$INSTDIR\translations"
File "C:\Users\effi\Documents\build-Image_Organizer_x32_win-Desktop_Qt_5_14_2_MSVC2017_32bit-Release\release\translations\qt_ar.qm"
File "C:\Users\effi\Documents\build-Image_Organizer_x32_win-Desktop_Qt_5_14_2_MSVC2017_32bit-Release\release\translations\qt_bg.qm"
File "C:\Users\effi\Documents\build-Image_Organizer_x32_win-Desktop_Qt_5_14_2_MSVC2017_32bit-Release\release\translations\qt_ca.qm"
File "C:\Users\effi\Documents\build-Image_Organizer_x32_win-Desktop_Qt_5_14_2_MSVC2017_32bit-Release\release\translations\qt_cs.qm"
File "C:\Users\effi\Documents\build-Image_Organizer_x32_win-Desktop_Qt_5_14_2_MSVC2017_32bit-Release\release\translations\qt_da.qm"
File "C:\Users\effi\Documents\build-Image_Organizer_x32_win-Desktop_Qt_5_14_2_MSVC2017_32bit-Release\release\translations\qt_de.qm"
File "C:\Users\effi\Documents\build-Image_Organizer_x32_win-Desktop_Qt_5_14_2_MSVC2017_32bit-Release\release\translations\qt_en.qm"
File "C:\Users\effi\Documents\build-Image_Organizer_x32_win-Desktop_Qt_5_14_2_MSVC2017_32bit-Release\release\translations\qt_es.qm"
File "C:\Users\effi\Documents\build-Image_Organizer_x32_win-Desktop_Qt_5_14_2_MSVC2017_32bit-Release\release\translations\qt_fi.qm"
File "C:\Users\effi\Documents\build-Image_Organizer_x32_win-Desktop_Qt_5_14_2_MSVC2017_32bit-Release\release\translations\qt_fr.qm"
File "C:\Users\effi\Documents\build-Image_Organizer_x32_win-Desktop_Qt_5_14_2_MSVC2017_32bit-Release\release\translations\qt_gd.qm"
File "C:\Users\effi\Documents\build-Image_Organizer_x32_win-Desktop_Qt_5_14_2_MSVC2017_32bit-Release\release\translations\qt_he.qm"
File "C:\Users\effi\Documents\build-Image_Organizer_x32_win-Desktop_Qt_5_14_2_MSVC2017_32bit-Release\release\translations\qt_hu.qm"
File "C:\Users\effi\Documents\build-Image_Organizer_x32_win-Desktop_Qt_5_14_2_MSVC2017_32bit-Release\release\translations\qt_it.qm"
File "C:\Users\effi\Documents\build-Image_Organizer_x32_win-Desktop_Qt_5_14_2_MSVC2017_32bit-Release\release\translations\qt_ja.qm"
File "C:\Users\effi\Documents\build-Image_Organizer_x32_win-Desktop_Qt_5_14_2_MSVC2017_32bit-Release\release\translations\qt_ko.qm"
File "C:\Users\effi\Documents\build-Image_Organizer_x32_win-Desktop_Qt_5_14_2_MSVC2017_32bit-Release\release\translations\qt_lv.qm"
File "C:\Users\effi\Documents\build-Image_Organizer_x32_win-Desktop_Qt_5_14_2_MSVC2017_32bit-Release\release\translations\qt_pl.qm"
File "C:\Users\effi\Documents\build-Image_Organizer_x32_win-Desktop_Qt_5_14_2_MSVC2017_32bit-Release\release\translations\qt_ru.qm"
File "C:\Users\effi\Documents\build-Image_Organizer_x32_win-Desktop_Qt_5_14_2_MSVC2017_32bit-Release\release\translations\qt_sk.qm"
File "C:\Users\effi\Documents\build-Image_Organizer_x32_win-Desktop_Qt_5_14_2_MSVC2017_32bit-Release\release\translations\qt_uk.qm"
File "C:\Users\effi\Documents\build-Image_Organizer_x32_win-Desktop_Qt_5_14_2_MSVC2017_32bit-Release\release\translations\qt_zh_TW.qm"
SetOutPath "$INSTDIR\styles"
File "C:\Users\effi\Documents\build-Image_Organizer_x32_win-Desktop_Qt_5_14_2_MSVC2017_32bit-Release\release\styles\qwindowsvistastyle.dll"
SetOutPath "$INSTDIR\platforms"
File "C:\Users\effi\Documents\build-Image_Organizer_x32_win-Desktop_Qt_5_14_2_MSVC2017_32bit-Release\release\platforms\qwindows.dll"
SetOutPath "$INSTDIR\imageformats"
File "C:\Users\effi\Documents\build-Image_Organizer_x32_win-Desktop_Qt_5_14_2_MSVC2017_32bit-Release\release\imageformats\qgif.dll"
File "C:\Users\effi\Documents\build-Image_Organizer_x32_win-Desktop_Qt_5_14_2_MSVC2017_32bit-Release\release\imageformats\qicns.dll"
File "C:\Users\effi\Documents\build-Image_Organizer_x32_win-Desktop_Qt_5_14_2_MSVC2017_32bit-Release\release\imageformats\qico.dll"
File "C:\Users\effi\Documents\build-Image_Organizer_x32_win-Desktop_Qt_5_14_2_MSVC2017_32bit-Release\release\imageformats\qjpeg.dll"
File "C:\Users\effi\Documents\build-Image_Organizer_x32_win-Desktop_Qt_5_14_2_MSVC2017_32bit-Release\release\imageformats\qsvg.dll"
File "C:\Users\effi\Documents\build-Image_Organizer_x32_win-Desktop_Qt_5_14_2_MSVC2017_32bit-Release\release\imageformats\qtga.dll"
File "C:\Users\effi\Documents\build-Image_Organizer_x32_win-Desktop_Qt_5_14_2_MSVC2017_32bit-Release\release\imageformats\qtiff.dll"
File "C:\Users\effi\Documents\build-Image_Organizer_x32_win-Desktop_Qt_5_14_2_MSVC2017_32bit-Release\release\imageformats\qwbmp.dll"
File "C:\Users\effi\Documents\build-Image_Organizer_x32_win-Desktop_Qt_5_14_2_MSVC2017_32bit-Release\release\imageformats\qwebp.dll"
SetOutPath "$INSTDIR\iconengines"
File "C:\Users\effi\Documents\build-Image_Organizer_x32_win-Desktop_Qt_5_14_2_MSVC2017_32bit-Release\release\iconengines\qsvgicon.dll"
SectionEnd

######################################################################

Section -Icons_Reg
SetOutPath "$INSTDIR"
WriteUninstaller "$INSTDIR\uninstall.exe"

!ifdef REG_START_MENU
!insertmacro MUI_STARTMENU_WRITE_BEGIN Application
CreateDirectory "$SMPROGRAMS\$SM_Folder"
CreateShortCut "$SMPROGRAMS\$SM_Folder\${APP_NAME}.lnk" "$INSTDIR\${MAIN_APP_EXE}"
CreateShortCut "$DESKTOP\${APP_NAME}.lnk" "$INSTDIR\${MAIN_APP_EXE}"
CreateShortCut "$SMPROGRAMS\$SM_Folder\Uninstall ${APP_NAME}.lnk" "$INSTDIR\uninstall.exe"

!ifdef WEB_SITE
WriteIniStr "$INSTDIR\${APP_NAME} website.url" "InternetShortcut" "URL" "${WEB_SITE}"
CreateShortCut "$SMPROGRAMS\$SM_Folder\${APP_NAME} Website.lnk" "$INSTDIR\${APP_NAME} website.url"
!endif
!insertmacro MUI_STARTMENU_WRITE_END
!endif

!ifndef REG_START_MENU
CreateDirectory "$SMPROGRAMS\Image Organizer x32"
CreateShortCut "$SMPROGRAMS\Image Organizer x32\${APP_NAME}.lnk" "$INSTDIR\${MAIN_APP_EXE}"
CreateShortCut "$DESKTOP\${APP_NAME}.lnk" "$INSTDIR\${MAIN_APP_EXE}"
CreateShortCut "$SMPROGRAMS\Image Organizer x32\Uninstall ${APP_NAME}.lnk" "$INSTDIR\uninstall.exe"

!ifdef WEB_SITE
WriteIniStr "$INSTDIR\${APP_NAME} website.url" "InternetShortcut" "URL" "${WEB_SITE}"
CreateShortCut "$SMPROGRAMS\Image Organizer x32\${APP_NAME} Website.lnk" "$INSTDIR\${APP_NAME} website.url"
!endif
!endif

WriteRegStr ${REG_ROOT} "${REG_APP_PATH}" "" "$INSTDIR\${MAIN_APP_EXE}"
WriteRegStr ${REG_ROOT} "${UNINSTALL_PATH}"  "DisplayName" "${APP_NAME}"
WriteRegStr ${REG_ROOT} "${UNINSTALL_PATH}"  "UninstallString" "$INSTDIR\uninstall.exe"
WriteRegStr ${REG_ROOT} "${UNINSTALL_PATH}"  "DisplayIcon" "$INSTDIR\${MAIN_APP_EXE}"
WriteRegStr ${REG_ROOT} "${UNINSTALL_PATH}"  "DisplayVersion" "${VERSION}"
WriteRegStr ${REG_ROOT} "${UNINSTALL_PATH}"  "Publisher" "${COMP_NAME}"

!ifdef WEB_SITE
WriteRegStr ${REG_ROOT} "${UNINSTALL_PATH}"  "URLInfoAbout" "${WEB_SITE}"
!endif
SectionEnd

######################################################################

Section Uninstall
${INSTALL_TYPE}
Delete "$INSTDIR\addimgthread.obj"
Delete "$INSTDIR\advancedimgsearch.obj"
Delete "$INSTDIR\BitExactImgFinder.obj"
Delete "$INSTDIR\D3Dcompiler_47.dll"
Delete "$INSTDIR\FaceDetector.obj"
Delete "$INSTDIR\FacesCropped.obj"
Delete "$INSTDIR\getfacedialog.obj"
Delete "$INSTDIR\getnumberdialog.obj"
Delete "$INSTDIR\Image_Organizer_x32_win.exe"
Delete "$INSTDIR\ImgFileScanner.obj"
Delete "$INSTDIR\ImgMatchFinderBase.obj"
Delete "$INSTDIR\ImgSearch.obj"
Delete "$INSTDIR\libEGL.dll"
Delete "$INSTDIR\libGLESv2.dll"
Delete "$INSTDIR\main.obj"
Delete "$INSTDIR\mainwindow.obj"
Delete "$INSTDIR\moc_addimgthread.cpp"
Delete "$INSTDIR\moc_addimgthread.obj"
Delete "$INSTDIR\moc_getfacedialog.cpp"
Delete "$INSTDIR\moc_getfacedialog.obj"
Delete "$INSTDIR\moc_getnumberdialog.cpp"
Delete "$INSTDIR\moc_getnumberdialog.obj"
Delete "$INSTDIR\moc_mainwindow.cpp"
Delete "$INSTDIR\moc_mainwindow.obj"
Delete "$INSTDIR\moc_MyTreeView.cpp"
Delete "$INSTDIR\moc_MyTreeView.obj"
Delete "$INSTDIR\moc_predefs.h"
Delete "$INSTDIR\moc_scanhandler.cpp"
Delete "$INSTDIR\moc_scanhandler.obj"
Delete "$INSTDIR\moc_settingsdialog.cpp"
Delete "$INSTDIR\moc_settingsdialog.obj"
Delete "$INSTDIR\MyStandardItemModel.obj"
Delete "$INSTDIR\MyTreeView.obj"
Delete "$INSTDIR\opencv_aruco420.dll"
Delete "$INSTDIR\opencv_bgsegm420.dll"
Delete "$INSTDIR\opencv_bioinspired420.dll"
Delete "$INSTDIR\opencv_calib3d420.dll"
Delete "$INSTDIR\opencv_ccalib420.dll"
Delete "$INSTDIR\opencv_core420.dll"
Delete "$INSTDIR\opencv_datasets420.dll"
Delete "$INSTDIR\opencv_dnn420.dll"
Delete "$INSTDIR\opencv_dnn_objdetect420.dll"
Delete "$INSTDIR\opencv_dnn_superres420.dll"
Delete "$INSTDIR\opencv_dpm420.dll"
Delete "$INSTDIR\opencv_face420.dll"
Delete "$INSTDIR\opencv_features2d420.dll"
Delete "$INSTDIR\opencv_flann420.dll"
Delete "$INSTDIR\opencv_fuzzy420.dll"
Delete "$INSTDIR\opencv_gapi420.dll"
Delete "$INSTDIR\opencv_hfs420.dll"
Delete "$INSTDIR\opencv_highgui420.dll"
Delete "$INSTDIR\opencv_imgcodecs420.dll"
Delete "$INSTDIR\opencv_imgproc420.dll"
Delete "$INSTDIR\opencv_img_hash420.dll"
Delete "$INSTDIR\opencv_line_descriptor420.dll"
Delete "$INSTDIR\opencv_ml420.dll"
Delete "$INSTDIR\opencv_objdetect420.dll"
Delete "$INSTDIR\opencv_optflow420.dll"
Delete "$INSTDIR\opencv_phase_unwrapping420.dll"
Delete "$INSTDIR\opencv_photo420.dll"
Delete "$INSTDIR\opencv_plot420.dll"
Delete "$INSTDIR\opencv_quality420.dll"
Delete "$INSTDIR\opencv_reg420.dll"
Delete "$INSTDIR\opencv_rgbd420.dll"
Delete "$INSTDIR\opencv_saliency420.dll"
Delete "$INSTDIR\opencv_shape420.dll"
Delete "$INSTDIR\opencv_stereo420.dll"
Delete "$INSTDIR\opencv_stitching420.dll"
Delete "$INSTDIR\opencv_structured_light420.dll"
Delete "$INSTDIR\opencv_superres420.dll"
Delete "$INSTDIR\opencv_surface_matching420.dll"
Delete "$INSTDIR\opencv_text420.dll"
Delete "$INSTDIR\opencv_tracking420.dll"
Delete "$INSTDIR\opencv_video420.dll"
Delete "$INSTDIR\opencv_videoio420.dll"
Delete "$INSTDIR\opencv_videoio_ffmpeg420.dll"
Delete "$INSTDIR\opencv_videostab420.dll"
Delete "$INSTDIR\opencv_xfeatures2d420.dll"
Delete "$INSTDIR\opencv_ximgproc420.dll"
Delete "$INSTDIR\opencv_xobjdetect420.dll"
Delete "$INSTDIR\opencv_xphoto420.dll"
Delete "$INSTDIR\opengl32sw.dll"
Delete "$INSTDIR\OrbMatcher.obj"
Delete "$INSTDIR\qrc_Images.cpp"
Delete "$INSTDIR\qrc_Images.obj"
Delete "$INSTDIR\Qt5Core.dll"
Delete "$INSTDIR\Qt5Gui.dll"
Delete "$INSTDIR\Qt5Svg.dll"
Delete "$INSTDIR\Qt5Widgets.dll"
Delete "$INSTDIR\scanhandler.obj"
Delete "$INSTDIR\settingsdialog.obj"
Delete "$INSTDIR\SimilarImgFinder.obj"
Delete "$INSTDIR\translations\qt_ar.qm"
Delete "$INSTDIR\translations\qt_bg.qm"
Delete "$INSTDIR\translations\qt_ca.qm"
Delete "$INSTDIR\translations\qt_cs.qm"
Delete "$INSTDIR\translations\qt_da.qm"
Delete "$INSTDIR\translations\qt_de.qm"
Delete "$INSTDIR\translations\qt_en.qm"
Delete "$INSTDIR\translations\qt_es.qm"
Delete "$INSTDIR\translations\qt_fi.qm"
Delete "$INSTDIR\translations\qt_fr.qm"
Delete "$INSTDIR\translations\qt_gd.qm"
Delete "$INSTDIR\translations\qt_he.qm"
Delete "$INSTDIR\translations\qt_hu.qm"
Delete "$INSTDIR\translations\qt_it.qm"
Delete "$INSTDIR\translations\qt_ja.qm"
Delete "$INSTDIR\translations\qt_ko.qm"
Delete "$INSTDIR\translations\qt_lv.qm"
Delete "$INSTDIR\translations\qt_pl.qm"
Delete "$INSTDIR\translations\qt_ru.qm"
Delete "$INSTDIR\translations\qt_sk.qm"
Delete "$INSTDIR\translations\qt_uk.qm"
Delete "$INSTDIR\translations\qt_zh_TW.qm"
Delete "$INSTDIR\styles\qwindowsvistastyle.dll"
Delete "$INSTDIR\platforms\qwindows.dll"
Delete "$INSTDIR\imageformats\qgif.dll"
Delete "$INSTDIR\imageformats\qicns.dll"
Delete "$INSTDIR\imageformats\qico.dll"
Delete "$INSTDIR\imageformats\qjpeg.dll"
Delete "$INSTDIR\imageformats\qsvg.dll"
Delete "$INSTDIR\imageformats\qtga.dll"
Delete "$INSTDIR\imageformats\qtiff.dll"
Delete "$INSTDIR\imageformats\qwbmp.dll"
Delete "$INSTDIR\imageformats\qwebp.dll"
Delete "$INSTDIR\iconengines\qsvgicon.dll"
 
RmDir "$INSTDIR\iconengines"
RmDir "$INSTDIR\imageformats"
RmDir "$INSTDIR\platforms"
RmDir "$INSTDIR\styles"
RmDir "$INSTDIR\translations"
 
Delete "$INSTDIR\uninstall.exe"
!ifdef WEB_SITE
Delete "$INSTDIR\${APP_NAME} website.url"
!endif

RmDir "$INSTDIR"

!ifdef REG_START_MENU
!insertmacro MUI_STARTMENU_GETFOLDER "Application" $SM_Folder
Delete "$SMPROGRAMS\$SM_Folder\${APP_NAME}.lnk"
Delete "$SMPROGRAMS\$SM_Folder\Uninstall ${APP_NAME}.lnk"
!ifdef WEB_SITE
Delete "$SMPROGRAMS\$SM_Folder\${APP_NAME} Website.lnk"
!endif
Delete "$DESKTOP\${APP_NAME}.lnk"

RmDir "$SMPROGRAMS\$SM_Folder"
!endif

!ifndef REG_START_MENU
Delete "$SMPROGRAMS\Image Organizer x32\${APP_NAME}.lnk"
Delete "$SMPROGRAMS\Image Organizer x32\Uninstall ${APP_NAME}.lnk"
!ifdef WEB_SITE
Delete "$SMPROGRAMS\Image Organizer x32\${APP_NAME} Website.lnk"
!endif
Delete "$DESKTOP\${APP_NAME}.lnk"

RmDir "$SMPROGRAMS\Image Organizer x32"
!endif

DeleteRegKey ${REG_ROOT} "${REG_APP_PATH}"
DeleteRegKey ${REG_ROOT} "${UNINSTALL_PATH}"
SectionEnd

######################################################################

