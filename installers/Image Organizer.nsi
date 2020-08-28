############################################################################################
#      NSIS Installation Script created by NSIS Quick Setup Script Generator v1.09.18
#               Entirely Edited with NullSoft Scriptable Installation System                
#              by Vlasis K. Barkas aka Red Wine red_wine@freemail.gr Sep 2006               
############################################################################################

!define APP_NAME "Image Organizer"
!define COMP_NAME "Image Organizer"
!define VERSION "01.00.00.00"
!define COPYRIGHT ""
!define DESCRIPTION ""
!define INSTALLER_NAME "C:\Users\effi\Desktop\NSIS\Output\Image Organizer\setup.exe"
!define MAIN_APP_EXE "Image_Organizer.exe"
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
InstallDir "$PROGRAMFILES\Image Organizer"

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
!define MUI_STARTMENUPAGE_DEFAULTFOLDER "Image Organizer"
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
File "C:\Users\effi\Documents\build-Image_Organizer-Desktop_Qt_5_14_2_MSVC2017_64bit-Release\release\addimgthread.obj"
File "C:\Users\effi\Documents\build-Image_Organizer-Desktop_Qt_5_14_2_MSVC2017_64bit-Release\release\advancedimgsearch.obj"
File "C:\Users\effi\Documents\build-Image_Organizer-Desktop_Qt_5_14_2_MSVC2017_64bit-Release\release\BitExactImgFinder.obj"
File "C:\Users\effi\Documents\build-Image_Organizer-Desktop_Qt_5_14_2_MSVC2017_64bit-Release\release\D3Dcompiler_47.dll"
File "C:\Users\effi\Documents\build-Image_Organizer-Desktop_Qt_5_14_2_MSVC2017_64bit-Release\release\FaceDetector.obj"
File "C:\Users\effi\Documents\build-Image_Organizer-Desktop_Qt_5_14_2_MSVC2017_64bit-Release\release\FacesCropped.obj"
File "C:\Users\effi\Documents\build-Image_Organizer-Desktop_Qt_5_14_2_MSVC2017_64bit-Release\release\getfacedialog.obj"
File "C:\Users\effi\Documents\build-Image_Organizer-Desktop_Qt_5_14_2_MSVC2017_64bit-Release\release\getnumberdialog.obj"
File "C:\Users\effi\Documents\build-Image_Organizer-Desktop_Qt_5_14_2_MSVC2017_64bit-Release\release\haarcascade_eye_tree_eyeglasses.xml"
File "C:\Users\effi\Documents\build-Image_Organizer-Desktop_Qt_5_14_2_MSVC2017_64bit-Release\release\Image_Organizer.exe"
File "C:\Users\effi\Documents\build-Image_Organizer-Desktop_Qt_5_14_2_MSVC2017_64bit-Release\release\ImgFileScanner.obj"
File "C:\Users\effi\Documents\build-Image_Organizer-Desktop_Qt_5_14_2_MSVC2017_64bit-Release\release\ImgMatchFinderBase.obj"
File "C:\Users\effi\Documents\build-Image_Organizer-Desktop_Qt_5_14_2_MSVC2017_64bit-Release\release\ImgSearch.obj"
File "C:\Users\effi\Documents\build-Image_Organizer-Desktop_Qt_5_14_2_MSVC2017_64bit-Release\release\lbpcascade_frontalface_improved.xml"
File "C:\Users\effi\Documents\build-Image_Organizer-Desktop_Qt_5_14_2_MSVC2017_64bit-Release\release\libEGL.dll"
File "C:\Users\effi\Documents\build-Image_Organizer-Desktop_Qt_5_14_2_MSVC2017_64bit-Release\release\libGLESv2.dll"
File "C:\Users\effi\Documents\build-Image_Organizer-Desktop_Qt_5_14_2_MSVC2017_64bit-Release\release\main.obj"
File "C:\Users\effi\Documents\build-Image_Organizer-Desktop_Qt_5_14_2_MSVC2017_64bit-Release\release\mainwindow.obj"
File "C:\Users\effi\Documents\build-Image_Organizer-Desktop_Qt_5_14_2_MSVC2017_64bit-Release\release\moc_addimgthread.cpp"
File "C:\Users\effi\Documents\build-Image_Organizer-Desktop_Qt_5_14_2_MSVC2017_64bit-Release\release\moc_addimgthread.obj"
File "C:\Users\effi\Documents\build-Image_Organizer-Desktop_Qt_5_14_2_MSVC2017_64bit-Release\release\moc_getfacedialog.cpp"
File "C:\Users\effi\Documents\build-Image_Organizer-Desktop_Qt_5_14_2_MSVC2017_64bit-Release\release\moc_getfacedialog.obj"
File "C:\Users\effi\Documents\build-Image_Organizer-Desktop_Qt_5_14_2_MSVC2017_64bit-Release\release\moc_getnumberdialog.cpp"
File "C:\Users\effi\Documents\build-Image_Organizer-Desktop_Qt_5_14_2_MSVC2017_64bit-Release\release\moc_getnumberdialog.obj"
File "C:\Users\effi\Documents\build-Image_Organizer-Desktop_Qt_5_14_2_MSVC2017_64bit-Release\release\moc_mainwindow.cpp"
File "C:\Users\effi\Documents\build-Image_Organizer-Desktop_Qt_5_14_2_MSVC2017_64bit-Release\release\moc_mainwindow.obj"
File "C:\Users\effi\Documents\build-Image_Organizer-Desktop_Qt_5_14_2_MSVC2017_64bit-Release\release\moc_MyTreeView.cpp"
File "C:\Users\effi\Documents\build-Image_Organizer-Desktop_Qt_5_14_2_MSVC2017_64bit-Release\release\moc_MyTreeView.obj"
File "C:\Users\effi\Documents\build-Image_Organizer-Desktop_Qt_5_14_2_MSVC2017_64bit-Release\release\moc_predefs.h"
File "C:\Users\effi\Documents\build-Image_Organizer-Desktop_Qt_5_14_2_MSVC2017_64bit-Release\release\moc_scanhandler.cpp"
File "C:\Users\effi\Documents\build-Image_Organizer-Desktop_Qt_5_14_2_MSVC2017_64bit-Release\release\moc_scanhandler.obj"
File "C:\Users\effi\Documents\build-Image_Organizer-Desktop_Qt_5_14_2_MSVC2017_64bit-Release\release\moc_settingsdialog.cpp"
File "C:\Users\effi\Documents\build-Image_Organizer-Desktop_Qt_5_14_2_MSVC2017_64bit-Release\release\moc_settingsdialog.obj"
File "C:\Users\effi\Documents\build-Image_Organizer-Desktop_Qt_5_14_2_MSVC2017_64bit-Release\release\MyStandardItemModel.obj"
File "C:\Users\effi\Documents\build-Image_Organizer-Desktop_Qt_5_14_2_MSVC2017_64bit-Release\release\MyTreeView.obj"
File "C:\Users\effi\Documents\build-Image_Organizer-Desktop_Qt_5_14_2_MSVC2017_64bit-Release\release\opengl32sw.dll"
File "C:\Users\effi\Documents\build-Image_Organizer-Desktop_Qt_5_14_2_MSVC2017_64bit-Release\release\OrbMatcher.obj"
File "C:\Users\effi\Documents\build-Image_Organizer-Desktop_Qt_5_14_2_MSVC2017_64bit-Release\release\qrc_Images.cpp"
File "C:\Users\effi\Documents\build-Image_Organizer-Desktop_Qt_5_14_2_MSVC2017_64bit-Release\release\qrc_Images.obj"
File "C:\Users\effi\Documents\build-Image_Organizer-Desktop_Qt_5_14_2_MSVC2017_64bit-Release\release\Qt5Core.dll"
File "C:\Users\effi\Documents\build-Image_Organizer-Desktop_Qt_5_14_2_MSVC2017_64bit-Release\release\Qt5Gui.dll"
File "C:\Users\effi\Documents\build-Image_Organizer-Desktop_Qt_5_14_2_MSVC2017_64bit-Release\release\Qt5Svg.dll"
File "C:\Users\effi\Documents\build-Image_Organizer-Desktop_Qt_5_14_2_MSVC2017_64bit-Release\release\Qt5Widgets.dll"
File "C:\Users\effi\Documents\build-Image_Organizer-Desktop_Qt_5_14_2_MSVC2017_64bit-Release\release\scanhandler.obj"
File "C:\Users\effi\Documents\build-Image_Organizer-Desktop_Qt_5_14_2_MSVC2017_64bit-Release\release\settingsdialog.obj"
File "C:\Users\effi\Documents\build-Image_Organizer-Desktop_Qt_5_14_2_MSVC2017_64bit-Release\release\SimilarImgFinder.obj"
File "C:\Users\effi\Documents\build-Image_Organizer-Desktop_Qt_5_14_2_MSVC2017_64bit-Release\release\trained_model.yml"
File "C:\Users\effi\Documents\build-Image_Organizer-Desktop_Qt_5_14_2_MSVC2017_64bit-Release\release\training_data.csv"
File "C:\Users\effi\Documents\build-Image_Organizer-Desktop_Qt_5_14_2_MSVC2017_64bit-Release\release\user_labels.csv"
SetOutPath "$INSTDIR\translations"
File "C:\Users\effi\Documents\build-Image_Organizer-Desktop_Qt_5_14_2_MSVC2017_64bit-Release\release\translations\qt_ar.qm"
File "C:\Users\effi\Documents\build-Image_Organizer-Desktop_Qt_5_14_2_MSVC2017_64bit-Release\release\translations\qt_bg.qm"
File "C:\Users\effi\Documents\build-Image_Organizer-Desktop_Qt_5_14_2_MSVC2017_64bit-Release\release\translations\qt_ca.qm"
File "C:\Users\effi\Documents\build-Image_Organizer-Desktop_Qt_5_14_2_MSVC2017_64bit-Release\release\translations\qt_cs.qm"
File "C:\Users\effi\Documents\build-Image_Organizer-Desktop_Qt_5_14_2_MSVC2017_64bit-Release\release\translations\qt_da.qm"
File "C:\Users\effi\Documents\build-Image_Organizer-Desktop_Qt_5_14_2_MSVC2017_64bit-Release\release\translations\qt_de.qm"
File "C:\Users\effi\Documents\build-Image_Organizer-Desktop_Qt_5_14_2_MSVC2017_64bit-Release\release\translations\qt_en.qm"
File "C:\Users\effi\Documents\build-Image_Organizer-Desktop_Qt_5_14_2_MSVC2017_64bit-Release\release\translations\qt_es.qm"
File "C:\Users\effi\Documents\build-Image_Organizer-Desktop_Qt_5_14_2_MSVC2017_64bit-Release\release\translations\qt_fi.qm"
File "C:\Users\effi\Documents\build-Image_Organizer-Desktop_Qt_5_14_2_MSVC2017_64bit-Release\release\translations\qt_fr.qm"
File "C:\Users\effi\Documents\build-Image_Organizer-Desktop_Qt_5_14_2_MSVC2017_64bit-Release\release\translations\qt_gd.qm"
File "C:\Users\effi\Documents\build-Image_Organizer-Desktop_Qt_5_14_2_MSVC2017_64bit-Release\release\translations\qt_he.qm"
File "C:\Users\effi\Documents\build-Image_Organizer-Desktop_Qt_5_14_2_MSVC2017_64bit-Release\release\translations\qt_hu.qm"
File "C:\Users\effi\Documents\build-Image_Organizer-Desktop_Qt_5_14_2_MSVC2017_64bit-Release\release\translations\qt_it.qm"
File "C:\Users\effi\Documents\build-Image_Organizer-Desktop_Qt_5_14_2_MSVC2017_64bit-Release\release\translations\qt_ja.qm"
File "C:\Users\effi\Documents\build-Image_Organizer-Desktop_Qt_5_14_2_MSVC2017_64bit-Release\release\translations\qt_ko.qm"
File "C:\Users\effi\Documents\build-Image_Organizer-Desktop_Qt_5_14_2_MSVC2017_64bit-Release\release\translations\qt_lv.qm"
File "C:\Users\effi\Documents\build-Image_Organizer-Desktop_Qt_5_14_2_MSVC2017_64bit-Release\release\translations\qt_pl.qm"
File "C:\Users\effi\Documents\build-Image_Organizer-Desktop_Qt_5_14_2_MSVC2017_64bit-Release\release\translations\qt_ru.qm"
File "C:\Users\effi\Documents\build-Image_Organizer-Desktop_Qt_5_14_2_MSVC2017_64bit-Release\release\translations\qt_sk.qm"
File "C:\Users\effi\Documents\build-Image_Organizer-Desktop_Qt_5_14_2_MSVC2017_64bit-Release\release\translations\qt_uk.qm"
File "C:\Users\effi\Documents\build-Image_Organizer-Desktop_Qt_5_14_2_MSVC2017_64bit-Release\release\translations\qt_zh_TW.qm"
SetOutPath "$INSTDIR\styles"
File "C:\Users\effi\Documents\build-Image_Organizer-Desktop_Qt_5_14_2_MSVC2017_64bit-Release\release\styles\qwindowsvistastyle.dll"
SetOutPath "$INSTDIR\platforms"
File "C:\Users\effi\Documents\build-Image_Organizer-Desktop_Qt_5_14_2_MSVC2017_64bit-Release\release\platforms\qwindows.dll"
SetOutPath "$INSTDIR\imageformats"
File "C:\Users\effi\Documents\build-Image_Organizer-Desktop_Qt_5_14_2_MSVC2017_64bit-Release\release\imageformats\qgif.dll"
File "C:\Users\effi\Documents\build-Image_Organizer-Desktop_Qt_5_14_2_MSVC2017_64bit-Release\release\imageformats\qicns.dll"
File "C:\Users\effi\Documents\build-Image_Organizer-Desktop_Qt_5_14_2_MSVC2017_64bit-Release\release\imageformats\qico.dll"
File "C:\Users\effi\Documents\build-Image_Organizer-Desktop_Qt_5_14_2_MSVC2017_64bit-Release\release\imageformats\qjpeg.dll"
File "C:\Users\effi\Documents\build-Image_Organizer-Desktop_Qt_5_14_2_MSVC2017_64bit-Release\release\imageformats\qsvg.dll"
File "C:\Users\effi\Documents\build-Image_Organizer-Desktop_Qt_5_14_2_MSVC2017_64bit-Release\release\imageformats\qtga.dll"
File "C:\Users\effi\Documents\build-Image_Organizer-Desktop_Qt_5_14_2_MSVC2017_64bit-Release\release\imageformats\qtiff.dll"
File "C:\Users\effi\Documents\build-Image_Organizer-Desktop_Qt_5_14_2_MSVC2017_64bit-Release\release\imageformats\qwbmp.dll"
File "C:\Users\effi\Documents\build-Image_Organizer-Desktop_Qt_5_14_2_MSVC2017_64bit-Release\release\imageformats\qwebp.dll"
SetOutPath "$INSTDIR\iconengines"
File "C:\Users\effi\Documents\build-Image_Organizer-Desktop_Qt_5_14_2_MSVC2017_64bit-Release\release\iconengines\qsvgicon.dll"
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
CreateDirectory "$SMPROGRAMS\Image Organizer"
CreateShortCut "$SMPROGRAMS\Image Organizer\${APP_NAME}.lnk" "$INSTDIR\${MAIN_APP_EXE}"
CreateShortCut "$DESKTOP\${APP_NAME}.lnk" "$INSTDIR\${MAIN_APP_EXE}"
CreateShortCut "$SMPROGRAMS\Image Organizer\Uninstall ${APP_NAME}.lnk" "$INSTDIR\uninstall.exe"

!ifdef WEB_SITE
WriteIniStr "$INSTDIR\${APP_NAME} website.url" "InternetShortcut" "URL" "${WEB_SITE}"
CreateShortCut "$SMPROGRAMS\Image Organizer\${APP_NAME} Website.lnk" "$INSTDIR\${APP_NAME} website.url"
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
Delete "$INSTDIR\haarcascade_eye_tree_eyeglasses.xml"
Delete "$INSTDIR\Image_Organizer.exe"
Delete "$INSTDIR\ImgFileScanner.obj"
Delete "$INSTDIR\ImgMatchFinderBase.obj"
Delete "$INSTDIR\ImgSearch.obj"
Delete "$INSTDIR\lbpcascade_frontalface_improved.xml"
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
Delete "$INSTDIR\trained_model.yml"
Delete "$INSTDIR\training_data.csv"
Delete "$INSTDIR\user_labels.csv"
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
Delete "$SMPROGRAMS\Image Organizer\${APP_NAME}.lnk"
Delete "$SMPROGRAMS\Image Organizer\Uninstall ${APP_NAME}.lnk"
!ifdef WEB_SITE
Delete "$SMPROGRAMS\Image Organizer\${APP_NAME} Website.lnk"
!endif
Delete "$DESKTOP\${APP_NAME}.lnk"

RmDir "$SMPROGRAMS\Image Organizer"
!endif

DeleteRegKey ${REG_ROOT} "${REG_APP_PATH}"
DeleteRegKey ${REG_ROOT} "${UNINSTALL_PATH}"
SectionEnd

######################################################################

