// LinkerPage.cpp : 实现文件
//

#include "stdafx.h"
#include "CUGBLinker.h"
#include "LinkerPage.h"


// CLinkerPage 对话框

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
}


BEGIN_MESSAGE_MAP(CLinkerPage, CPropertyPage)
END_MESSAGE_MAP()


// CLinkerPage 消息处理程序

BOOL CLinkerPage::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_lblID.SetText(L"单机此处管理帐号");
	m_cboID.AddString(L"080520s");
	m_cboID.AddString(L"4104211");


	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}
