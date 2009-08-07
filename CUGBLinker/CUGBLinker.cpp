// CUGBLinker.cpp : 定义应用程序的类行为。
//

#include "stdafx.h"
#include "CUGBLinker.h"
#include "CUGBLinkerDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CCUGBLinkerApp

BEGIN_MESSAGE_MAP(CCUGBLinkerApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CCUGBLinkerApp 构造

CCUGBLinkerApp::CCUGBLinkerApp()
: curAccountNum(0)
{
	// TODO: 在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
}


// 唯一的一个 CCUGBLinkerApp 对象

CCUGBLinkerApp theApp;


//添加的标识只运行一次的属性名
CString g_szPropName = L"CUGBLinker";
HANDLE	g_hValue = (HANDLE)520;

//添加一个枚举窗口的函数
BOOL CALLBACK EnumWndProc(HWND hwnd,LPARAM lParam)
{
	HANDLE h = GetProp(hwnd,g_szPropName);
	if( h == g_hValue)
	{
		*(HWND*)lParam = hwnd;
		return false;
	}

	return true;
}


// CCUGBLinkerApp 初始化

BOOL CCUGBLinkerApp::InitInstance()
{
	// 只能同时运行一个实例

	//查找是否有本程序的前一个实例运行
	HWND oldHWnd = NULL;
	EnumWindows(EnumWndProc,(LPARAM)&oldHWnd);	//枚举所有运行的窗口
	if(oldHWnd != NULL)
	{
		::ShowWindow(oldHWnd,SW_SHOWNORMAL);	//激活找到的前一个程序
		::SetForegroundWindow(oldHWnd);			//把它设为前景窗口
		return false;							//退出本次运行
	}



	// 如果一个运行在 Windows XP 上的应用程序清单指定要
	// 使用 ComCtl32.dll 版本 6 或更高版本来启用可视化方式，
	//则需要 InitCommonControlsEx()。否则，将无法创建窗口。
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// 将它设置为包括所有要在应用程序中使用的
	// 公共控件类。
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();

	if (!AfxSocketInit())
	{
		AfxMessageBox(IDP_SOCKETS_INIT_FAILED);
		return FALSE;
	}

	AfxEnableControlContainer();

	// 标准初始化
	// 如果未使用这些功能并希望减小
	// 最终可执行文件的大小，则应移除下列
	// 不需要的特定初始化例程
	// 更改用于存储设置的注册表项
	// TODO: 应适当修改该字符串，
	// 例如修改为公司或组织名
	SetRegistryKey(_T("CUGBLinker"));

	CCUGBLinkerDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: 在此处放置处理何时用“确定”来关闭
		//  对话框的代码
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: 在此放置处理何时用“取消”来关闭
		//  对话框的代码
	}

	// 由于对话框已关闭，所以将返回 FALSE 以便退出应用程序，
	//  而不是启动应用程序的消息泵。
	return FALSE;
}

BOOL CCUGBLinkerApp::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	if( pMsg->message == WM_KEYDOWN )
	{
		if (pMsg->wParam == VK_ESCAPE)
		{
			ShowWindow(m_pMainWnd->m_hWnd, SW_HIDE); 
			return true;
		}
	}

	return CWinApp::PreTranslateMessage(pMsg);
}

