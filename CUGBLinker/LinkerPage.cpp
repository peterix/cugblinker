// LinkerPage.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "CUGBLinker.h"
#include "LinkerPage.h"


// CLinkerPage �Ի���

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


// CLinkerPage ��Ϣ�������

BOOL CLinkerPage::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	// ��ʼ��Socket
	m_socket.Create();
	if(0 == m_socket.Connect(L"202.204.105.7",80))
	{
		MessageBox(L"Connect Error!");
	}


	// ������ʾ��Ϣ
	m_lblID.SetText(L"�����˴������ʺ�");

	m_cboID.AddString(L"080520s");
	m_cboID.AddString(L"4104211");

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CLinkerPage::OnStnClickedStaticId()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	MessageBox(L"Clicked");
}

void CLinkerPage::OnBnClickedButtonCon()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	// Step 3: Send message
	CString userStr;
	userStr.Format(L"uid=080519S&password=12345&range=0&timeout=1&operation=connect");
	CString sendStr;
	sendStr.Format(L"POST /ipgw/ipgw.ipgw HTTP/1.1\r\nHost: 202.204.105.7\r\nContent-Length: %d\r\nContent-Type: application/x-www-form-urlencoded\r\n\r\n",userStr.GetLength());
	sendStr+=userStr;

	if (m_socket.Send(sendStr,sendStr.GetLength()) == SOCKET_ERROR) 
	{
		MessageBox(L"����ʧ�ܣ�Connect��!");
	}

 	//CString revStr=L"";
 	//if(m_socket.Receive(revStr.GetBuffer(),10000) == SOCKET_ERROR)
 	//{
 	//	MessageBox(L"Receive Error!");
 	//}
 	//revStr.ReleaseBuffer();
}
