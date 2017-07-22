# -*- conf -*-

# NSIS installer script based on example2.nsi from the nsis-2.44 distribution.
# Copyright (c) 2009 Stelios Bounanos, M0GLD.
# Copyright (c) 2009 Dave Freese, W1HKJ

# substitute your application name for instances of FLIMG

# Variables
!define FLIMG_DESCRIPTION "${FLIMG_NAME} ${FLIMG_VERSION}"
!define FLIMG_STRING "${FLIMG_NAME}-${FLIMG_VERSION}"

!define PRODUCT_BINARY "${FLIMG_BINARY}"
!define PRODUCT_NAME "${FLIMG_NAME}"
!define PRODUCT_VERSION "${FLIMG_VERSION}"
!define PRODUCT_STRING "${FLIMG_STRING}"
!define PRODUCT_DESCRIPTION "${FLIMG_DESCRIPTION}"

# Compression options
SetCompressor /SOLID lzma

# This function is called before displaying the first installer page.
# It aborts the installation if the Windows version is too old.
!include WinVer.nsh
Function .onInit
    ${IfNot} ${AtLeastWin2000}
        MessageBox MB_ICONSTOP "Sorry, your Windows version is too old.$\n${PRODUCT_NAME} requires Windows 2000 or later."
	Abort
    ${EndIf}
FunctionEnd

# The name of the installer
Name "${PRODUCT_DESCRIPTION}"

# The file to write
OutFile ${INSTALLER_FILE}

# The default installation directory
InstallDir $PROGRAMFILES\${PRODUCT_STRING}

# Registry key to check for directory (so if you install again, it will
# overwrite the old one automatically)
!define INSTALL_DIR_REG_KEY SOFTWARE\${PRODUCT_STRING}
InstallDirRegKey HKLM "${INSTALL_DIR_REG_KEY}" "Install_Dir"

# Request application privileges for Windows Vista
RequestExecutionLevel admin

# License
LicenseText "${PRODUCT_NAME} is distributed under the GNU GPL as detailed \
below. You must abide by the terms of this license if you modify or \
redistribute the program." "Continue"
LicenseData "${LICENSE_FILE}"
SubCaption 0 ": License Information"

# Other options
BrandingText " "
InstProgressFlags smooth
VIAddVersionKey ProductName "${PRODUCT_NAME}"
VIAddVersionKey ProductVersion "${PRODUCT_VERSION}"
VIAddVersionKey FileVersion "${PRODUCT_VERSION}"
VIAddVersionKey FileDescription "${FLIMG_DESCRIPTION} installer"
VIAddVersionKey LegalCopyright "${PRODUCT_NAME} developers"
VIAddVersionKey OriginalFilename "${INSTALLER_FILE}"
VIProductVersion "3.0.0.0"
WindowIcon off
XPStyle on

# Installer pages
Page license
Page components
Page directory
Page instfiles
UninstPage uninstConfirm
UninstPage instfiles

# Registry uninstall path
!define REG_UNINSTALL_PATH Software\Microsoft\Windows\CurrentVersion\Uninstall\${PRODUCT_STRING}

# This is a hidden section and is always selected.  It writes the uninstall
# registry keys and uninstaller binary.
Section -install
    # Set output path to the installation directory.
    SetOutPath $INSTDIR
    # Write the installation paths into the registry
    WriteRegStr HKLM "${INSTALL_DIR_REG_KEY}" "Install_Dir" "$INSTDIR"
    # Write the uninstall keys for Windows
    WriteRegStr HKLM "${REG_UNINSTALL_PATH}" "DisplayName" "${PRODUCT_DESCRIPTION}"
    WriteRegStr HKLM "${REG_UNINSTALL_PATH}" "DisplayVersion" "${PRODUCT_VERSION}"
    WriteRegStr HKLM "${REG_UNINSTALL_PATH}" "DisplayIcon" '"$INSTDIR\${PRODUCT_BINARY}"'
    WriteRegStr HKLM "${REG_UNINSTALL_PATH}" "HelpLink" "${SUPPORT_URL}"
    WriteRegStr HKLM "${REG_UNINSTALL_PATH}" "Publisher" "FLIMG developers"
    WriteRegStr HKLM "${REG_UNINSTALL_PATH}" "URLUpdateInfo" "${UPDATES_URL}"
    WriteRegStr HKLM "${REG_UNINSTALL_PATH}" "UninstallString" '"$INSTDIR\uninstall.exe"'
    WriteRegStr HKLM "${REG_UNINSTALL_PATH}" "QuietUninstallString" '"$INSTDIR\uninstall.exe" /S'
    WriteRegDWORD HKLM "${REG_UNINSTALL_PATH}" "NoModify" 1
    WriteRegDWORD HKLM "${REG_UNINSTALL_PATH}" "NoRepair" 1
    WriteUninstaller "uninstall.exe"
SectionEnd

#Var WANT_FLIMG

Section "FLIMG"
	SectionIn RO
	SetOutPath $INSTDIR
	File "${FLIMG_BINARY}"
SectionEnd

# Start Menu path
!define SM_PATH_BASE $SMPROGRAMS\${PRODUCT_NAME}
!define SM_PATH ${SM_PATH_BASE}\${PRODUCT_STRING}

# The following sections are optional
Section "Start Menu Shortcuts"
    CreateDirectory "${SM_PATH}"
	CreateShortCut "${SM_PATH}\${FLIMG_NAME}.lnk" "$INSTDIR\${FLIMG_BINARY}" "" "$INSTDIR\${FLIMG_BINARY}" 0
    CreateShortCut "${SM_PATH}\Uninstall.lnk" "$INSTDIR\uninstall.exe" "" "$INSTDIR\uninstall.exe" 0
SectionEnd

Section "Desktop Shortcuts"
	CreateShortCut "$DESKTOP\${FLIMG_DESCRIPTION}.lnk" "$INSTDIR\${FLIMG_BINARY}" "" \
		"$INSTDIR\${FLIMG_BINARY}" 0
SectionEnd

# This is unselected by default
Section /o "Quick Launch Shortcuts"
	CreateShortCut "$QUICKLAUNCH\${FLIMG_DESCRIPTION}}.lnk" "$INSTDIR\${FLIMG_BINARY}" "" \
		"$INSTDIR\${FLIMG_BINARY}" 0
SectionEnd

# Uninstaller
Section "Uninstall"
    # Remove registry keys
    DeleteRegKey HKLM "${REG_UNINSTALL_PATH}"
    DeleteRegKey HKLM "${INSTALL_DIR_REG_KEY}"

# Remove files and uninstaller
	Delete /REBOOTOK $INSTDIR\${FLIMG_BINARY}
    Delete /REBOOTOK $INSTDIR\uninstall.exe

# Remove shortcuts, if any
    Delete "${SM_PATH}\*.*"
	Delete "$DESKTOP\${FLIMG_DESCRIPTION}.lnk"
	Delete "$QUICKLAUNCH\${FLIMG_DESCRIPTION}.lnk"

# Remove directories used
    RMDir "${SM_PATH}"
    RMDir "${SM_PATH_BASE}"
    RMDir "$INSTDIR"
SectionEnd

# Offer to reboot the machine if the reboot flag is nonzero. This flag is set by
# commands that specify the /REBOOTOK switch if the BINARY_* files were in use
# during uninstallation. Stupid Windows.
Function un.onGUIEnd
    IfRebootFlag 0 noreboot
    MessageBox MB_YESNO|MB_ICONQUESTION \
               "A reboot is required to finish removing ${PRODUCT_NAME}. Do you wish to reboot now?" IDNO noreboot
    Reboot
    noreboot:
FunctionEnd

# Tell the user if we could not reboot for some reason.
Function un.onRebootFailed
    MessageBox MB_OK|MB_ICONSTOP "Reboot failed. Please reboot manually." /SD IDOK
FunctionEnd
