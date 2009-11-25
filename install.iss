; 脚本由 Inno Setup 脚本向导 生成！
; 有关创建 Inno Setup 脚本文件的详细资料请查阅帮助文档！

#define MyAppName "CUGBLiner"
#define MyAppVerName "CUGBLiner"
#define MyAppPublisher "DLX"
#define MyAppURL "http://code.google.com/p/cugblinker/"
#define MyAppExeName "CUGBLinker.exe"

[Setup]
; 注: AppId的值为单独标识该应用程序。
; 不要为其他安装程序使用相同的AppId值。
; (生成新的GUID，点击 工具|在IDE中生成GUID。)
AppId={{26F0F21B-FEBC-4635-9305-9A0E9E8D88D3}
AppName={#MyAppName}
AppVerName={#MyAppVerName}
AppPublisher={#MyAppPublisher}
AppPublisherURL={#MyAppURL}
AppSupportURL={#MyAppURL}
AppUpdatesURL={#MyAppURL}
DefaultDirName={pf}\{#MyAppName}
DefaultGroupName={#MyAppName}
AllowNoIcons=yes
OutputDir=C:\Documents and Settings\Administrator\桌面
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
Source: "E:\My Documents\Visual Studio 2008\Projects\CUGBLinker\Release\CUGBLinker.xml"; DestDir: "{app}"; Flags: ignoreversion
Source: "C:\WINDOWS\system32\wpcap.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "C:\WINDOWS\system32\Packet.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "C:\WINDOWS\system32\npptools.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "C:\WINDOWS\system32\drivers\npf.sys"; DestDir: "C:\WINDOWS\system32\drivers"; Flags: ignoreversion
; 注意: 不要在任何共享系统文件上使用“Flags: ignoreversion”

[Icons]
Name: "{group}\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}"
Name: "{group}\{cm:UninstallProgram,{#MyAppName}}"; Filename: "{uninstallexe}"
Name: "{commondesktop}\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}"; Tasks: desktopicon
Name: "{userappdata}\Microsoft\Internet Explorer\Quick Launch\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}"; Tasks: quicklaunchicon

[Run]
Filename: "{app}\{#MyAppExeName}"; Description: "{cm:LaunchProgram,{#MyAppName}}"; Flags: nowait postinstall skipifsilent

