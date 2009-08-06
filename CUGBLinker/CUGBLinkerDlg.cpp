// CUGBLinkerDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "CUGBLinker.h"
#include "CUGBLinkerDlg.h"
#include "global.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define WM_SHOWTASK WM_USER+55
#define WM_SHOWME WM_USER+101
#define WM_KILLME WM_USER+102
#define WM_CONNECT WM_USER+103
#define WM_DISCONNECT WM_USER+104
#define WM_DISCONNECTALL WM_USER+105


// CCUGBLinkerDlg �Ի���




CCUGBLinkerDlg::CCUGBLinkerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCUGBLinkerDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCUGBLinkerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CCUGBLinkerDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_MESSAGE(WM_SHOWTASK,OnShowTask)
	ON_WM_SYSCOMMAND()
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CCUGBLinkerDlg ��Ϣ�������

BOOL CCUGBLinkerDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	
	// ������ӽ���
	m_sheet.AddPage(&m_linkerPage);
	// �������ͳ�ƽ���
	//m_sheet.AddPage(&m_trafficPage);

	m_sheet.Create(this, WS_CHILD | WS_VISIBLE, WS_EX_CONTROLPARENT);
	//����TabControl��С
	//���һ������
	const int margin=10;
	CRect frameRect,m_sheetRect;
	GetClientRect(&frameRect);
	frameRect.DeflateRect(margin,margin);
	m_sheet.MoveWindow(frameRect);
	m_sheet.GetClientRect(&m_sheetRect);
	m_sheet.GetTabControl()->MoveWindow(m_sheetRect);
	m_sheet.SetActivePage(0);

	// ��������ͼ��
	nid.cbSize=(DWORD)sizeof(NOTIFYICONDATA); 
	nid.hWnd=this->m_hWnd; 
	nid.uID=IDR_MAINFRAME; 
	nid.uFlags=NIF_ICON|NIF_MESSAGE|NIF_TIP ; 
	nid.uCallbackMessage=WM_SHOWTASK;//�Զ������Ϣ���� 
	nid.hIcon=LoadIcon(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDR_MAINFRAME)); 
	swprintf(nid.szTip,L"CUGBLinker");
	Shell_NotifyIcon(NIM_ADD,&nid);//�����������ͼ�� 

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CCUGBLinkerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ��������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù����ʾ��
//
HCURSOR CCUGBLinkerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CCUGBLinkerDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if (nID==SC_MINIMIZE /*|| SC_CLOSE*/) 
	{ 
		ShowWindow(SW_HIDE);//���������� 
		return;
	}

	CDialog::OnSysCommand(nID, lParam);
}

LRESULT CCUGBLinkerDlg::OnShowTask(WPARAM wParam,LPARAM lParam) 
//wParam���յ���ͼ���ID����lParam���յ���������Ϊ 
{ 
	if(wParam!=IDR_MAINFRAME) 
		return 1; 
	switch(lParam) 
	{ 
	case WM_RBUTTONUP://�Ҽ�����ʱ������ݲ˵�������ֻ��һ�����رա� 
		{
			LPPOINT lpoint=new tagPOINT; 
			::GetCursorPos(lpoint);//�õ����λ�� 
			CMenu menu; 
			menu.CreatePopupMenu();//����һ������ʽ�˵� 
			menu.AppendMenu(MF_STRING,WM_SHOWME,L"��ʾ/����(&S)");
			menu.AppendMenu(MF_SEPARATOR); 
			menu.AppendMenu(MF_STRING,WM_CONNECT,L"��������(&C)"); 
			menu.AppendMenu(MF_STRING,WM_DISCONNECT,L"�Ͽ�����(&D)");
			menu.AppendMenu(MF_STRING,WM_DISCONNECTALL,L"�Ͽ�ȫ������(&A)");
			menu.AppendMenu(MF_SEPARATOR); 
			menu.AppendMenu(MF_STRING,WM_KILLME,L"�˳�(&X)"); 
			//ȷ������ʽ�˵���λ�� 
			//menu.TrackPopupMenu(TPM_LEFTALIGN,lpoint->x,lpoint->y,this); 
			this->SetForegroundWindow();
			int ret=menu.TrackPopupMenu(TPM_RETURNCMD|TPM_LEFTALIGN|TPM_HORIZONTAL,lpoint->x,lpoint->y,this,NULL);
			int dis=0;// ���ڱ�ʶ�Ͽ����ǶϿ�ȫ��

			switch(ret)
			{
			case WM_SHOWME:
				if (IsWindowVisible())
				{
					ShowWindow(SW_HIDE);
				}
				else
				{
					ShowWindow(SW_SHOW);//�򵥵���ʾ���������¶� 
					ShowWindow(SW_SHOWNORMAL); //���Ա���ԭ������С��
				}
				break;
			case WM_KILLME:
				SendMessage(WM_CLOSE);
				break;
			case WM_CONNECT:
				AfxBeginThread(Connect, NULL);
				break;
			case WM_DISCONNECT:
				dis=0;
				AfxBeginThread(DisConnect, &dis);
				break;
			case WM_DISCONNECTALL:
				dis=1;
				AfxBeginThread(DisConnect, &dis);
				break;
			}

			//��Դ���� 
			HMENU hmenu=menu.Detach(); 
			menu.DestroyMenu(); 
			delete lpoint; 
		} 
		break; 
	case WM_LBUTTONDBLCLK://˫������Ĵ��� 
		{
			if (IsWindowVisible())
			{
				ShowWindow(SW_HIDE);
			}
			else
			{
			ShowWindow(SW_SHOW);//�򵥵���ʾ���������¶� 
			ShowWindow(SW_SHOWNORMAL); //���Ա���ԭ������С��
			}
		} 
		break; 
	} 
	return 0; 
}

void CCUGBLinkerDlg::OnClose()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	Shell_NotifyIcon(NIM_DELETE,&nid);//ɾ��������ͼ��
	CDialog::OnClose();
}
