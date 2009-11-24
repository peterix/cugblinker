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
	CButton m_rdoRangeIn;	// 访问范围国内
	CButton m_rdoRangeOut;	// 访问范围国外
	CButton m_chkAutoStart; // 随系统启动
	CButton m_chkAutoCon;	// 自动连接
	CButton m_chkSavePwd;	// 是否保存密码
	CEdit m_txtInfo;		// 连接信息
	CButton m_btnConnect;	// 连接按钮
	CSplitButton m_btnDisCon; // 断开按钮
	CButton m_btnDisConXP;	//XP下的断开按钮

private:
	// 全部断开还是只断开当前连接，0表示断开当前，1表示断开全部
	int m_dis;
	// 是否自动连接
	BOOL m_bAutoCon;
	// 是否随系统启动
	BOOL m_bAutoStart;
	// 当前所使用系统的版本
	int m_osVersion;
public:
	// 保存当前帐号的序号
	int m_curAccountIndex;
public:
	void SetBtnStat(void);
	void InitStat(void);
	void SetItemText(void);
	void UpdateComboBox(void);
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
	afx_msg LRESULT OnUpdateInfo(WPARAM wParam = 0,LPARAM lParam = 0);
	afx_msg void OnBnClickedCheckWithsys();
	afx_msg void OnDestroy();

	afx_msg void OnBnClickedSaveAccount();
};
