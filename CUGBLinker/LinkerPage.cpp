// LinkerPage.cpp : 实现文件
//

#include "stdafx.h"
#include "CUGBLinker.h"
#include "LinkerPage.h"
#include "AccountInfo.h"
#include "AccountDlg.h"
#include "global.h"


// CLinkerPage 对话框

IMPLEMENT_DYNAMIC(CLinkerPage, CPropertyPage)

CLinkerPage::CLinkerPage()
: CPropertyPage(CLinkerPage::IDD)
, m_dis(0)
{

}

CLinkerPage::~CLinkerPage()
{
}

void CLinkerPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_ID, m_lblID);
	DDX_Control(pDX, IDC_COMBO_ID, m_cboID);
	DDX_Control(pDX, IDC_EDIT_PWD, m_txtPwd);
	DDX_Control(pDX, IDC_CHECK_SAVEPWD, m_chkSavePwd);
	DDX_Control(pDX, IDC_CONNECTINFO, m_txtInfo);
	DDX_Control(pDX, IDC_RADIO_IN, m_rdoRangeIn);
	DDX_Control(pDX, IDC_RADIO_OUT, m_rdoRangeOut);
	DDX_Control(pDX, IDC_CHECK_AUTOCON, m_chkAutoCon);
	DDX_Control(pDX, IDC_CHECK_WITHSYS, m_chkAutoStart);
	DDX_Control(pDX, IDC_BUTTON_CON, m_btnConnect);
	DDX_Control(pDX, IDC_BUTTON_DISCON, m_btnDisCon);
	DDX_CBString(pDX, IDC_COMBO_ID, theApp.curAccount.m_username);
	DDX_Text(pDX, IDC_EDIT_PWD, theApp.curAccount.m_password);
	DDX_Check(pDX, IDC_CHECK_SAVEPWD, theApp.curAccount.m_savePwd);
	DDX_Radio(pDX, IDC_RADIO_IN, theApp.curAccount.m_range);
}


BEGIN_MESSAGE_MAP(CLinkerPage, CPropertyPage)
	ON_STN_CLICKED(IDC_STATIC_ID, &CLinkerPage::OnStnClickedStaticId)
	ON_BN_CLICKED(IDC_BUTTON_CON, &CLinkerPage::OnBnClickedButtonCon)
	ON_BN_CLICKED(IDC_BUTTON_DISCON, &CLinkerPage::OnBnClickedButtonDiscon)
	ON_CBN_EDITCHANGE(IDC_COMBO_ID, &CLinkerPage::OnCbnEditchangeComboId)
	ON_CBN_SELCHANGE(IDC_COMBO_ID, &CLinkerPage::OnCbnSelchangeComboId)
	ON_EN_CHANGE(IDC_EDIT_PWD, &CLinkerPage::OnEnChangeEditPwd)
	ON_COMMAND(ID_DISCON, &CLinkerPage::OnMenuDiscon)
	ON_COMMAND(ID_DISCONALL, &CLinkerPage::OnMenuDisconAll)
	ON_UPDATE_COMMAND_UI(ID_DISCON, &CLinkerPage::OnUpdateDiscon)
	ON_UPDATE_COMMAND_UI(ID_DISCONALL, &CLinkerPage::OnUpdateDisconall)
	ON_WM_INITMENUPOPUP()
END_MESSAGE_MAP()


// CLinkerPage 消息处理程序

void CLinkerPage::OnInitMenuPopup(CMenu* pPopupMenu, UINT nIndex, BOOL bSysMenu)
{
	CPropertyPage::OnInitMenuPopup(pPopupMenu, nIndex, bSysMenu);

	// TODO: 在此处添加消息处理程序代码
	ASSERT(pPopupMenu != NULL); 
	// Check the enabled state of various menu items. 

	CCmdUI state; 
	state.m_pMenu = pPopupMenu; 
	ASSERT(state.m_pOther == NULL); 
	ASSERT(state.m_pParentMenu == NULL); 

	// Determine if menu is popup in top-level menu and set m_pOther to 
	// it if so (m_pParentMenu == NULL indicates that it is secondary popup). 
	HMENU hParentMenu; 
	if (AfxGetThreadState()->m_hTrackingMenu == pPopupMenu->m_hMenu) 
		state.m_pParentMenu = pPopupMenu; // Parent == child for tracking popup. 
	else if ((hParentMenu = ::GetMenu(m_hWnd)) != NULL) 
	{ 
		CWnd* pParent = this; 
		// Child windows don't have menus--need to go to the top! 
		if (pParent != NULL && 
			(hParentMenu = ::GetMenu(pParent->m_hWnd)) != NULL) 
		{ 
			int nIndexMax = ::GetMenuItemCount(hParentMenu); 
			for (int nIndex = 0; nIndex < nIndexMax; nIndex++) 
			{ 
				if (::GetSubMenu(hParentMenu, nIndex) == pPopupMenu->m_hMenu) 
				{ 
					// When popup is found, m_pParentMenu is containing menu. 
					state.m_pParentMenu = CMenu::FromHandle(hParentMenu); 
					break; 
				} 
			} 
		} 
	} 

	state.m_nIndexMax = pPopupMenu->GetMenuItemCount(); 
	for (state.m_nIndex = 0; state.m_nIndex < state.m_nIndexMax; 
		state.m_nIndex++) 
	{ 
		state.m_nID = pPopupMenu->GetMenuItemID(state.m_nIndex); 
		if (state.m_nID == 0) 
			continue; // Menu separator or invalid cmd - ignore it. 

		ASSERT(state.m_pOther == NULL); 
		ASSERT(state.m_pMenu != NULL); 
		if (state.m_nID == (UINT)-1) 
		{ 
			// Possibly a popup menu, route to first item of that popup. 
			state.m_pSubMenu = pPopupMenu->GetSubMenu(state.m_nIndex); 
			if (state.m_pSubMenu == NULL || 
				(state.m_nID = state.m_pSubMenu->GetMenuItemID(0)) == 0 || 
				state.m_nID == (UINT)-1) 
			{ 
				continue; // First item of popup can't be routed to. 
			} 
			state.DoUpdate(this, TRUE); // Popups are never auto disabled. 
		} 
		else 
		{ 
			// Normal menu item. 
			// Auto enable/disable if frame window has m_bAutoMenuEnable 
			// set and command is _not_ a system command. 
			state.m_pSubMenu = NULL; 
			state.DoUpdate(this, FALSE); 
		} 

		// Adjust for menu deletions and additions. 
		UINT nCount = pPopupMenu->GetMenuItemCount(); 
		if (nCount < state.m_nIndexMax) 
		{ 
			state.m_nIndex -= (state.m_nIndexMax - nCount); 
			while (state.m_nIndex < nCount && 
				pPopupMenu->GetMenuItemID(state.m_nIndex) == state.m_nID) 
			{ 
				state.m_nIndex++; 
			} 
		} 
		state.m_nIndexMax = nCount; 
	} 
}


BOOL CLinkerPage::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	// TODO:  在此添加额外的初始化

	// 设置提示信息
	m_lblID.SetText(L"单机此处管理帐号");

	m_btnDisCon.SetDropDownMenu(IDR_DISMENU,0);

	CAccountInfo newUser;
	newUser.m_username=L"080520s";
	newUser.m_password=L"11111";
	newUser.m_autoDis=true;
	newUser.m_range=0;
	newUser.m_savePwd=true;
	newUser.m_showTip=true;
	theApp.accounts.Add(newUser);

	newUser.m_username=L"080519s";
	newUser.m_password=L"22222";
	newUser.m_autoDis=false;
	newUser.m_range=1;
	newUser.m_savePwd=false;
	newUser.m_showTip=false;
	theApp.accounts.Add(newUser);

	for(int i=0;i<theApp.accounts.GetCount();i++)
	{
		m_cboID.AddString(theApp.accounts[i].m_username);
	}
	m_txtInfo.SetWindowText(L"aaa\r\nbb\r\nccc\r\nddd\r\neee\r\nfff\r\nggg\r\nhhh\r\niii\r\njjj\r\n");

	// 更新界面，设置按钮的可用状态
	UpdateData(FALSE);
	SetBtnStat();
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CLinkerPage::OnCbnEditchangeComboId()
{
	// TODO: 在此添加控件通知处理程序代码
	m_cboID.GetWindowText(theApp.curAccount.m_username);
	SetItemText();
	SetBtnStat();
}

void CLinkerPage::OnCbnSelchangeComboId()
{
	// TODO: 在此添加控件通知处理程序代码
	int sel=m_cboID.GetCurSel();
	if (sel>=0)
		m_cboID.GetLBText(sel,theApp.curAccount.m_username);
	SetItemText();
	SetBtnStat();
}

void CLinkerPage::OnEnChangeEditPwd()
{
	// TODO:  如果该控件是 RICHEDIT 控件，则它将不会
	// 发送该通知，除非重写 CPropertyPage::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	m_txtPwd.GetWindowText(theApp.curAccount.m_password);
	SetBtnStat();
}

void CLinkerPage::SetItemText(void)
{
	TRACE(theApp.curAccount.m_username+L"  ");

	// 更新界面其他控件状态
	int index=m_cboID.FindStringExact(-1,theApp.curAccount.m_username);
	if (index>=0)
	{
		TRACE(theApp.accounts[index].m_username+L"\n");

		theApp.curAccount=theApp.accounts[index];
		m_txtPwd.SetWindowText(theApp.curAccount.m_password);
		if (theApp.curAccount.m_range==0)
		{
			m_rdoRangeIn.SetCheck(1);
			m_rdoRangeOut.SetCheck(0);
		}
		else
		{
			m_rdoRangeIn.SetCheck(0);
			m_rdoRangeOut.SetCheck(1);
		}
		m_chkSavePwd.SetCheck(theApp.curAccount.m_savePwd);
	}
	else
	{
		m_txtPwd.SetWindowText(L"");
		m_chkSavePwd.SetCheck(0);
	}
}

void CLinkerPage::SetBtnStat(void)
{
	// 更新按钮状态
	if (theApp.curAccount.m_username!="" && theApp.curAccount.m_password!="")
	{
		m_btnConnect.EnableWindow(TRUE);
		//m_btnDisCon.EnableWindow(TRUE);
	}
	else
	{
		m_btnConnect.EnableWindow(FALSE);
		//m_btnDisCon.EnableWindow(FALSE);

		m_btnDisCon.SetWindowText(L"断开");
		m_dis=0;
	}

}

void CLinkerPage::OnMenuDiscon()
{
	// TODO: 在此添加命令处理程序代码
	m_btnDisCon.SetWindowText(L"断开");
	m_dis=0;

	//OnBnClickedButtonDiscon(); // 选择菜单后自动触发单击事件
}

void CLinkerPage::OnMenuDisconAll()
{
	// TODO: 在此添加命令处理程序代码
	m_btnDisCon.SetWindowText(L"断开全部");
	m_dis=1;

	//OnBnClickedButtonDiscon(); // 选择菜单后自动触发单击事件
}

void CLinkerPage::OnUpdateDiscon(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	pCmdUI->SetCheck(!m_dis);
}

void CLinkerPage::OnUpdateDisconall(CCmdUI *pCmdUI)
{
	// TODO: 在此添加命令更新用户界面处理程序代码
	if (theApp.curAccount.m_username!="" && theApp.curAccount.m_password!="")
	{
		pCmdUI->Enable(TRUE);
	}
	else
		pCmdUI->Enable(FALSE);

	pCmdUI->SetCheck(m_dis);
}

void CLinkerPage::OnStnClickedStaticId()
{
	// TODO: 在此添加控件通知处理程序代码
	CAccountDlg accountDlg;
	accountDlg.DoModal();
	UpdateComboBox();
}

void CLinkerPage::OnBnClickedButtonCon()
{
	// TODO: 在此添加控件通知处理程序代码
	// 当连接成功时添加新用户到用户列表中
	UpdateData(TRUE);
	int index=m_cboID.FindStringExact(-1,theApp.curAccount.m_username);
	if (index==CB_ERR)
	{
		theApp.accounts.Add(theApp.curAccount);
		//m_cboID.AddString(theApp.curAccount.m_username);
		UpdateComboBox();
	}
	else
	{
		theApp.accounts[index]=theApp.curAccount;
	}

	AfxBeginThread(Connect, NULL);
}

void CLinkerPage::OnBnClickedButtonDiscon()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if (m_dis==1)
	{
		// 当断开全部成功时添加新用户到用户列表中
		int index=m_cboID.FindStringExact(-1,theApp.curAccount.m_username);
		if (index==CB_ERR)
		{
			theApp.accounts.Add(theApp.curAccount);
			//m_cboID.AddString(theApp.curAccount.m_username);
			UpdateComboBox();
		}
		else
		{
			theApp.accounts[index]=theApp.curAccount;
		}
	}

	AfxBeginThread(DisConnect, &m_dis);
}

void CLinkerPage::UpdateComboBox(void)
{
	int size=m_cboID.GetCount();
	for (int i=0;i<size;i++)
	{	
		m_cboID.DeleteString(0);
	}
	for (int i=0;i<theApp.accounts.GetCount();i++)
	{
		m_cboID.AddString(theApp.accounts[i].m_username);
	}
	CString curStr;
	m_cboID.GetWindowText(curStr);
	if (m_cboID.FindStringExact(-1,curStr)==CB_ERR)
	{
		m_cboID.SetWindowText(L"");
		OnCbnEditchangeComboId();
	}
}
