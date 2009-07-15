// TipStatic.cpp : 实现文件
//

#include "stdafx.h"
#include "TipStatic.h"


// CTipStatic

IMPLEMENT_DYNAMIC(CTipStatic, CStatic)

CTipStatic::CTipStatic()
{

}

CTipStatic::~CTipStatic()
{
}


BEGIN_MESSAGE_MAP(CTipStatic, CStatic)
	ON_WM_SETCURSOR()
	ON_WM_CTLCOLOR_REFLECT()
END_MESSAGE_MAP()



// CTipStatic 消息处理程序



BOOL CTipStatic::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	::SetCursor(::LoadCursor(NULL,IDC_HAND));
	return TRUE;
}

HBRUSH CTipStatic::CtlColor(CDC* /*pDC*/, UINT /*nCtlColor*/)
{
	// TODO:  在此更改 DC 的任何属性
	DWORD dwStyle = GetStyle();
	if (!(dwStyle & SS_NOTIFY))
	{
		// Turn on notify flag to get mouse messages and STN_CLICKED.
		// Otherwise, I'll never get any mouse clicks!
		::SetWindowLong(m_hWnd, GWL_STYLE, dwStyle | SS_NOTIFY);
	}

	// TODO:  如果不应调用父级的处理程序，则返回非 null 画笔
	return NULL;
}

BOOL CTipStatic::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类
	m_tooltip.RelayEvent(pMsg);

	return CStatic::PreTranslateMessage(pMsg);
}

void CTipStatic::PreSubclassWindow()
{
	// TODO: 在此添加专用代码和/或调用基类
	m_tooltip.Create(this);
	m_tooltip.Activate(TRUE);
	//m_tooltip.AddTool(this, "单击此处管理帐号");
	//m_tooltip.SetMaxTipWidth(100);
	
	CStatic::PreSubclassWindow();
}

void CTipStatic::SetText(CString text)
{
	m_tooltip.AddTool(this,text);
}
