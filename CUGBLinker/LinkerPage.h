#pragma once
#include "advcombobox.h"
#include "tipstatic.h"
#include "afxwin.h"
#include "afxsock.h"
#include "accountinfo.h"


// CLinkerPage �Ի���

class CLinkerPage  : public CPropertyPage
{
	DECLARE_DYNAMIC(CLinkerPage)

public:
	CLinkerPage();
	virtual ~CLinkerPage();

// �Ի�������
	enum { IDD = IDD_LINKER_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();

// ����ؼ�����
public:
	// �ؼ�����
	CTipStatic m_lblID;		// �ʺŹ���
	CAdvComboBox m_cboID;	// �ʺ�
	CEdit m_txtPwd;			// ����
	CButton m_rdoRange;		// ���ʷ�Χ
	CButton m_chkAutoStart; // ��ϵͳ����
	CButton m_chkAutoCon;	// �Զ�����
	CButton m_chkSavePwd;	// �Ƿ񱣴�����
	CEdit m_txtInfo;		// ������Ϣ
	CButton m_btnConnect;	// ���Ӱ�ť
	CSplitButton m_btnDisCon; // �Ͽ���ť

	// ��ǰ�ʺ�
	CAccountInfo curAccount;
private:
	// �������ӵ�Socket
	CSocket *m_pSocket;
	// ȫ���Ͽ�����ֻ�Ͽ���ǰ����
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
