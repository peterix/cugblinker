// CUGBLinkerDlg.h : 头文件
//

#pragma once

#include "LinkerPage.h"
#include "TrafficPage.h"

// CCUGBLinkerDlg 对话框
class CCUGBLinkerDlg : public CDialog
{
// 构造
public:
	CCUGBLinkerDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_CUGBLINKER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:
	CPropertySheet m_sheet;
	CLinkerPage m_linkerPage; // 网关连接页面
	CTrafficPage m_trafficPage; // 流量信息页面
	NOTIFYICONDATA nid;
	pcap_if_t* alldevs; // 网卡
	
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg LRESULT OnShowTask(WPARAM wParam,LPARAM lParam);
	afx_msg LRESULT OnUpdateNotify(WPARAM wParam = 0,LPARAM lParam = 0);
	afx_msg void OnClose();
};
