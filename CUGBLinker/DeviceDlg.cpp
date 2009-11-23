// DeviceDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "CUGBLinker.h"
#include "DeviceDlg.h"
#include "CUGBLinkerDlg.h"


// CDeviceDlg �Ի���

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


// CDeviceDlg ��Ϣ�������

BOOL CDeviceDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��
	CCUGBLinkerDlg* pMainWnd=(CCUGBLinkerDlg*)theApp.m_pMainWnd;
	pcap_if_t* alldevs=finddevs();
	pcap_if_t* d=NULL;
	for(d = alldevs; d != NULL; d = d->next)
	{
		m_lstDev.AddString(CString(d->description));
	}
	m_lstDev.SetCurSel(0);
	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CDeviceDlg::OnLbnSelchangeListDevice()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
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
