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
	, pLinkerPage(NULL)
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
	ON_EN_CHANGE(IDC_EDIT_DISSIZE, &CTrafficPage::OnEnChangeEditDissize)
	ON_WM_TIMER()
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
	CCUGBLinkerDlg* pMainWnd=(CCUGBLinkerDlg*)theApp.m_pMainWnd;
	pLinkerPage=(CLinkerPage*)&(pMainWnd->m_linkerPage);

	m_curNIC=theApp.configXml.GetCurNIC();

	CString NICDescription=GetNICDescription(m_curNIC);
	if (NICDescription.GetLength()>20)
	{
		m_lblCurDev.SetWindowText(NICDescription.Left(20)+L"...");
	}
	else
		m_lblCurDev.SetWindowText(NICDescription);
	m_lblCurDev.SetText(NICDescription);
	
	// 设置界面初始化状态
	if (theApp.curAccount.m_showTip)
	{
		m_chkAutoDis.EnableWindow(TRUE);
	}
	else
		m_chkAutoDis.EnableWindow(FALSE);

	// 设置进度条
	m_lblTotal.SetFont(&textFont);
	//m_lblTotal.SetWindowText(L"2005/2408(10%)");
	m_proTotal.SetRange(0,theApp.curAccount.m_maxTraffic);
	m_proTotal.SetPos(theApp.curAccount.m_curTraffic/1024/1024);

	// 调用流量统计函数开始统计流量
	AfxBeginThread(statistic_traffic, NULL);

	SetTimer(11,1000,NULL);
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
		if(fp)
		{
			pcap_breakloop(fp);
		}
	}
	m_curNIC=deviceDlg.GetCurNIC();
	CString NICDescription=GetNICDescription(m_curNIC);
	if (NICDescription.GetLength()>20)
	{
		m_lblCurDev.SetWindowText(NICDescription.Left(20)+L"...");
	}
	else
		m_lblCurDev.SetWindowText(NICDescription);

	m_lblCurDev.SetText(NICDescription);
}

void CTrafficPage::OnDestroy()
{
	CPropertyPage::OnDestroy();

	// TODO: 在此处添加消息处理程序代码
	UpdateData(TRUE);
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
	return L"点击此处选择网卡...";
}

void CTrafficPage::OnBnClickedCheckDistip()
{
	OnBnClickedCheckAutodis();
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
	UpdateData(TRUE);
	if (pLinkerPage->m_curAccountIndex>=0 && pLinkerPage->m_curAccountIndex<theApp.accounts.GetCount())
	{
		theApp.accounts[pLinkerPage->m_curAccountIndex]=theApp.curAccount;
	}
}

void CTrafficPage::OnEnChangeEditDissize()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CPropertyPage::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
	OnBnClickedCheckAutodis();
	m_proTotal.SetRange(0,theApp.curAccount.m_maxTraffic);
}

void CTrafficPage::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	m_proTotal.SetPos(theApp.curAccount.m_curTraffic/1024/1024);
	//CString temp;
	//temp.Format(L"%f",theApp.curAccount.m_curTraffic);
	//m_lblTotal.SetWindowText(temp);

	if (pLinkerPage->m_curAccountIndex>=0 && pLinkerPage->m_curAccountIndex<theApp.accounts.GetCount())
	{
		theApp.configXml.SetCurTraffic(theApp.curAccount);
	}
	CPropertyPage::OnTimer(nIDEvent);
}
