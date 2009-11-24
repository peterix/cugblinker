#pragma once
#include "afxwin.h"


// CDeviceDlg �Ի���

class CDeviceDlg : public CDialog
{
	DECLARE_DYNAMIC(CDeviceDlg)

public:
	CDeviceDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CDeviceDlg();

// �Ի�������
	enum { IDD = IDD_DEVICE_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

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
