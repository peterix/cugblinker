#pragma once
#include "advcombobox.h"
#include "tipstatic.h"
#include "afxwin.h"
#include "afxsock.h"
#include "accountinfo.h"


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
	// 控件对象
	CTipStatic m_lblID;		// 帐号管理
	CAdvComboBox m_cboID;	// 帐号
	CEdit m_txtPwd;			// 密码
	CButton m_rdoRange;		// 访问范围
	CButton m_chkAutoStart; // 随系统启动
	CButton m_chkAutoCon;	// 自动连接
	CButton m_chkSavePwd;	// 是否保存密码
	CEdit m_txtInfo;		// 连接信息
	CButton m_btnConnect;	// 连接按钮
	CSplitButton m_btnDisCon; // 断开按钮

	// 当前帐号
	CAccountInfo curAccount;
private:
	// 用于连接的Socket
	CSocket *m_pSocket;
	// 全部断开还是只断开当前连接
	bool m_bDisconAll;
public:
	void SetBtnStat(void);
	void SetItemText(void);
	afx_msg void OnStnClickedStaticId();
	afx_msg void OnBnClickedButtonCon();
	afx_msg void OnCbnEditchangeComboId();
	afx_msg void OnCbnSelchangeComboId();
	afx_msg void OnEnChangeEditPwd();
	afx_msg void OnMenuDiscon();
	afx_msg void OnMenuDisconAll();
	afx_msg void OnUpdateDiscon(CCmdUI *pCmdUI);
	afx_msg void OnUpdateDisconall(CCmdUI *pCmdUI);
	afx_msg void OnInitMenuPopup(CMenu* pPopupMenu, UINT nIndex, BOOL bSysMenu);
	afx_msg void OnBnClickedButtonDiscon();
};
