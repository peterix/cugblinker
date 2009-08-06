// CUGBLinkerDlg.cpp : 实现文件
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


// CCUGBLinkerDlg 对话框




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


// CCUGBLinkerDlg 消息处理程序

BOOL CCUGBLinkerDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	
	// 添加连接界面
	m_sheet.AddPage(&m_linkerPage);
	// 添加流量统计界面
	//m_sheet.AddPage(&m_trafficPage);

	m_sheet.Create(this, WS_CHILD | WS_VISIBLE, WS_EX_CONTROLPARENT);
	//调整TabControl大小
	//需进一步调整
	const int margin=10;
	CRect frameRect,m_sheetRect;
	GetClientRect(&frameRect);
	frameRect.DeflateRect(margin,margin);
	m_sheet.MoveWindow(frameRect);
	m_sheet.GetClientRect(&m_sheetRect);
	m_sheet.GetTabControl()->MoveWindow(m_sheetRect);
	m_sheet.SetActivePage(0);

	// 设置托盘图标
	nid.cbSize=(DWORD)sizeof(NOTIFYICONDATA); 
	nid.hWnd=this->m_hWnd; 
	nid.uID=IDR_MAINFRAME; 
	nid.uFlags=NIF_ICON|NIF_MESSAGE|NIF_TIP ; 
	nid.uCallbackMessage=WM_SHOWTASK;//自定义的消息名称 
	nid.hIcon=LoadIcon(AfxGetInstanceHandle(),MAKEINTRESOURCE(IDR_MAINFRAME)); 
	swprintf(nid.szTip,L"CUGBLinker");
	Shell_NotifyIcon(NIM_ADD,&nid);//在托盘区添加图标 

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CCUGBLinkerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标显示。
//
HCURSOR CCUGBLinkerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CCUGBLinkerDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	if (nID==SC_MINIMIZE /*|| SC_CLOSE*/) 
	{ 
		ShowWindow(SW_HIDE);//隐藏主窗口 
		return;
	}

	CDialog::OnSysCommand(nID, lParam);
}

LRESULT CCUGBLinkerDlg::OnShowTask(WPARAM wParam,LPARAM lParam) 
//wParam接收的是图标的ID，而lParam接收的是鼠标的行为 
{ 
	if(wParam!=IDR_MAINFRAME) 
		return 1; 
	switch(lParam) 
	{ 
	case WM_RBUTTONUP://右键起来时弹出快捷菜单，这里只有一个“关闭” 
		{
			LPPOINT lpoint=new tagPOINT; 
			::GetCursorPos(lpoint);//得到鼠标位置 
			CMenu menu; 
			menu.CreatePopupMenu();//声明一个弹出式菜单 
			menu.AppendMenu(MF_STRING,WM_SHOWME,L"显示/隐藏(&S)");
			menu.AppendMenu(MF_SEPARATOR); 
			menu.AppendMenu(MF_STRING,WM_CONNECT,L"连接网络(&C)"); 
			menu.AppendMenu(MF_STRING,WM_DISCONNECT,L"断开网络(&D)");
			menu.AppendMenu(MF_STRING,WM_DISCONNECTALL,L"断开全部连接(&A)");
			menu.AppendMenu(MF_SEPARATOR); 
			menu.AppendMenu(MF_STRING,WM_KILLME,L"退出(&X)"); 
			//确定弹出式菜单的位置 
			//menu.TrackPopupMenu(TPM_LEFTALIGN,lpoint->x,lpoint->y,this); 
			this->SetForegroundWindow();
			int ret=menu.TrackPopupMenu(TPM_RETURNCMD|TPM_LEFTALIGN|TPM_HORIZONTAL,lpoint->x,lpoint->y,this,NULL);
			int dis=0;// 用于标识断开还是断开全部

			switch(ret)
			{
			case WM_SHOWME:
				if (IsWindowVisible())
				{
					ShowWindow(SW_HIDE);
				}
				else
				{
					ShowWindow(SW_SHOW);//简单的显示主窗口完事儿 
					ShowWindow(SW_SHOWNORMAL); //可以避免原来的最小化
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

			//资源回收 
			HMENU hmenu=menu.Detach(); 
			menu.DestroyMenu(); 
			delete lpoint; 
		} 
		break; 
	case WM_LBUTTONDBLCLK://双击左键的处理 
		{
			if (IsWindowVisible())
			{
				ShowWindow(SW_HIDE);
			}
			else
			{
			ShowWindow(SW_SHOW);//简单的显示主窗口完事儿 
			ShowWindow(SW_SHOWNORMAL); //可以避免原来的最小化
			}
		} 
		break; 
	} 
	return 0; 
}

void CCUGBLinkerDlg::OnClose()
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	Shell_NotifyIcon(NIM_DELETE,&nid);//删除托盘区图标
	CDialog::OnClose();
}
