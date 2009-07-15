// TipStatic.cpp : ʵ���ļ�
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



// CTipStatic ��Ϣ�������



BOOL CTipStatic::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	::SetCursor(::LoadCursor(NULL,IDC_HAND));
	return TRUE;
}

HBRUSH CTipStatic::CtlColor(CDC* /*pDC*/, UINT /*nCtlColor*/)
{
	// TODO:  �ڴ˸��� DC ���κ�����
	DWORD dwStyle = GetStyle();
	if (!(dwStyle & SS_NOTIFY))
	{
		// Turn on notify flag to get mouse messages and STN_CLICKED.
		// Otherwise, I'll never get any mouse clicks!
		::SetWindowLong(m_hWnd, GWL_STYLE, dwStyle | SS_NOTIFY);
	}

	// TODO:  �����Ӧ���ø����Ĵ�������򷵻ط� null ����
	return NULL;
}

BOOL CTipStatic::PreTranslateMessage(MSG* pMsg)
{
	// TODO: �ڴ����ר�ô����/����û���
	m_tooltip.RelayEvent(pMsg);

	return CStatic::PreTranslateMessage(pMsg);
}

void CTipStatic::PreSubclassWindow()
{
	// TODO: �ڴ����ר�ô����/����û���
	m_tooltip.Create(this);
	m_tooltip.Activate(TRUE);
	//m_tooltip.AddTool(this, "�����˴������ʺ�");
	//m_tooltip.SetMaxTipWidth(100);
	
	CStatic::PreSubclassWindow();
}

void CTipStatic::SetText(CString text)
{
	m_tooltip.AddTool(this,text);
}
