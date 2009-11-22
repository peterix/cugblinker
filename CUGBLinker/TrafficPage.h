#pragma once
#include "trafficbutton.h"
#include "afxwin.h"


// CTrafficPage �Ի���

class CTrafficPage : public CPropertyPage
{
	DECLARE_DYNAMIC(CTrafficPage)

public:
	CTrafficPage();
	virtual ~CTrafficPage();

// �Ի�������
	enum { IDD = IDD_TRAFFIC_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
private:
	CFont textFont;
public:
	CTrafficButton m_btnSpeed;
	CProgressCtrl m_proTotal;
	CStatic m_lblTotal;
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	virtual BOOL OnInitDialog();
};
