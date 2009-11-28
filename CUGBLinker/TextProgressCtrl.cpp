// MyProgressCtrl.cpp : 实现文件
//

#include "stdafx.h"
#include "TextProgressCtrl.h"


// CTextProgressCtrl

IMPLEMENT_DYNAMIC(CTextProgressCtrl, CProgressCtrl)

CTextProgressCtrl::CTextProgressCtrl()
: m_nPos(0)
, m_nMax(0)
{
}

CTextProgressCtrl::~CTextProgressCtrl()
{
}


BEGIN_MESSAGE_MAP(CTextProgressCtrl, CProgressCtrl)
	ON_WM_PAINT()
END_MESSAGE_MAP()



// CTextProgressCtrl 消息处理程序



void CTextProgressCtrl::OnPaint()
{
	CProgressCtrl::OnPaint();
	CDC *pDC = CProgressCtrl::GetDC();
	pDC->SetBkMode(TRANSPARENT);
	CString temp;
	temp.Format(L"%4d/%d(%.1f%%)",m_nPos,m_nMax,(float)m_nPos/m_nMax*100);
	pDC->TextOut(50,6,temp);
	ReleaseDC(pDC);
}

int CTextProgressCtrl::SetPos(int nPos)
{
	int res=CProgressCtrl::SetPos(nPos);;
	m_nPos=nPos;
	Invalidate(TRUE);
	return res;
}

void CTextProgressCtrl::SetRange(short nUpper)
{
	m_nMax=nUpper;
	CProgressCtrl::SetRange(0,nUpper);
	Invalidate(TRUE);
}
