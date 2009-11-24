// TrafficPage.cpp : 实现文件
//

#include "stdafx.h"
#include "CUGBLinker.h"
#include "TrafficPage.h"
#include "DeviceDlg.h"
#include "CUGBLinkerDlg.h"

// CTrafficPage 对话框

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


// CTrafficPage 消息处理程序

HBRUSH CTrafficPage::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CPropertyPage::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何属性
	if (pWnd->GetDlgCtrlID() == IDC_STATIC_TOTAL)
	{  
		pDC->SetTextColor(RGB(40,20,40));
		pDC->SetBkMode(TRANSPARENT);
	}	

	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
	return hbr;
}

BOOL CTrafficPage::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_curNIC=theApp.configXml.GetCurNIC();

	CCUGBLinkerDlg* pMainWnd=(CCUGBLinkerDlg*)theApp.m_pMainWnd;
	CString NICDescription=GetNICDescription(m_curNIC);
	m_lblCurDev.SetWindowText(NICDescription.Left(20)+L"...");
	m_lblCurDev.SetText(NICDescription);
	
	// 设置界面初始化状态

	// 设置进度条
	m_lblTotal.SetFont(&textFont);
	m_lblTotal.SetWindowText(L"2005/2408(10%)");
	m_proTotal.SetPos(50);

	// 调用流量统计函数开始统计流量
	AfxBeginThread(statistic_traffic, NULL);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CTrafficPage::OnStnClickedStaticNic()
{
	// TODO: 在此添加控件通知处理程序代码
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

	// TODO: 在此处添加消息处理程序代码
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
	// TODO: 在此添加控件通知处理程序代码
}
