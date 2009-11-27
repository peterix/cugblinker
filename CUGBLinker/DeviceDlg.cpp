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
	, m_curNIC(_T(""))
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
	CString curNicDes;
	int curNicIndex=0;
	pcap_if_t* alldevs=finddevs();
	pcap_if_t* d=NULL;
	int i=0;
	for(d = alldevs; d != NULL; d = d->next,i++)
	{
		m_lstDev.AddString(CString(d->description));
		if (CString(d->name)==m_curNIC)
		{
			curNicIndex=i;
		}
	}
	if (alldevs)
	{
		pcap_freealldevs(alldevs);
	}
	m_lstDev.SetCurSel(curNicIndex);
	OnLbnSelchangeListDevice();
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

void CDeviceDlg::OnLbnSelchangeListDevice()
{
	// TODO: 在此添加控件通知处理程序代码
	pcap_if_t* alldevs=finddevs();
	pcap_if_t* d=NULL;
	CString nicDes,strInfo;
	int index=m_lstDev.GetCurSel();
	if (index>=0)
	{
		m_lstDev.GetText(index,nicDes);
	}
	for(d = alldevs; d != NULL; d = d->next)
	{
		if (nicDes==CString(d->description))
		{
			m_curNIC=CString(d->name);
			strInfo=CString(d->name);
			strInfo+=CString(L"\r\n\r\nDescription: ")+CString(d->description);
			strInfo+=CString(L"\r\nLoopback: ")+CString((d->flags & PCAP_IF_LOOPBACK)?"yes":"no");
			for(pcap_addr_t *a=d->addresses;a;a=a->next) 
			{
				char ip6str[128];
				CString temp;
				temp.Format(L"\r\nAddress Family: #%d",a->addr->sa_family);
				strInfo+=temp;
				switch(a->addr->sa_family)
				{
				case AF_INET:
					strInfo+=CString(L"\r\nAddress Family Name: AF_INET");
					if (a->addr)
						strInfo+=CString(L"\r\nAddress: ")+CString(iptos(((struct sockaddr_in *)a->addr)->sin_addr.s_addr));
					if (a->netmask)
						strInfo+=CString(L"\r\nNetmask: ")+CString(iptos(((struct sockaddr_in *)a->netmask)->sin_addr.s_addr));
					if (a->broadaddr)
						strInfo+=CString(L"\r\nBroadcast Address: ")+CString(iptos(((struct sockaddr_in *)a->broadaddr)->sin_addr.s_addr));
					if (a->dstaddr)
						strInfo+=CString(L"\r\nDestination Address: ")+CString(iptos(((struct sockaddr_in *)a->dstaddr)->sin_addr.s_addr));
					break;

				case AF_INET6:
					strInfo+=CString(L"\r\nAddress Family Name: AF_INET6");
					if (a->addr)
						strInfo+=CString(L"\r\nAddress: ")+CString(ip6tos(a->addr, ip6str, sizeof(ip6str)));
					break;

				default:
					strInfo+=CString(L"\r\nAddress Family Name: Unknown");
					break;
				}
			}
			m_txtDevInfo.SetWindowText(strInfo);
			break;
		}
	}
	if (alldevs)
	{
		pcap_freealldevs(alldevs);
	}
}

void CDeviceDlg::SetCurNIC(CString curNIC)
{
	m_curNIC=curNIC;
}

CString CDeviceDlg::GetCurNIC(void)
{
	return m_curNIC;
}
