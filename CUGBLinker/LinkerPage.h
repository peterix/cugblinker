#pragma once
#include "advcombobox.h"
#include "tipstatic.h"
#include "afxwin.h"
#include "afxsock.h"


// CLinkerPage 对话框

class CLinkerPage  : public CPropertyPage
{
	DECLARE_DYNAMIC(CLinkerPage)

public:
	CLinkerPage();
	virtual ~CLinkerPage();

// 对话框数据
	enum { IDD = IDD_LINKER_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();

// 界面控件对象
public:
	// 帐号下拉列表
	CAdvComboBox m_cboID;
	CTipStatic m_lblID;
	afx_msg void OnStnClickedStaticId();
	CButton m_btnConnect;
	CButton m_btnDisConnect;
	afx_msg void OnBnClickedButtonCon();
private:
	// //用于连接的Socket
	CSocket m_socket;
};
