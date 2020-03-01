; Script generated by the HM NIS Edit Script Wizard.

; HM NIS Edit Wizard helper defines
!define PRODUCT_NAME "启程输入法"
!define PRODUCT_VERSION "3.0"
!define PRODUCT_PUBLISHER "启程软件"
!define PRODUCT_WEB_SITE "http://soime.cn"
!define PRODUCT_DIR_REGKEY "Software\Microsoft\Windows\CurrentVersion\App Paths\makensis.exe"
!define PRODUCT_UNINST_KEY "Software\Microsoft\Windows\CurrentVersion\Uninstall\${PRODUCT_NAME}"
!define PRODUCT_UNINST_ROOT_KEY "HKLM"

; MUI 1.67 compatible ------
!include "MUI.nsh"

; MUI Settings
!define MUI_ABORTWARNING
!define MUI_ICON "sinstar3.ICO"
!define MUI_UNICON "${NSISDIR}\Contrib\Graphics\Icons\modern-uninstall.ico"

SetPluginUnload alwaysoff
Var /GLOBAL bUpdate


; Welcome page
!insertmacro MUI_PAGE_WELCOME
; License page
!insertmacro MUI_PAGE_LICENSE "License.rtf"
; Components page
!define MUI_PAGE_HEADER_TEXT "组件选择"
!insertmacro MUI_PAGE_COMPONENTS
; Directory page
!insertmacro MUI_PAGE_DIRECTORY
; Instfiles page
!insertmacro MUI_PAGE_INSTFILES
; Finish page
!define MUI_FINISHPAGE_RUN "$INSTDIR\使用说明.txt"
!insertmacro MUI_PAGE_FINISH

; Uninstaller pages
!insertmacro MUI_UNPAGE_INSTFILES

; Language files
!insertmacro MUI_LANGUAGE "SimpChinese"

; MUI end ------

Name "${PRODUCT_NAME} ${PRODUCT_VERSION}"
OutFile "Setup.exe"
InstallDir "$PROGRAMFILES\sinstar3"
InstallDirRegKey HKLM "${PRODUCT_DIR_REGKEY}" ""
ShowInstDetails show
ShowUnInstDetails show

Section "核心程序" SEC_CORE
  SectionIn RO
  SetOutPath "$INSTDIR"
  SetOverwrite ifnewer
  
  File /r "register.exe"
  File /r "RegisterCore.dll"
  File /r "license.rtf"
  File /r "使用说明.txt"
  File /r "license.rtf"
  SetOutPath "$INSTDIR\program"
  ;File /r "program\*.*"
  SetOutPath "$INSTDIR\defskin"
  ;File /r "defskin\*.*"
  SetOutPath "$INSTDIR\sound"
  ;File /r "sound\*.*"
  SetOutPath "$INSTDIR\data"
  ;File /r "data\*.*"

  SetOutPath "$INSTDIR\server"
  ;File /r "server\blur.ini"
  ;File /r "server\config.ini"
  ;File /r "server\default.spl"
  ;File /r "server\en-ch.flm"
  ;File /r "server\line.dat"
  ;File /r "server\spell.dat"
  ;File /r "server\spell.pit"
  ;File /r "server\symbol.txt"
  ;File /r "server\usercmd.ud"
  ;File /r "server\userdef.ud"
  ;File /r "server\wordrate.dat"
SectionEnd

Section "扩展皮肤" SEC_SKIN
SectionEnd
Section "辅助工具" SEC_TOOLS
SectionEnd
SectionGroup /e "!编码方案" SEC_COMP
Section "五笔86" COMP_WB86
SectionIn RO
SectionEnd
Section "五笔98" COMP_WB98
SectionEnd
Section "五笔2000" COMP_WB2k
SectionEnd
Section "表形码26" COMP_BXM26
SectionEnd
Section "表形码31" COMP_BXM31
SectionEnd
Section "郑码6.6" COMP_ZM66
SectionEnd
Section "权氏两笔" COMP_QS2B
SectionEnd

SectionGroupEnd


Section -AdditionalIcons
  WriteIniStr "$INSTDIR\${PRODUCT_NAME}.url" "InternetShortcut" "URL" "${PRODUCT_WEB_SITE}"
  CreateShortCut "$SMPROGRAMS\启程输入法\Website.lnk" "$INSTDIR\${PRODUCT_NAME}.url"
  CreateShortCut "$SMPROGRAMS\启程输入法\Uninstall.lnk" "$INSTDIR\uninst.exe"
SectionEnd

Section -Post
  SetPluginUnload manual
  System::Free 0
  
  WriteUninstaller "$INSTDIR\uninst.exe"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "DisplayName" "$(^Name)"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "UninstallString" "$INSTDIR\uninst.exe"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "DisplayIcon" "$INSTDIR\makensis.exe"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "DisplayVersion" "${PRODUCT_VERSION}"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "URLInfoAbout" "${PRODUCT_WEB_SITE}"
  WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "Publisher" "${PRODUCT_PUBLISHER}"
  
SectionEnd

; Section descriptions
!insertmacro MUI_FUNCTION_DESCRIPTION_BEGIN
  !insertmacro MUI_DESCRIPTION_TEXT ${SEC_CORE} "启程输入法核心文件。"
  !insertmacro MUI_DESCRIPTION_TEXT ${SEC_COMP} "输入法码表"
  !insertmacro MUI_DESCRIPTION_TEXT ${COMP_WB86} "五笔字型86版"
  !insertmacro MUI_DESCRIPTION_TEXT ${COMP_WB98} "五笔字型98版"
  !insertmacro MUI_DESCRIPTION_TEXT ${COMP_WB2K} "五笔字型2000版"
  !insertmacro MUI_DESCRIPTION_TEXT ${COMP_BXM26} "表型码26键版本"
  !insertmacro MUI_DESCRIPTION_TEXT ${COMP_BXM31} "表型码31键版本"
  !insertmacro MUI_DESCRIPTION_TEXT ${COMP_ZM66} "郑码6.6版本"
  !insertmacro MUI_DESCRIPTION_TEXT ${COMP_QS2B} "权氏两笔"
  !insertmacro MUI_DESCRIPTION_TEXT ${SEC_SKIN} "扩展皮肤，美化界面。"
  !insertmacro MUI_DESCRIPTION_TEXT ${SEC_TOOLS} "包含码表编辑器，词库编辑器"
!insertmacro MUI_FUNCTION_DESCRIPTION_END

Function .onInit
   InitPluginsDir
   SetOutPath $PLUGINSDIR
   ;File RegisterCore.dll
   ;System::Call '$PLUGINSDIR\Register::Sinstar_GetCurrentVer2(*i,*i,*i,*i) i (r0r0,r1r1,r2r2,r3r3) .r4'
   ;IntCmp $4 1 0 Exit
   ;MessageBox MB_OK|MB_ICONSTOP  "Current Ver $0.$1.$2.$3 。$\r$\n$\r$\n点击 “确定” 退出安装程序。" IDOK Exit
   System::Call '$PLUGINSDIR\RegisterCore::Sinstar_IsRunning()i.R0'
   IntCmp $R0 1 0 no_run
   MessageBox MB_OK|MB_ICONSTOP  "安装程序检测到 ${PRODUCT_NAME} 正在运行。$\r$\n$\r$\n点击 “确定” 退出安装程序。" IDOK Exit
   Exit:
   Quit
   no_run:
   
FunctionEnd

Function un.onUninstSuccess
  HideWindow
  MessageBox MB_ICONINFORMATION|MB_OK "$(^Name) 已成功地从你的计算机移除。"
FunctionEnd

Function un.onInit
  MessageBox MB_ICONQUESTION|MB_YESNO|MB_DEFBUTTON2 "你确实要完全移除 $(^Name) ，其及所有的组件？" IDYES +2
  Abort
FunctionEnd

Section Uninstall
  Delete "$INSTDIR\${PRODUCT_NAME}.url"
  Delete "$INSTDIR\uninst.exe"
  Delete "$INSTDIR\License.txt"
  Delete "$INSTDIR\makensis.exe"

  Delete "$SMPROGRAMS\启程输入法\Uninstall.lnk"
  Delete "$SMPROGRAMS\启程输入法\Website.lnk"
  RMDir "$SMPROGRAMS\启程输入法"
  RMDir "$INSTDIR"

  DeleteRegKey ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}"
  DeleteRegKey HKLM "${PRODUCT_DIR_REGKEY}"
  SetAutoClose true
SectionEnd
