#pragma once
#include "afxwin.h"


// CAccountDlg 对话框

class CAccountDlg : public CDialog
{
	DECLARE_DYNAMIC(CAccountDlg)

public:
	CAccountDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CAccountDlg();

// 对话框数据
	enum { IDD = IDD_ACCOUNT_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CListBox m_lstAccounts;
	CButton m_btnDel;
	CButton m_btnDelAll;
	afx_msg void OnBnClickedDelButton();
	afx_msg void OnBnClickedDelallButton();
	afx_msg void OnLbnSelchangeAccountList();
};
