#pragma once


// CAdvComboBox

class CAdvComboBox : public CComboBox
{
	DECLARE_DYNAMIC(CAdvComboBox)

public:
	CAdvComboBox();
	virtual ~CAdvComboBox();

protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
private:
	bool m_bAutoComplete;
public:
	afx_msg void OnCbnEditupdate();
};


