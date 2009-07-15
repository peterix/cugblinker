#pragma once
#include "afxcmn.h"


// CTipStatic

class CTipStatic : public CStatic
{
	DECLARE_DYNAMIC(CTipStatic)

public:
	CTipStatic();
	virtual ~CTipStatic();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg HBRUSH CtlColor(CDC* /*pDC*/, UINT /*nCtlColor*/);
	// TipÃ· æ
	CToolTipCtrl m_tooltip;
	virtual BOOL PreTranslateMessage(MSG* pMsg);
protected:
	virtual void PreSubclassWindow();
public:
	void SetText(CString text);
};


