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
OutputDir=C:\Documents and Settings\Administrator\����
OutputBaseFilename=CUGBLinker
;SetupIconFile=E:\My Documents\Visual Studio 2008\Projects\CUGBLinker\CUGBLinker\res\CUGBLinker.ico
Compression=lzma
SolidCompression=yes

[Languages]
Name: "chinesesimp"; MessagesFile: "compiler:Default.isl"

[Tasks]
Name: "desktopicon"; Description: "{cm:CreateDesktopIcon}"; GroupDescription: "{cm:AdditionalIcons}";
Name: "quicklaunchicon"; Description: "{cm:CreateQuickLaunchIcon}"; GroupDescription: "{cm:AdditionalIcons}"; Flags: unchecked

[Files]
Source: "E:\My Documents\Visual Studio 2008\Projects\CUGBLinker\Release\CUGBLinker.exe"; DestDir: "{app}"; Flags: ignoreversion
Source: "C:\WINDOWS\system32\wpcap.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "C:\WINDOWS\system32\Packet.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "C:\WINDOWS\system32\npptools.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "C:\WINDOWS\system32\pthreadVC.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "C:\WINDOWS\system32\drivers\npf.sys"; DestDir: "{sys}\drivers"; Flags: onlyifdoesntexist
; ע��: ��Ҫ���κι���ϵͳ�ļ���ʹ�á�Flags: ignoreversion��

[Icons]
Name: "{group}\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}"; WorkingDir: "{app}"
Name: "{group}\{cm:UninstallProgram,{#MyAppName}}"; Filename: "{uninstallexe}"; WorkingDir: "{app}"
Name: "{commondesktop}\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}"; Tasks: desktopicon; WorkingDir: "{app}"
Name: "{userappdata}\Microsoft\Internet Explorer\Quick Launch\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}"; Tasks: quicklaunchicon; WorkingDir: "{app}"

[Registry]
Root: HKLM; Subkey: "SYSTEM\CurrentControlSet\Services\NPF"; Flags: uninsdeletekey
Root: HKLM; Subkey: "SYSTEM\CurrentControlSet\Services\NPF"; ValueType: dword; ValueName:"Type"; ValueData: "1"
Root: HKLM; Subkey: "SYSTEM\CurrentControlSet\Services\NPF"; ValueType: dword; ValueName:"Start"; ValueData: "1"
Root: HKLM; Subkey: "SYSTEM\CurrentControlSet\Services\NPF"; ValueType: dword; ValueName:"ErrorControl"; ValueData: "1"
Root: HKLM; Subkey: "SYSTEM\CurrentControlSet\Services\NPF"; ValueType: expandsz; ValueName:"ImagePath"; ValueData: "system32\drivers\npf.sys"
Root: HKLM; Subkey: "SYSTEM\CurrentControlSet\Services\NPF"; ValueType: string; ValueName:"DisplayName"; ValueData: "NetGroup Packet Filter Driver"
Root: HKLM; Subkey: "SYSTEM\CurrentControlSet\Services\NPF"; ValueType: dword; ValueName:"TimestampMode"; ValueData: "0"

[Run]
Filename: "{app}\{#MyAppExeName}"; Description: "{cm:LaunchProgram,{#MyAppName}}"; Flags: nowait postinstall skipifsilent

