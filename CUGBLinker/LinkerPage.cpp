// LinkerPage.cpp : 实现文件
//

#include "stdafx.h"
#include "CUGBLinker.h"
#include "LinkerPage.h"


// CLinkerPage 对话框

IMPLEMENT_DYNAMIC(CLinkerPage, CPropertyPage)

CLinkerPage::CLinkerPage()
	: CPropertyPage(CLinkerPage::IDD)
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
}


BEGIN_MESSAGE_MAP(CLinkerPage, CPropertyPage)
	ON_STN_CLICKED(IDC_STATIC_ID, &CLinkerPage::OnStnClickedStaticId)
	ON_BN_CLICKED(IDC_BUTTON_CON, &CLinkerPage::OnBnClickedButtonCon)
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
