#pragma once


// CTextProgressCtrl

class CTextProgressCtrl : public CProgressCtrl
{
	DECLARE_DYNAMIC(CTextProgressCtrl)

public:
	CTextProgressCtrl();
	virtual ~CTextProgressCtrl();

protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnPaint();
	int SetPos(int nPos);
	void SetRange(short nUpper);
	int m_nPos;
	int m_nMax;
};