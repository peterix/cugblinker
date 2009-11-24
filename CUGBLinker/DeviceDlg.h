#pragma once
#include "afxwin.h"


// CDeviceDlg 对话框

class CDeviceDlg : public CDialog
{
	DECLARE_DYNAMIC(CDeviceDlg)

public:
	CDeviceDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDeviceDlg();

// 对话框数据
	enum { IDD = IDD_DEVICE_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CListBox m_lstDev;
	CEdit m_txtDevInfo;
	virtual BOOL OnInitDialog();
	afx_msg void OnLbnSelchangeListDevice();
	CString m_curNIC;
	void SetCurNIC(CString curNIC);
	CString GetCurNIC(void);
};
