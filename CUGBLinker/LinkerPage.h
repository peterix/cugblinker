#pragma once
#include "advcombobox.h"
#include "tipstatic.h"


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
	// �ʺ������б�
	CAdvComboBox m_cboID;
	CTipStatic m_lblID;
	afx_msg void OnStnClickedStaticId();
};
