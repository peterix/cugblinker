// CUGBLinkerDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "CUGBLinker.h"
#include "CUGBLinkerDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CCUGBLinkerDlg �Ի���




CCUGBLinkerDlg::CCUGBLinkerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCUGBLinkerDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CCUGBLinkerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CCUGBLinkerDlg, CDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


// CCUGBLinkerDlg ��Ϣ�������

BOOL CCUGBLinkerDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	
	// ������ӽ���
	m_sheet.AddPage(&m_linkerPage);
	// �������ͳ�ƽ���
	//m_sheet.AddPage(&m_trafficPage);

	m_sheet.Create(this, WS_CHILD | WS_VISIBLE, WS_EX_CONTROLPARENT);
	//����TabControl��С
	//���һ������
	const int margin=10;
	CRect frameRect,m_sheetRect;
	GetClientRect(&frameRect);
	frameRect.DeflateRect(margin,margin);
	m_sheet.MoveWindow(frameRect);
	m_sheet.GetClientRect(&m_sheetRect);
	m_sheet.GetTabControl()->MoveWindow(m_sheetRect);
	m_sheet.SetActivePage(0);
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CCUGBLinkerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ��������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù����ʾ��
//
HCURSOR CCUGBLinkerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

