#pragma once
#include "afxwin.h"


// CAccountDlg �Ի���

class CAccountDlg : public CDialog
{
	DECLARE_DYNAMIC(CAccountDlg)

public:
	CAccountDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CAccountDlg();

// �Ի�������
	enum { IDD = IDD_ACCOUNT_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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
