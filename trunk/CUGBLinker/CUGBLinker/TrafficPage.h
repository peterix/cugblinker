#pragma once


// CTrafficPage 对话框

class CTrafficPage : public CPropertyPage
{
	DECLARE_DYNAMIC(CTrafficPage)

public:
	CTrafficPage();
	virtual ~CTrafficPage();

// 对话框数据
	enum { IDD = IDD_TRAFFIC_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
};
