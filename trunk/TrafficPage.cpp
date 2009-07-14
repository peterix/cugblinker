// TrafficPage.cpp : 实现文件
//

#include "stdafx.h"
#include "CUGBLinker.h"
#include "TrafficPage.h"


// CTrafficPage 对话框

IMPLEMENT_DYNAMIC(CTrafficPage, CPropertyPage)

CTrafficPage::CTrafficPage()
	: CPropertyPage(CTrafficPage::IDD)
{

}

CTrafficPage::~CTrafficPage()
{
}

void CTrafficPage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CTrafficPage, CPropertyPage)
END_MESSAGE_MAP()


// CTrafficPage 消息处理程序
