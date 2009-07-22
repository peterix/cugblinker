// LinkerPage.cpp : 实现文件
//

#include "stdafx.h"
#include "CUGBLinker.h"
#include "LinkerPage.h"


// CLinkerPage 对话框

IMPLEMENT_DYNAMIC(CLinkerPage, CPropertyPage)

CLinkerPage::CLinkerPage()
	: CPropertyPage(CLinkerPage::IDD)
	, m_strID(_T(""))
	, m_strPwd(_T(""))
{

}

CLinkerPage::~CLinkerPage()
{
}

void CLinkerPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_ID, m_cboID);
	DDX_Control(pDX, IDC_STATIC_ID, m_lblID);
	DDX_Control(pDX, IDC_BUTTON_CON, m_btnConnect);
	DDX_Control(pDX, IDC_BUTTON_DISCON, m_btnDisConnect);
	DDX_CBString(pDX, IDC_COMBO_ID, m_strID);
	DDX_Text(pDX, IDC_EDIT_PWD, m_strPwd);
}


BEGIN_MESSAGE_MAP(CLinkerPage, CPropertyPage)
	ON_STN_CLICKED(IDC_STATIC_ID, &CLinkerPage::OnStnClickedStaticId)
	ON_BN_CLICKED(IDC_BUTTON_CON, &CLinkerPage::OnBnClickedButtonCon)
	ON_CBN_EDITCHANGE(IDC_COMBO_ID, &CLinkerPage::OnCbnEditchangeComboId)
ON_CBN_SELCHANGE(IDC_COMBO_ID, &CLinkerPage::OnCbnSelchangeComboId)
ON_EN_CHANGE(IDC_EDIT_PWD, &CLinkerPage::OnEnChangeEditPwd)
END_MESSAGE_MAP()


// CLinkerPage 消息处理程序

BOOL CLinkerPage::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	// TODO:  在此添加额外的初始化

	// 设置提示信息
	m_lblID.SetText(L"单机此处管理帐号");

	m_cboID.AddString(L"080520s");
	m_cboID.AddString(L"4104211");

	// 更新界面，设置按钮的可用状态
	UpdateData(FALSE);
	CheckEditChange();
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CLinkerPage::OnStnClickedStaticId()
{
	// TODO: 在此添加控件通知处理程序代码
	MessageBox(L"Clicked");
}

void CLinkerPage::OnBnClickedButtonCon()
{
	// TODO: 在此添加控件通知处理程序代码
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
		MessageBox(L"发送失败（Connect）!");
	}

	// Step 4: Receive message

 	CStringA recStr('\0',10000) ;
 	if(m_pSocket->Receive(recStr.GetBuffer(),10000) == SOCKET_ERROR)
 	{
 		MessageBox(L"Receive Error!");
 	}
 	recStr.ReleaseBuffer();
	delete m_pSocket;
}

void CLinkerPage::OnCbnEditchangeComboId()
{
	// TODO: 在此添加控件通知处理程序代码
	CheckEditChange();
}

void CLinkerPage::OnCbnSelchangeComboId()
{
	// TODO: 在此添加控件通知处理程序代码
	CheckEditChange();
}

void CLinkerPage::OnEnChangeEditPwd()
{
	// TODO:  如果该控件是 RICHEDIT 控件，则它将不会
	// 发送该通知，除非重写 CPropertyPage::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	CheckEditChange();
}

void CLinkerPage::CheckEditChange(void)
{
	UpdateData(TRUE);
	if (m_strID!="" && m_strPwd!="")
	{
		m_btnConnect.EnableWindow(TRUE);
		m_btnDisConnect.EnableWindow(TRUE);
	}
	else
	{
		m_btnConnect.EnableWindow(FALSE);
		m_btnDisConnect.EnableWindow(FALSE);
	}
}
