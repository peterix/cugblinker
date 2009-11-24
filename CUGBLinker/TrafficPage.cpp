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
	DDX_Control(pDX, IDC_EDIT_DISSIZE, m_txtMaxTraffic);
	DDX_Control(pDX, IDC_CHECK_DISTIP, m_chkShowTip);
	DDX_Control(pDX, IDC_CHECK_AUTODIS, m_chkAutoDis);
	DDX_Text(pDX, IDC_EDIT_DISSIZE, theApp.curAccount.m_maxTraffic);
	DDX_Check(pDX, IDC_CHECK_DISTIP, theApp.curAccount.m_showTip);
	DDX_Check(pDX, IDC_CHECK_AUTODIS, theApp.curAccount.m_autoDis);
}


BEGIN_MESSAGE_MAP(CTrafficPage, CPropertyPage)
	ON_WM_CTLCOLOR()
	ON_STN_CLICKED(IDC_STATIC_NIC, &CTrafficPage::OnStnClickedStaticNic)
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_CHECK_DISTIP, &CTrafficPage::OnBnClickedCheckDistip)
	ON_BN_CLICKED(IDC_CHECK_AUTODIS, &CTrafficPage::OnBnClickedCheckAutodis)
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

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	m_curNIC=theApp.configXml.GetCurNIC();

	CCUGBLinkerDlg* pMainWnd=(CCUGBLinkerDlg*)theApp.m_pMainWnd;
	CString NICDescription=GetNICDescription(m_curNIC);
	m_lblCurDev.SetWindowText(NICDescription.Left(20)+L"...");
	m_lblCurDev.SetText(NICDescription);
	
	// ���ý����ʼ��״̬

	// ���ý�����
	m_lblTotal.SetFont(&textFont);
	m_lblTotal.SetWindowText(L"2005/2408(10%)");
	m_proTotal.SetPos(50);

	// ��������ͳ�ƺ�����ʼͳ������
	AfxBeginThread(statistic_traffic, NULL);

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CTrafficPage::OnStnClickedStaticNic()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDeviceDlg deviceDlg;
	deviceDlg.SetCurNIC(m_curNIC);
	if (IDOK==deviceDlg.DoModal())
	{
		m_curNIC=deviceDlg.GetCurNIC();
	}
	m_lblCurDev.SetWindowText(GetNICDescription(m_curNIC).Left(20)+L"...");
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
	pcap_freealldevs(alldevs);
	return L"";
}

void CTrafficPage::OnBnClickedCheckDistip()
{
	CCUGBLinkerDlg* pMainWnd=(CCUGBLinkerDlg*)theApp.m_pMainWnd;
	CLinkerPage* pLinkerPage=(CLinkerPage*)&(pMainWnd->m_linkerPage);

	if (pLinkerPage->m_curAccountIndex>=0 && pLinkerPage->m_curAccountIndex<theApp.accounts.GetCount())
	{
		theApp.accounts[pLinkerPage->m_curAccountIndex]=theApp.curAccount;
	}
	if (m_chkShowTip.GetCheck())
	{
		m_chkAutoDis.EnableWindow(TRUE);
	}
	else
		m_chkAutoDis.EnableWindow(FALSE);
}

void CTrafficPage::OnBnClickedCheckAutodis()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}
