# vimcdoc (http://vimcdoc.sf.net) Win32 platform installation program
# NSIS source script
# Compile this file with NSIS2!! available at http://nsis.sf.net
# Author: lang2 (lang2_at_users.sf.net)

OutFile "vimcdoc-setup.exe"

SetCompressor bzip2

# We are overwriting everything
SetOverwrite on

######
# Setup pages to be displayed
######
Page license
Page components
Page directory
Page instfiles

######
# Load the lanuage files
######
LoadLanguageFile "${NSISDIR}\Contrib\Language files\English.nlf"
LoadLanguageFile "${NSISDIR}\Contrib\Language files\SimpChinese.nlf"

#Setup license page
LicenseLangString myLicenseData ${LANG_ENGLISH} "LICENSE"
LicenseLangString myLicenseData ${LANG_SIMPCHINESE} "LICENSE"
LicenseData $(myLicenseData)

######
# Setup various language string
# The same name is used for lang string and the install attribute is the
# same, which is confusing. But works nonetheless. Note that $() is a 
# user variable.
######
#Setup name string
LangString Name ${LANG_SIMPCHINESE} "Vim 中文文档"
LangString Name ${LANG_ENGLISH} "Vim Chinese Documentation"
Name $(Name)

LangString DocsectName ${LANG_ENGLISH} "Chinese documentation"
LangString DocsectName ${LANG_SIMPCHINESE} "Vim 中文文档"

;LangString Backup ${LANG_ENGLISH} "Backup originals"
;LangString Backup ${LANG_SIMPCHINESE} "备份原文档"

LangString StartVim ${LANG_SIMPCHINESE} "安装完毕后察看中文帮助"
LangString StartVim ${LANG_ENGLISH} "View the Chinese help after installation"

LangString SetupVim ${LANG_SIMPCHINESE} "设置中文为缺省帮助语言"
LangString SetupVim ${LANG_ENGLISH} "Set Chinese as the default help language"

LangString BrandingText ${LANG_SIMPCHINESE} "http://vimcdoc.sf.net"
LangString BrandingText ${LANG_ENGLISH} "http://vimcdoc.sf.net"
BrandingText $(BrandingText)

LangString LicenseText ${LANG_SIMPCHINESE} "版权信息"
LangString LicenseText ${LANG_ENGLISH} "License agreement"
LicenseText $(LicenseText)

LangString CompletedText ${LANG_ENGLISH} "Thanks for installing vimcdoc."
LangString CompletedText ${LANG_SIMPCHINESE} "感谢使用 Vim 中文文档！"
CompletedText $(CompletedText)

LangString DirText1 ${LANG_ENGLISH}   "Please make sure that the following directory is corrrect. \
 If you are not sure, simply press 'Install'."
LangString DirText2 ${LANG_ENGLISH}  "The setup program has \
  detected that you have Vim installed in:"
LangString DirText1 ${LANG_SIMPCHINESE}    "请确认以下列出的目录。如果你不确定，请点击'安装'。"
LangString DirText2 ${LANG_SIMPCHINESE}    "安装程序检测到你的 Vim 安装在以下目录:"
DirText $(DirText1) $(DirText2)

LangString ComponentText ${LANG_SIMPCHINSE} "请选择安装选项:"
LangString ComponentText ${LANG_ENGLISH} "Please setup installation options:"
ComponentText $(ComponentText)


######
# Pre-processing
######
#Setup the INSTDIR from registery
InstallDirRegKey HKLM SOFTWARE\Vim\Gvim "path"
#InstallColors 000000 809090
InstProgressFlags smooth

UninstallText "This will uninstall vimcdoc. Hit next to continue."

ShowInstDetails show

###########
# Sections
###########
Section  !$(DocsectName)
  SectionIn RO ;This section has to be run

  ; Set the other two options to be off 
  StrCpy $R1 'no'
  StrCpy $R2 'no'

SectionEnd

#Section $(Backup) 
 #StrCpy $R0 'yes'
 #AddSize 3500
#SectionEnd

Section $(SetupVim)
 StrCpy $R2 'yes'
SectionEnd

Section $(StartVim)
 StrCpy $R1 'yes'
SectionEnd

Section - DoStuff
  SetOutPath $INSTDIR\..\vimfiles\doc
  File /r "doc\*.cnx"
  File "doc\tags-cn"
  SetOutPath $INSTDIR\..\vimfiles\syntax
  File "syntax\help_cn.vim"
  StrCmp $R2 'yes' 0 +3
    SetOutPath $INSTDIR\..\vimfiles\plugin
    File "plugin\vimcdoc.vim"
  SetOutPath $PROGRAMFILES\vimcdoc
  File "README.md"
  File "INSTALL"
  File "LICENSE"
  File "AUTHORS"
  File "guides.txt"
SectionEnd

Section "Uninstall"
  Delete $INSTDIR\*.cnx
  Delete $INSTDIR\tags-cn
  Delete $INSTDIR\..\syntax\help_cn.vim
  Delete $INSTDIR\..\plugin\vimcdoc.vim
  Delete $INSTDIR\vimcdoc-uninst.exe
  Rmdir /r $PROGRAMFILES\vimcdoc
SectionEnd


###########################
## Functions
##########################
#Function BackupOrig
  #IfFileExists $INSTDIR\doc\backup\*.* BackedUp
  #CreateDirectory $INSTDIR\doc\backup
  #CopyFiles "$INSTDIR\doc\*.cnx" "$INSTDIR\doc\backup" 4000
  #BackedUp: ; backup already. skip
#FunctionEnd

# Yes the uninstaller is not written into $PROGRAMFILES
# because I don't know how to!
Function .onInstSuccess
  WriteUninstaller $INSTDIR\..\vimfiles\doc\vimcdoc-uninst.exe
  StrCmp $R1 'yes' 0 +2 
    Exec "$INSTDIR\gvim.exe +help@cn" ; view help file in Vim
FunctionEnd

Function .onInit
	Push ${LANG_ENGLISH}
	Push English
	Push ${LANG_SIMPCHINESE}
	Push "简体中文"
	Push 2 ; 2 is the number of languages
	LangDLL::LangDialog "Installer Language" "Please select the language of the installer"

	Pop $LANGUAGE
	StrCmp $LANGUAGE "cancel" 0 +2
		Abort
FunctionEnd



; eof
