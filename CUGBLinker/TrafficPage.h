#pragma once
#include "trafficbutton.h"
#include "afxwin.h"
#include "tipstatic.h"
#include "LinkerPage.h"

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
	CTipStatic m_lblCurDev;
	// ��ǰͳ������������
	CString m_curNIC;
	CEdit m_txtMaxTraffic;
	CButton m_chkShowTip;
	CButton m_chkAutoDis;
	CLinkerPage* pLinkerPage;

	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	virtual BOOL OnInitDialog();

	afx_msg void OnStnClickedStaticNic();
	afx_msg void OnDestroy();
	CString GetNICDescription(CString nic);
	afx_msg void OnBnClickedCheckDistip();
	afx_msg void OnBnClickedCheckAutodis();
	afx_msg void OnEnChangeEditDissize();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
};
