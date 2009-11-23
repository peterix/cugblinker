// TrafficPage.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "CUGBLinker.h"
#include "TrafficPage.h"
#include "DeviceDlg.h"
#include "CUGBLinkerDlg.h"

// CTrafficPage �Ի���

IMPLEMENT_DYNAMIC(CTrafficPage, CPropertyPage)

CTrafficPage::CTrafficPage()
	: CPropertyPage(CTrafficPage::IDD)
	, m_curNIC(_T(""))
{

}

CTrafficPage::~CTrafficPage()
{
}

void CTrafficPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON_SPEED, m_btnSpeed);
	DDX_Control(pDX, IDC_PROGRESS_TOTAL, m_proTotal);
	DDX_Control(pDX, IDC_STATIC_TOTAL, m_lblTotal);
	DDX_Control(pDX, IDC_STATIC_NIC, m_lblCurDev);
}


BEGIN_MESSAGE_MAP(CTrafficPage, CPropertyPage)
	ON_WM_CTLCOLOR()
	ON_STN_CLICKED(IDC_STATIC_NIC, &CTrafficPage::OnStnClickedStaticNic)
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// CTrafficPage ��Ϣ�������

HBRUSH CTrafficPage::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CPropertyPage::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  �ڴ˸��� DC ���κ�����
	if (pWnd->GetDlgCtrlID() == IDC_STATIC_TOTAL)
	{  
		pDC->SetTextColor(RGB(40,20,40));
		pDC->SetBkMode(TRANSPARENT);
	}	

	// TODO:  ���Ĭ�ϵĲ������軭�ʣ��򷵻���һ������
	return hbr;
}

BOOL CTrafficPage::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��	textFont.CreateFont(20,0,0,0,FW_BOLD, FALSE, FALSE, FALSE, DEFAULT_CHARSET,OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, VARIABLE_PITCH, _T("Arial"));
	m_curNIC=theApp.configXml.GetCurNIC();

	CCUGBLinkerDlg* pMainWnd=(CCUGBLinkerDlg*)theApp.m_pMainWnd;
	CString NICDescription=GetNICDescription(m_curNIC);
	m_lblCurDev.SetWindowText(NICDescription.Left(20)+L"...");
	m_lblCurDev.SetText(NICDescription);
	


	m_lblTotal.SetFont(&textFont);
	m_lblTotal.SetWindowText(L"2005/2408(10%)");
	m_proTotal.SetPos(50);

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CTrafficPage::OnStnClickedStaticNic()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDeviceDlg deviceDlg;
	if (IDOK==deviceDlg.DoModal())
	{
		//m_curNIC=deviceDlg.m_txtDevInfo;
	}	
	m_lblCurDev.SetText(GetNICDescription(m_curNIC));
}

void CTrafficPage::OnDestroy()
{
	CPropertyPage::OnDestroy();

	// TODO: �ڴ˴������Ϣ����������
	theApp.configXml.SetCurNIC(m_curNIC);
}

CString CTrafficPage::GetNICDescription(CString nic)
{
	pcap_if_t* alldevs=finddevs();
	pcap_if_t* d=NULL;
	/* Print the list */
	for(d = alldevs; d != NULL; d = d->next)
	{
		if (m_curNIC==CString(d->name))
		{
			return CString(d->description);
			break;
		}
	}
	return L"";
}
