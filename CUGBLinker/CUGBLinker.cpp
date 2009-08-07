// CUGBLinker.cpp : ����Ӧ�ó��������Ϊ��
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


// CCUGBLinkerApp ����

CCUGBLinkerApp::CCUGBLinkerApp()
: curAccountNum(0)
{
	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� CCUGBLinkerApp ����

CCUGBLinkerApp theApp;


//��ӵı�ʶֻ����һ�ε�������
CString g_szPropName = L"CUGBLinker";
HANDLE	g_hValue = (HANDLE)520;

//���һ��ö�ٴ��ڵĺ���
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


// CCUGBLinkerApp ��ʼ��

BOOL CCUGBLinkerApp::InitInstance()
{
	// ֻ��ͬʱ����һ��ʵ��

	//�����Ƿ��б������ǰһ��ʵ������
	HWND oldHWnd = NULL;
	EnumWindows(EnumWndProc,(LPARAM)&oldHWnd);	//ö���������еĴ���
	if(oldHWnd != NULL)
	{
		::ShowWindow(oldHWnd,SW_SHOWNORMAL);	//�����ҵ���ǰһ������
		::SetForegroundWindow(oldHWnd);			//������Ϊǰ������
		return false;							//�˳���������
	}



	// ���һ�������� Windows XP �ϵ�Ӧ�ó����嵥ָ��Ҫ
	// ʹ�� ComCtl32.dll �汾 6 ����߰汾�����ÿ��ӻ���ʽ��
	//����Ҫ InitCommonControlsEx()�����򣬽��޷��������ڡ�
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// ��������Ϊ��������Ҫ��Ӧ�ó�����ʹ�õ�
	// �����ؼ��ࡣ
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();

	if (!AfxSocketInit())
	{
		AfxMessageBox(IDP_SOCKETS_INIT_FAILED);
		return FALSE;
	}

	AfxEnableControlContainer();

	// ��׼��ʼ��
	// ���δʹ����Щ���ܲ�ϣ����С
	// ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
	// ����Ҫ���ض���ʼ������
	// �������ڴ洢���õ�ע�����
	// TODO: Ӧ�ʵ��޸ĸ��ַ�����
	// �����޸�Ϊ��˾����֯��
	SetRegistryKey(_T("CUGBLinker"));

	CCUGBLinkerDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: �ڴ˴����ô����ʱ�á�ȷ�������ر�
		//  �Ի���Ĵ���
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: �ڴ˷��ô����ʱ�á�ȡ�������ر�
		//  �Ի���Ĵ���
	}

	// ���ڶԻ����ѹرգ����Խ����� FALSE �Ա��˳�Ӧ�ó���
	//  ����������Ӧ�ó������Ϣ�á�
	return FALSE;
}

BOOL CCUGBLinkerApp::PreTranslateMessage(MSG* pMsg)
{
	// TODO: �ڴ����ר�ô����/����û���
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

