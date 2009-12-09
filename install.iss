; �ű��� Inno Setup �ű��� ���ɣ�
; �йش��� Inno Setup �ű��ļ�����ϸ��������İ����ĵ���

#define MyAppName "CUGBLiner"
#define MyAppVerName "CUGBLiner"
#define MyAppPublisher "DLX"
#define MyAppURL "http://code.google.com/p/cugblinker/"
#define MyAppExeName "CUGBLinker.exe"


[Setup]
; ע: AppId��ֵΪ������ʶ��Ӧ�ó���
; ��ҪΪ������װ����ʹ����ͬ��AppIdֵ��
; (�����µ�GUID����� ����|��IDE������GUID��)
AppId={{BB217D6D-989D-48E8-8ABA-D7364032FD5A}
AppName={#MyAppName}
AppVerName={#MyAppVerName}
AppPublisher={#MyAppPublisher}
AppPublisherURL={#MyAppURL}
AppSupportURL={#MyAppURL}
AppUpdatesURL={#MyAppURL}
DefaultDirName={pf}\{#MyAppName}
DefaultGroupName={#MyAppName}
AllowNoIcons=yes
OutputDir=.
OutputBaseFilename=CUGBLinker
Compression=lzma
SolidCompression=yes
ArchitecturesInstallIn64BitMode=x64 ia64

[Languages]
Name: "chinesesimp"; MessagesFile: "compiler:Default.isl"

[Tasks]
Name: "desktopicon"; Description: "{cm:CreateDesktopIcon}"; GroupDescription: "{cm:AdditionalIcons}";
Name: "quicklaunchicon"; Description: "{cm:CreateQuickLaunchIcon}"; GroupDescription: "{cm:AdditionalIcons}"; Flags: unchecked

[Files]
Source: ".\Release\dlls\npptools.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: ".\Release\dlls\pthreadVC.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: ".\Release\dlls\drivers\npf.inf"; DestDir: "{win}\inf"; Flags: ignoreversion
; x86�汾
Source: ".\Release\CUGBLinker.exe"; DestDir: "{app}"; Flags: ignoreversion; Check: not Is64BitInstallMode
Source: ".\Release\dlls\wpcap.dll"; DestDir: "{app}"; Flags: ignoreversion; Check: not Is64BitInstallMode
Source: ".\Release\dlls\Packet.dll"; DestDir: "{app}"; Flags: ignoreversion; Check: not Is64BitInstallMode
Source: ".\Release\dlls\drivers\npf.sys"; DestDir: "{sys}\drivers"; Flags: onlyifdoesntexist; Check: not Is64BitInstallMode
; x64�汾
Source: ".\x64\Release\CUGBLinker.exe"; DestDir: "{app}"; Flags: ignoreversion; Check: Is64BitInstallMode
Source: ".\x64\Release\dlls\wpcap.dll"; DestDir: "{app}"; Flags: ignoreversion; Check: Is64BitInstallMode
Source: ".\x64\Release\dlls\Packet.dll"; DestDir: "{app}"; Flags: ignoreversion; Check: Is64BitInstallMode
Source: ".\x64\Release\dlls\drivers\npf.sys"; DestDir: "{sys}\drivers"; Flags: onlyifdoesntexist; Check: Is64BitInstallMode
; ע��: ��Ҫ���κι���ϵͳ�ļ���ʹ�á�Flags: ignoreversion��

[Icons]
Name: "{group}\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}"; WorkingDir: "{app}"
Name: "{group}\{cm:UninstallProgram,{#MyAppName}}"; Filename: "{uninstallexe}"; WorkingDir: "{app}"
Name: "{group}\�������°汾"; Filename: "{#MyAppURL}"; WorkingDir: "{app}"
Name: "{commondesktop}\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}"; Tasks: desktopicon; WorkingDir: "{app}"
Name: "{userappdata}\Microsoft\Internet Explorer\Quick Launch\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}"; Tasks: quicklaunchicon; WorkingDir: "{app}"

; ���ע�����Ϣ���Ǳ��룩���ѷ�ֹ����û�а�װ�ɹ�ʱ������ͨ��������ʽ��������
[Registry]
Root: HKLM; Subkey: "SYSTEM\CurrentControlSet\Services\NPF"; Flags: uninsdeletekey
Root: HKLM; Subkey: "SYSTEM\CurrentControlSet\Services\NPF"; ValueType: dword; ValueName:"Type"; ValueData: "1"
Root: HKLM; Subkey: "SYSTEM\CurrentControlSet\Services\NPF"; ValueType: dword; ValueName:"Start"; ValueData: "1"
Root: HKLM; Subkey: "SYSTEM\CurrentControlSet\Services\NPF"; ValueType: dword; ValueName:"ErrorControl"; ValueData: "1"
Root: HKLM; Subkey: "SYSTEM\CurrentControlSet\Services\NPF"; ValueType: expandsz; ValueName:"ImagePath"; ValueData: "system32\drivers\npf.sys"
Root: HKLM; Subkey: "SYSTEM\CurrentControlSet\Services\NPF"; ValueType: string; ValueName:"DisplayName"; ValueData: "NetGroup Packet Filter Driver"
Root: HKLM; Subkey: "SYSTEM\CurrentControlSet\Services\NPF"; ValueType: dword; ValueName:"TimestampMode"; ValueData: "0"

[Run]
Filename: "{sys}\rundll32.exe"; Parameters: "SETUPAPI.DLL,InstallHinfSection DefaultInstall 128 {win}\inf\npf.inf"; Flags: runhidden skipifdoesntexist
Filename: "{sys}\net.exe"; Parameters: "start npf"; Flags: runhidden skipifdoesntexist
Filename: "{app}\{#MyAppExeName}"; Description: "{cm:LaunchProgram,{#MyAppName}}"; Flags: nowait postinstall skipifsilent
