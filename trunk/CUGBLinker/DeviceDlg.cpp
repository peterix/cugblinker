// DeviceDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "CUGBLinker.h"
#include "DeviceDlg.h"
#include "CUGBLinkerDlg.h"


// CDeviceDlg 对话框

IMPLEMENT_DYNAMIC(CDeviceDlg, CDialog)

CDeviceDlg::CDeviceDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDeviceDlg::IDD, pParent)
{

}

CDeviceDlg::~CDeviceDlg()
{
}

void CDeviceDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_DEVICE, m_lstDev);
	DDX_Control(pDX, IDC_EDIT_DEVICE, m_txtDevInfo);
}


BEGIN_MESSAGE_MAP(CDeviceDlg, CDialog)
	ON_LBN_SELCHANGE(IDC_LIST_DEVICE, &CDeviceDlg::OnLbnSelchangeListDevice)
END_MESSAGE_MAP()


// CDeviceDlg 消息处理程序

BOOL CDeviceDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  在此添加额外的初始化
	CCUGBLinkerDlg* pMainWnd=(CCUGBLinkerDlg*)theApp.m_pMainWnd;
	pcap_if_t* alldevs=finddevs();
	pcap_if_t* d=NULL;
	for(d = alldevs; d != NULL; d = d->next)
	{
		m_lstDev.AddString(CString(d->description));
	}
	m_lstDev.SetCurSel(0);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CDeviceDlg::OnLbnSelchangeListDevice()
{
	// TODO: 在此添加控件通知处理程序代码
	pcap_if_t* alldevs=finddevs();
	pcap_if_t* d=NULL;
	for(d = alldevs; d != NULL; d = d->next)
	{
		CString nicDes;
		m_lstDev.GetWindowText(nicDes);
		if (nicDes==CString(d->description))
		{

		}
	}
}
