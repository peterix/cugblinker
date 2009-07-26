// LinkerPage.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "CUGBLinker.h"
#include "LinkerPage.h"
#include "AccountInfo.h"


// CLinkerPage �Ի���

IMPLEMENT_DYNAMIC(CLinkerPage, CPropertyPage)

CLinkerPage::CLinkerPage()
: CPropertyPage(CLinkerPage::IDD)
, m_bDisconAll(false)
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
	DDX_CBString(pDX, IDC_COMBO_ID, curAccount.m_username);
	DDX_Text(pDX, IDC_EDIT_PWD, curAccount.m_password);
	DDX_Check(pDX, IDC_CHECK_SAVEPWD, curAccount.m_savePwd);
	DDX_Radio(pDX, IDC_RADIO_IN, curAccount.m_range);
	DDX_Check(pDX, IDC_CHECK_AUTOCON, curAccount.m_autoCon);
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


// CLinkerPage ��Ϣ�������

void CLinkerPage::OnInitMenuPopup(CMenu* pPopupMenu, UINT nIndex, BOOL bSysMenu)
{
	CPropertyPage::OnInitMenuPopup(pPopupMenu, nIndex, bSysMenu);

	// TODO: �ڴ˴������Ϣ����������
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

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	// ������ʾ��Ϣ
	m_lblID.SetText(L"�����˴������ʺ�");

	m_btnDisCon.SetDropDownMenu(IDR_DISMENU,0);

	CAccountInfo newUser;
	newUser.m_username=L"080520s";
	newUser.m_password=L"11111";
	newUser.m_autoCon=true;
	newUser.m_autoDis=true;
	newUser.m_range=0;
	newUser.m_savePwd=true;
	newUser.m_showTip=true;
	theApp.accounts.Add(newUser);
	newUser.m_username=L"080519s";
	newUser.m_password=L"22222";
	newUser.m_autoCon=false;
	newUser.m_autoDis=false;
	newUser.m_range=1;
	newUser.m_savePwd=false;
	newUser.m_showTip=false;

	theApp.accounts.Add(newUser);
	//m_cboID.AddString(L"080520s");
	//m_cboID.AddString(L"4104211");
	for(int i=0;i<theApp.accounts.GetCount();i++)
	{
		m_cboID.AddString(theApp.accounts[i].m_username);
	}
	m_txtInfo.SetWindowText(L"aaa\r\nbb\r\nccc\r\nddd\r\neee\r\nfff\r\nggg\r\nhhh\r\niii\r\njjj\r\n");

	// ���½��棬���ð�ť�Ŀ���״̬
	UpdateData(FALSE);
	SetBtnStat();
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CLinkerPage::OnCbnEditchangeComboId()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_cboID.GetWindowText(curAccount.m_username);
	SetItemText();
	SetBtnStat();
}

void CLinkerPage::OnCbnSelchangeComboId()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int sel=m_cboID.GetCurSel();
	if (sel>=0)
		m_cboID.GetLBText(sel,curAccount.m_username);
	SetItemText();
	SetBtnStat();
}

void CLinkerPage::OnEnChangeEditPwd()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ�������������
	// ���͸�֪ͨ��������д CPropertyPage::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	m_txtPwd.GetWindowText(curAccount.m_password);
	SetBtnStat();
}

void CLinkerPage::SetItemText(void)
{
	TRACE(curAccount.m_username+L"  ");

	// ���½��������ؼ�״̬
	int index=m_cboID.FindStringExact(-1,curAccount.m_username);
	if (index>=0)
	{
		TRACE(theApp.accounts[index].m_username+L"\n");

		curAccount=theApp.accounts[index];
		m_txtPwd.SetWindowText(curAccount.m_password);
		if (curAccount.m_range==0)
		{
			m_rdoRangeIn.SetCheck(1);
			m_rdoRangeOut.SetCheck(0);
		}
		else
		{
			m_rdoRangeIn.SetCheck(0);
			m_rdoRangeOut.SetCheck(1);
		}
		m_chkAutoCon.SetCheck(curAccount.m_autoCon);
		m_chkSavePwd.SetCheck(curAccount.m_savePwd);
	}
	else
	{
		m_txtPwd.SetWindowText(L"");
		m_chkSavePwd.SetCheck(0);
	}
}

void CLinkerPage::SetBtnStat(void)
{
	// ���°�ť״̬
	if (curAccount.m_username!="" && curAccount.m_password!="")
	{
		m_btnConnect.EnableWindow(TRUE);
		//m_btnDisCon.EnableWindow(TRUE);
	}
	else
	{
		m_btnConnect.EnableWindow(FALSE);
		//m_btnDisCon.EnableWindow(FALSE);

		m_btnDisCon.SetWindowText(L"�Ͽ�");
		m_bDisconAll=false;
	}

}

void CLinkerPage::OnMenuDiscon()
{
	// TODO: �ڴ���������������
	m_btnDisCon.SetWindowText(L"�Ͽ�");
	m_bDisconAll=false;

	OnBnClickedButtonDiscon(); // ѡ��˵����Զ����������¼�
}

void CLinkerPage::OnMenuDisconAll()
{
	// TODO: �ڴ���������������
	m_btnDisCon.SetWindowText(L"�Ͽ�ȫ��");
	m_bDisconAll=true;

	OnBnClickedButtonDiscon(); // ѡ��˵����Զ����������¼�
}

void CLinkerPage::OnUpdateDiscon(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	pCmdUI->SetCheck(!m_bDisconAll);
}

void CLinkerPage::OnUpdateDisconall(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	if (curAccount.m_username!="" && curAccount.m_password!="")
	{
		pCmdUI->Enable(TRUE);
	}
	else
		pCmdUI->Enable(FALSE);

	pCmdUI->SetCheck(m_bDisconAll);
}

void CLinkerPage::OnStnClickedStaticId()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	MessageBox(L"Clicked");
}

void CLinkerPage::OnBnClickedButtonCon()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	// ������û����û��б���
	UpdateData(TRUE);
	int index=m_cboID.FindStringExact(-1,curAccount.m_username);
	if (index==CB_ERR)
	{
		theApp.accounts.Add(curAccount);
		m_cboID.AddString(curAccount.m_username);
	}
	else
	{
		theApp.accounts[index]=curAccount;
	}

	MessageBox(L"Connect Success!");

	// ��������
	/*
	m_pSocket=new CSocket();
	m_pSocket->Create();
	if(0 == m_pSocket->Connect(L"202.204.105.7",80))
	{
	MessageBox(L"Connect Error!");
	}

	// Step 3: Send message
	CStringA userStr;
	userStr.Format("uid=080519s&password=12345&range=0&timeout=1&operation=connect");
	CStringA sendStr;
	sendStr.Format("POST /ipgw/ipgw.ipgw HTTP/1.1\r\nHost: 202.204.105.7\r\nContent-Length: %d\r\nContent-Type: application/x-www-form-urlencoded\r\n\r\n",userStr.GetLength());
	sendStr+=userStr;

	if (m_pSocket->Send(sendStr,sendStr.GetLength(),0) == SOCKET_ERROR) 
	{
	MessageBox(L"����ʧ�ܣ�Connect��!");
	}

	// Step 4: Receive message

	CStringA recStr('\0',10000) ;
	if(m_pSocket->Receive(recStr.GetBuffer(),10000) == SOCKET_ERROR)
	{
	MessageBox(L"Receive Error!");
	}
	recStr.ReleaseBuffer();
	delete m_pSocket;
	*/
}

void CLinkerPage::OnBnClickedButtonDiscon()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	MessageBox(L"Disconnect Success!");
}
