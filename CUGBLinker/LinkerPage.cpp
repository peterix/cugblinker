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
, m_osVersion(0)
, m_bAutoCon(FALSE)
, m_curAccountNum(0)
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
	DDX_Control(pDX, IDC_BUTTONXP_DISCON, m_btnDisConXP);
	DDX_CBString(pDX, IDC_COMBO_ID, theApp.curAccount.m_username);
	DDX_Text(pDX, IDC_EDIT_PWD, theApp.curAccount.m_password);
	DDX_Check(pDX, IDC_CHECK_SAVEPWD, theApp.curAccount.m_savePwd);
	DDX_Radio(pDX, IDC_RADIO_IN, theApp.curAccount.m_range);
	DDX_Check(pDX, IDC_CHECK_WITHSYS, m_bAutoStart);
	DDX_Check(pDX, IDC_CHECK_AUTOCON, m_bAutoCon);
}


BEGIN_MESSAGE_MAP(CLinkerPage, CPropertyPage)
	ON_STN_CLICKED(IDC_STATIC_ID, &CLinkerPage::OnStnClickedStaticId)
	ON_BN_CLICKED(IDC_BUTTON_CON, &CLinkerPage::OnBnClickedButtonCon)
	ON_BN_CLICKED(IDC_BUTTON_DISCON, &CLinkerPage::OnBnClickedButtonDiscon)
	ON_BN_CLICKED(IDC_BUTTONXP_DISCON, &CLinkerPage::OnBnClickedButtonDiscon)
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
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_RADIO_IN, &CLinkerPage::OnBnClickedSaveAccount)
	ON_BN_CLICKED(IDC_RADIO_OUT, &CLinkerPage::OnBnClickedSaveAccount)
	ON_BN_CLICKED(IDC_CHECK_SAVEPWD, &CLinkerPage::OnBnClickedSaveAccount)
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
	// �жϵ�ǰʹ�õ�ϵͳ����������ʾʲô��ʽ�ĶϿ���ť
	OSVERSIONINFO osvi;
	ZeroMemory(&osvi, sizeof(OSVERSIONINFO));
	osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFO);
	GetVersionEx(&osvi);
	m_osVersion=osvi.dwMajorVersion;

	if (m_osVersion>=6) // VISTA���ϰ汾
	{
		m_btnDisConXP.ShowWindow(SW_HIDE);
		m_btnDisCon.ShowWindow(SW_SHOW);
	}
	else // VISTA���°汾��XP�� 
	{
		m_btnDisConXP.ShowWindow(SW_SHOW);
		m_btnDisCon.ShowWindow(SW_HIDE);
	}


	// ������ʾ��Ϣ
	m_lblID.SetText(L"�����˴������ʺ�");

	m_btnDisCon.SetDropDownMenu(IDR_DISMENU,0);

	//CAccountInfo newUser;
	//newUser.m_username=L"1111111";
	//newUser.m_password=L"2222222";
	//newUser.m_autoDis=true;
	//newUser.m_range=0;
	//newUser.m_savePwd=true;
	//newUser.m_showTip=true;
	//theApp.configXml.SetAccount(newUser);
	//theApp.accounts.Add(newUser);

	//newUser.m_username=L"080519s";
	//newUser.m_password=L"22222";
	//newUser.m_autoDis=false;
	//newUser.m_range=1;
	//newUser.m_savePwd=false;
	//newUser.m_showTip=false;
	//theApp.accounts.Add(newUser);

	//for(int i=0;i<theApp.accounts.GetCount();i++)
	//{
	//	m_cboID.AddString(theApp.accounts[i].m_username);
	//}
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
	InitStat();
	SetBtnStat();
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
	m_curAccountNum=m_cboID.GetCurSel();
	if (m_curAccountNum>=0)
		m_cboID.GetLBText(m_curAccountNum,theApp.curAccount.m_username);
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
	if (GetFocus()==&m_txtPwd)
	{
		OnBnClickedSaveAccount();	
	}
	SetBtnStat();
}

// �û��ı�ʱ��Ҫ���ô˺��������������ؼ�״̬
void CLinkerPage::SetItemText(void)
{
	// ���½��������ؼ�״̬
	int index=m_cboID.FindStringExact(-1,theApp.curAccount.m_username);
	m_curAccountNum=index;
	if (index>=0)
	{
		theApp.curAccount=theApp.accounts[index];
		if (theApp.curAccount.m_savePwd)
		{
			m_txtPwd.SetWindowText(theApp.curAccount.m_password);
		}
		else
			m_txtPwd.SetWindowText(L"");

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
		if (m_chkSavePwd.GetCheck())
		{
			m_chkAutoCon.EnableWindow(TRUE);
		}
		else
			m_chkAutoCon.EnableWindow(FALSE);
	}
	else
	{
		m_txtPwd.SetWindowText(L"");
		m_chkSavePwd.SetCheck(0);
		m_chkAutoCon.EnableWindow(FALSE);
	}
}

void CLinkerPage::SetBtnStat(void)
{
	// ���°�ť״̬
	m_txtPwd.GetWindowText(theApp.curAccount.m_password);

	if (theApp.curAccount.m_username!="" && theApp.curAccount.m_password!="")
	{
		m_btnConnect.EnableWindow(TRUE);
		m_btnDisConXP.EnableWindow(TRUE);
	}
	else
	{
		m_btnConnect.EnableWindow(FALSE);
		m_btnDisConXP.EnableWindow(FALSE);

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

	m_txtInfo.SetWindowText(L"�����С�");
}

void CLinkerPage::OnBnClickedButtonDiscon()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);
	if (m_osVersion<6) // VISTA���°汾��XP��
		m_dis=1;
	AfxBeginThread(DisConnect, &m_dis);
	m_txtInfo.SetWindowText(L"�Ͽ��С�");
}

// ���û��б�ı����Ҫ����ComboBox����
void CLinkerPage::UpdateComboBox(void)
{
	//CString curStr;
	//m_cboID.GetWindowText(curStr);
	//UpdateData(TRUE);

	// ���ԭComboBox����
	int size=m_cboID.GetCount();
	for (int i=0;i<size;i++)
	{	
		m_cboID.DeleteString(0);
	}

	// ���б����û�����ӵ�ComboBox��
	size=theApp.accounts.GetCount();
	for (int i=0;i<size;i++)
	{
		m_cboID.AddString(theApp.accounts[i].m_username);
	}

	if (m_cboID.FindStringExact(-1,theApp.curAccount.m_username)==CB_ERR)
	{
		m_cboID.SetWindowText(L"");
	}
	else
	{
		m_cboID.SetWindowText(theApp.curAccount.m_username);
		m_cboID.SelectString(-1,theApp.curAccount.m_username);
	}
	OnCbnEditchangeComboId();
}

// ������Ϣ��ʾ�������Ѿ�������û���Ϣ���û��б�
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
	_tcscpy_s(pMainWnd->nid.szInfo,*strInfo);
	if (*success==1)//���ӳɹ�
	{
		pMainWnd->nid.dwInfoFlags = NIIF_INFO;
		_tcscpy_s(pMainWnd->nid.szInfoTitle,L"���ӳɹ�");
	}
	else if (*success==2)//�Ͽ��ɹ�
	{
		pMainWnd->nid.dwInfoFlags = NIIF_INFO;
		_tcscpy_s(pMainWnd->nid.szInfoTitle,L"�Ͽ��ɹ�");
	}
	else if (*success==-1)//����ʧ��
	{
		pMainWnd->nid.dwInfoFlags = NIIF_ERROR;
		_tcscpy_s(pMainWnd->nid.szInfoTitle,L"����ʧ��");
	}
	else if (*success==-2)//�Ͽ�ʧ��
	{
		pMainWnd->nid.dwInfoFlags = NIIF_ERROR;
		_tcscpy_s(pMainWnd->nid.szInfoTitle,L"�Ͽ�ʧ��");
	}
	Shell_NotifyIcon(NIM_MODIFY, &pMainWnd->nid);

	CString tempStr;
	m_txtPwd.GetWindowText(tempStr);
	// ������û����û��б�
	if (*success==1 || (m_dis==1 && *success==2))
	{
		// ���ӻ�Ͽ�ȫ���ɹ�ʱ������û����û��б���
		int index=m_cboID.FindStringExact(-1,theApp.curAccount.m_username);
		if (index==CB_ERR)
		{
			theApp.accounts.Add(theApp.curAccount);
			UpdateComboBox();
		}
		//else
		//{
		//	theApp.accounts[index]=theApp.curAccount;
		//}
	}
	m_txtPwd.SetWindowText(tempStr);
	delete strInfo;
	delete success;
	return 0;
}

void CLinkerPage::OnBnClickedCheckWithsys()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(TRUE);

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
	// ��ϵͳ������ѡ��״̬
	HKEY hRegKey=NULL;
	CString str=_T("Software\\Microsoft\\Windows\\CurrentVersion\\Run");
	if(RegOpenKey(HKEY_CURRENT_USER,str,&hRegKey) == ERROR_SUCCESS)
	{
		if(RegQueryValueEx(hRegKey,_T("CUGBLinker"),NULL,NULL,NULL,NULL)==ERROR_SUCCESS)
			m_chkAutoStart.SetCheck(1);
		else
			m_chkAutoStart.SetCheck(0);
	}
	RegCloseKey(hRegKey);
	
	// �û����б�״̬
	int accountLen=theApp.configXml.GetAccountCount();
	for (int i=0;i<accountLen;i++)
	{
		theApp.accounts.Add(theApp.configXml.GetAccount(i));
	}
	UpdateComboBox();
	m_curAccountNum=theApp.configXml.GetActiveAccount();
	m_cboID.SetCurSel(m_curAccountNum);
	OnCbnSelchangeComboId();
	//if (m_curAccountNum>=0 && m_curAccountNum<theApp.accounts.GetCount())
	//{
	//	theApp.curAccount=theApp.accounts[m_curAccountNum];
	//	SetItemText();
	//}


	// �Զ�����״̬
	m_chkAutoCon.SetCheck(theApp.configXml.GetAutoConnect());
	if (m_btnConnect.IsWindowEnabled())
	{
		if (m_chkAutoCon.GetCheck())
		{
			OnBnClickedButtonCon();
		}
	}
	else
		m_chkAutoCon.EnableWindow(FALSE);

	// �Ͽ���ť״̬
	m_dis=theApp.configXml.GetDisBtnStatus();
	if (m_dis)
		m_btnDisCon.SetWindowText(L"�Ͽ�ȫ��");
	else
		m_btnDisCon.SetWindowText(L"�Ͽ�");
}

void CLinkerPage::OnDestroy()
{
	CPropertyPage::OnDestroy();

	// TODO: �ڴ˴������Ϣ����������

	// ����������õ�xml�ļ�
	UpdateData(TRUE);
	// �û����б�״̬
	int accountLen=theApp.configXml.GetAccountCount();
	for (int i=accountLen-1;i>=0;i--)
	{
		theApp.configXml.DelAccount(i);
	}
	theApp.configXml.SaveFile();
	accountLen=theApp.accounts.GetCount();
	for (int i=0;i<accountLen;i++)
	{
		theApp.configXml.SetAccount(theApp.accounts[i]);
	}
	theApp.configXml.SetActiveAccount(m_curAccountNum);

	// �Զ�����״̬
	theApp.configXml.SetAutoConnect(m_bAutoCon);

	// �Ͽ���ť״̬
	theApp.configXml.SetDisBtnStatus(m_dis);

	theApp.configXml.SaveFile();
}

void CLinkerPage::OnBnClickedSaveAccount()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	// ���浱ǰ�û�����
	UpdateData(TRUE);
	if (m_curAccountNum>=0 && m_curAccountNum<theApp.accounts.GetCount())
	{
		theApp.accounts[m_curAccountNum]=theApp.curAccount;
	}
	if (m_chkSavePwd.GetCheck())
	{
		m_chkAutoCon.EnableWindow(TRUE);
	}
	else
		m_chkAutoCon.EnableWindow(FALSE);
}
void CLinkerPage::OnStnClickedStaticId(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
}
