// AccountDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "CUGBLinker.h"
#include "AccountDlg.h"


// CAccountDlg 对话框

IMPLEMENT_DYNAMIC(CAccountDlg, CDialog)

CAccountDlg::CAccountDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CAccountDlg::IDD, pParent)
{

}

CAccountDlg::~CAccountDlg()
{
}

void CAccountDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_ACCOUNT_LIST, m_lstAccounts);
	DDX_Control(pDX, IDC_DEL_BUTTON, m_btnDel);
	DDX_Control(pDX, IDC_DELALL_BUTTON, m_btnDelAll);
}


BEGIN_MESSAGE_MAP(CAccountDlg, CDialog)
	ON_BN_CLICKED(IDC_DEL_BUTTON, &CAccountDlg::OnBnClickedDelButton)
	ON_BN_CLICKED(IDC_DELALL_BUTTON, &CAccountDlg::OnBnClickedDelallButton)
	ON_LBN_SELCHANGE(IDC_ACCOUNT_LIST, &CAccountDlg::OnLbnSelchangeAccountList)
END_MESSAGE_MAP()


// CAccountDlg 消息处理程序

BOOL CAccountDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	// 初始化list
	for (int i=0;i<theApp.accounts.GetCount();i++)
	{
		m_lstAccounts.AddString(theApp.accounts[i].m_username);
	}
	if (m_lstAccounts.GetCount()<=0)
	{
		m_btnDelAll.EnableWindow(FALSE);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CAccountDlg::OnBnClickedDelButton()
{
	// TODO: 在此添加控件通知处理程序代码
	for (int i=0;i<m_lstAccounts.GetCount();)
	{
		if (m_lstAccounts.GetSel(i))
		{
			m_lstAccounts.DeleteString(i);
			theApp.accounts.RemoveAt(i);
		}
		else
			i++;
	}
	m_btnDel.EnableWindow(FALSE);
	if (m_lstAccounts.GetCount()<=0)
	{
		m_btnDelAll.EnableWindow(FALSE);
	}
}

void CAccountDlg::OnBnClickedDelallButton()
{
	// TODO: 在此添加控件通知处理程序代码
	for (int i=0;i<theApp.accounts.GetCount();i++)
	{
		m_lstAccounts.DeleteString(0);
	}
	theApp.accounts.RemoveAll();

	m_btnDel.EnableWindow(FALSE);
	m_btnDelAll.EnableWindow(FALSE);
}

void CAccountDlg::OnLbnSelchangeAccountList()
{
	// TODO: 在此添加控件通知处理程序代码
	TRACE("%d\n",m_lstAccounts.GetSelCount());
	if (m_lstAccounts.GetSelCount()>0)
	{
		m_btnDel.EnableWindow(TRUE);
	}
	else
		m_btnDel.EnableWindow(FALSE);

}
