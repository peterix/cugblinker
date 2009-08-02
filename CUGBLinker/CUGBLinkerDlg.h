// CUGBLinkerDlg.h : ͷ�ļ�
//

#pragma once

#include "LinkerPage.h"
#include "TrafficPage.h"

// CCUGBLinkerDlg �Ի���
class CCUGBLinkerDlg : public CDialog
{
// ����
public:
	CCUGBLinkerDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_CUGBLINKER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:
	CPropertySheet m_sheet;
	CLinkerPage m_linkerPage;//��������ҳ��
	CTrafficPage m_trafficPage;//������Ϣҳ��
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg LRESULT OnShowTask(WPARAM wParam,LPARAM lParam);
	NOTIFYICONDATA nid;
	afx_msg void OnClose();
};
