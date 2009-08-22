// LinkerPage.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "CUGBLinker.h"
#include "CUGBLinkerDlg.h"
#include "LinkerPage.h"
#include "AccountInfo.h"
#include "AccountDlg.h"
#include "global.h"


// CLinkerPage �Ի���

IMPLEMENT_DYNAMIC(CLinkerPage, CPropertyPage)

CLinkerPage::CLinkerPage()
: CPropertyPage(CLinkerPage::IDD)
, m_dis(0)
, m_bAutoStart(FALSE)
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
	DDX_Check(pDX, IDC_CHECK_WITHSYS, m_bAutoStart);
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
	ON_MESSAGE(WM_UPDATEINFO, &CLinkerPage::OnUpdateInfo)
	ON_BN_CLICKED(IDC_CHECK_WITHSYS, &CLinkerPage::OnBnClickedCheckWithsys)
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
	newUser.m_password=L"181305";
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
	//m_txtInfo.SetWindowText(L"�������ӳɹ�\r\n\r\n"
	//	L"�� �� ���� ������\r\n" 
	//	L"���ʷ�Χ�� ����\r\n" 
	//	L"Ƿ�Ѷ����� �� \r\n"
	//	L"��ʱ��飺 8Сʱ \r\n"
	//	L"��ǰ���ӣ� 0�� \r\n"
	//	L"�ʻ��� 40.000Ԫ \r\n"
	//	L"���Ƿ���Զ���������ע�⼰ʱ�ӿ\r\n");

	// ���½��棬���ð�ť�Ŀ���״̬
	//UpdateData(FALSE);
	SetBtnStat();
	InitStat();
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CLinkerPage::OnCbnEditchangeComboId()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_cboID.GetWindowText(theApp.curAccount.m_username);
	SetItemText();
	SetBtnStat();
}

void CLinkerPage::OnCbnSelchangeComboId()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int sel=m_cboID.GetCurSel();
	if (sel>=0)
		m_cboID.GetLBText(sel,theApp.curAccount.m_username);
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
	m_txtPwd.GetWindowText(theApp.curAccount.m_password);
	SetBtnStat();
}

void CLinkerPage::SetItemText(void)
{
	TRACE(theApp.curAccount.m_username+L"  ");

	// ���½��������ؼ�״̬
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
	// ���°�ť״̬
	if (theApp.curAccount.m_username!="" && theApp.curAccount.m_password!="")
	{
		m_btnConnect.EnableWindow(TRUE);
		//m_btnDisCon.EnableWindow(TRUE);
	}
	else
	{
		m_btnConnect.EnableWindow(FALSE);
		//m_btnDisCon.EnableWindow(FALSE);

		m_btnDisCon.SetWindowText(L"�Ͽ�");
		m_dis=0;
	}

}

void CLinkerPage::OnMenuDiscon()
{
	// TODO: �ڴ���������������
	m_btnDisCon.SetWindowText(L"�Ͽ�");
	m_dis=0;

	//OnBnClickedButtonDiscon(); // ѡ��˵����Զ����������¼�
}

void CLinkerPage::OnMenuDisconAll()
{
	// TODO: �ڴ���������������
	m_btnDisCon.SetWindowText(L"�Ͽ�ȫ��");
	m_dis=1;

	//OnBnClickedButtonDiscon(); // ѡ��˵����Զ����������¼�
}

void CLinkerPage::OnUpdateDiscon(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
	pCmdUI->SetCheck(!m_dis);
}

void CLinkerPage::OnUpdateDisconall(CCmdUI *pCmdUI)
{
	// TODO: �ڴ������������û����洦��������
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CAccountDlg accountDlg;
	accountDlg.DoModal();
	UpdateComboBox();
}

void CLinkerPage::OnBnClickedButtonCon()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	// �����ӳɹ�ʱ������û����û��б���
	UpdateData(TRUE);
	AfxBeginThread(Connect, NULL);
}

void CLinkerPage::OnBnClickedButtonDiscon()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
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

LRESULT CLinkerPage::OnUpdateInfo(WPARAM wParam, LPARAM lParam)
{
	CCUGBLinkerDlg* pMainWnd=(CCUGBLinkerDlg*)theApp.m_pMainWnd;

	CString* strInfo=(CString*)wParam;
	int* success=(int*)lParam;//0���ɹ���1���ӳɹ���2�Ͽ��ɹ�

	// �����м���ʾ��������
	m_txtInfo.SetWindowText(*strInfo);

	// ����������ʾ����
	strInfo->Replace(L"\n",L"");
	pMainWnd->nid.cbSize=sizeof(NOTIFYICONDATA);
	pMainWnd->nid.uFlags = NIF_INFO;
	swprintf(pMainWnd->nid.szInfo,*strInfo);
	if (*success==1)//���ӳɹ�
	{
		pMainWnd->nid.dwInfoFlags = NIIF_INFO;
		swprintf(pMainWnd->nid.szInfoTitle,L"���ӳɹ�");
	}
	else if (*success==2)//�Ͽ��ɹ�
	{
		pMainWnd->nid.dwInfoFlags = NIIF_INFO;
		swprintf(pMainWnd->nid.szInfoTitle,L"�Ͽ��ɹ�");
	}
	else if (*success==-1)//����ʧ��
	{
		pMainWnd->nid.dwInfoFlags = NIIF_ERROR;
		swprintf(pMainWnd->nid.szInfoTitle,L"����ʧ��");
	}
	else if (*success==-2)//�Ͽ�ʧ��
	{
		pMainWnd->nid.dwInfoFlags = NIIF_ERROR;
		swprintf(pMainWnd->nid.szInfoTitle,L"�Ͽ�ʧ��");
	}
	return Shell_NotifyIcon(NIM_MODIFY, &pMainWnd->nid);

	// ������û����û��б�
	if (*success==1 || (m_dis==1 && *success==2))
	{// ���ӻ�Ͽ��ɹ�
		// ���ӻ�Ͽ�ȫ���ɹ�ʱ������û����û��б���
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
	delete strInfo;
	delete success;
	return 0;
}

void CLinkerPage::OnBnClickedCheckWithsys()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData();

	CString fileName('\0',200);
	GetModuleFileName(NULL,fileName.GetBuffer(),200);
	fileName.ReleaseBuffer();
	HKEY hRegKey=NULL;
	CString str=_T("Software\\Microsoft\\Windows\\CurrentVersion\\Run");

	if(RegOpenKey(HKEY_CURRENT_USER,str,&hRegKey) != ERROR_SUCCESS)
		return;

	if(m_bAutoStart)
	{
		RegSetValueEx(hRegKey,_T("CUGBLinker"),0,REG_SZ,
			(CONST BYTE *)fileName.GetBuffer(),fileName.GetLength()*2);
		fileName.ReleaseBuffer();	
	}
	else
	{
		RegDeleteValue(hRegKey,_T("CUGBLinker"));
	}
	RegCloseKey(hRegKey);
}

void CLinkerPage::InitStat(void)
{
	// ���������ѡ��״̬
	HKEY hRegKey=NULL;
	CString str=_T("Software\\Microsoft\\Windows\\CurrentVersion\\Run");
	if(RegOpenKey(HKEY_CURRENT_USER,str,&hRegKey) == ERROR_SUCCESS)
	{
		LONG a;
		if(RegQueryValueEx(hRegKey,_T("CUGBLinker"),NULL,NULL,NULL,NULL)==ERROR_SUCCESS)
			m_chkAutoStart.SetCheck(1);
		else
			m_chkAutoStart.SetCheck(0);
	}
	RegCloseKey(hRegKey);
	
	// �û����б�״̬
	m_cboID.SetCurSel(0);
	OnCbnSelchangeComboId();

	// �Զ�����״̬

	// �Ͽ���ť״̬
}
