
// testDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "test.h"
#include "testDlg.h"
#include <afxinet.h>
#include "tinyxml.h"
#include "tinystr.h"
#include "ConfigXml.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CtestDlg �Ի���




CtestDlg::CtestDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CtestDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CtestDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CtestDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON1, &CtestDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CtestDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CtestDlg::OnBnClickedButton3)
END_MESSAGE_MAP()


// CtestDlg ��Ϣ�������

BOOL CtestDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CtestDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CtestDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
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

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CtestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CtestDlg::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	configXml.Init();


//	TiXmlDocument doc("CUGBLinker.xml");
//	TiXmlHandle hDoc(&doc);
//	if(!doc.LoadFile())
//	{
//		TiXmlDeclaration * decl = new TiXmlDeclaration( "1.0", "", "" );
//		doc.LinkEndChild(decl);
//		TiXmlElement * root = new TiXmlElement( "CUGBLinker" );
//		doc.LinkEndChild(root);
//		TiXmlElement * accounts = new TiXmlElement( "Account" );
//		root->LinkEndChild(accounts);
//		accounts->SetAttribute("ID","12345");
//		TiXmlElement * autoConnect = new TiXmlElement( "AutoConnect" );
//		accounts->LinkEndChild(autoConnect);
//	}
////	else
//	{
//		TiXmlElement* user=hDoc.FirstChildElement().FirstChildElement().Element();
//		if (user)
//		{
//		//	CString id=user->Attribute("ID");
//			user->SetAttribute("ID","2");
//		}
//	}
//	doc.SaveFile();


	//CString *pFilename=new CString(L"CUGBLinker.xml");
	//string strFileName = converToMultiChar(( LPCWSTR )pFilename);
	//TiXmlDocument doc;
	//if (!doc.LoadFile(strFileName.c_str()))
	//{
	//	TiXmlDeclaration* decl = new TiXmlDeclaration( "1.0", "UTF-8", "" );  
	//	doc.LinkEndChild( decl );

	//	string strTemp;
	//	string strRoot;
	//	CString strRootName = theApp.m_strTerminalName + _T("-FlashList");
	//	CString strDateTime = _T("");
	//	CString strSend = strFname;
	//	CString strInfo = _T("Flash");
	//	CTime time = CTime::GetCurrentTime();
	//	strDateTime = time.Format(_T("%Y-%m-%d %H:%M:%S"));
	//	strTemp = converToMultiChar(( LPCWSTR )strSend);

	//	strRoot = converToMultiChar(( LPCWSTR )strRootName);
	//	TiXmlElement* root = new TiXmlElement(strRoot.c_str());
	//	doc.LinkEndChild(root);

	//	TiXmlElement * msgs = new TiXmlElement( strTemp.c_str() );
	//	root->LinkEndChild(msgs);

	//	TiXmlElement * flashInfo;
	//	strTemp = theApp.converToMultiChar((LPCWSTR)strInfo);
	//	flashInfo = new TiXmlElement(strTemp.c_str());
	//	msgs->LinkEndChild(flashInfo);
	//	flashInfo->SetAttribute("PlayTime",iPlayTime);
	//	strTemp = theApp.converToMultiChar(( LPCWSTR )strDateTime);
	//	flashInfo->SetAttribute("PlayDateTime",strTemp.c_str());

	//	doc.SaveFile(strFileName.c_str());
	//}
	//else
	//{
	//	TiXmlHandle hDoc(&doc);
	//	TiXmlElement* pElem;
	//	TiXmlHandle hRoot(0);
	//	pElem = hDoc.FirstChildElement().Element();
	//	string strTemp;
	//	string sFname;
	//	sFname = theApp.converToMultiChar((LPCWSTR)strFname);
	//	CString strInfo = _T("Flash");
	//	CString strDateTime = _T("");
	//	CTime time = CTime::GetCurrentTime();
	//	strDateTime = time.Format(_T("%Y-%m-%d %H:%M:%S"));
	//	hRoot = TiXmlHandle(pElem);

	//	pElem = hRoot.FirstChild(sFname.c_str()).Element();
	//	if (!pElem)
	//	{
	//		TiXmlElement * msgs = new TiXmlElement(sFname.c_str());
	//		hDoc.FirstChildElement().Element()->LinkEndChild(msgs);

	//		TiXmlElement * flashInfo;
	//		strTemp = theApp.converToMultiChar((LPCWSTR)strInfo);
	//		flashInfo = new TiXmlElement(strTemp.c_str());
	//		msgs->LinkEndChild(flashInfo);
	//		flashInfo->SetAttribute("PlayTime",iPlayTime);
	//		strTemp = theApp.converToMultiChar(( LPCWSTR )strDateTime);
	//		flashInfo->SetAttribute("PlayDateTime",strTemp.c_str());
	//	}
	//	else
	//	{
	//		TiXmlElement * flashInfo;
	//		strTemp = theApp.converToMultiChar((LPCWSTR)strInfo);
	//		flashInfo = new TiXmlElement(strTemp.c_str());
	//		pElem->LinkEndChild(flashInfo);
	//		flashInfo->SetAttribute("PlayTime",iPlayTime);
	//		strTemp = theApp.converToMultiChar(( LPCWSTR )strDateTime);
	//		flashInfo->SetAttribute("PlayDateTime",strTemp.c_str());
	//	}

	//	doc.SaveFile(strFileName.c_str());
	//}
}

void CtestDlg::OnBnClickedButton2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	configXml.SetActiveAccount(1);
	configXml.SetAutoConnect(0);
	configXml.SetDisBtnStatus(1);
	configXml.SaveFile();
}

void CtestDlg::OnBnClickedButton3()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	int a;
	a=configXml.GetActiveAccount();
	a=configXml.GetAutoConnect();
	a=configXml.GetDisBtnStatus();
}
