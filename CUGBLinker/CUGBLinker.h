// CUGBLinker.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������
#include "AccountInfo.h"

// CCUGBLinkerApp:
// �йش����ʵ�֣������ CUGBLinker.cpp
//

class CCUGBLinkerApp : public CWinApp
{
public:
	CCUGBLinkerApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

// �ʺ���Ϣ
	CArray<CAccountInfo> accounts;
	// ��ǰ�ʺ�
	CAccountInfo curAccount;
	// ��ǰ�ʺ����
	int curAccountNum;

	DECLARE_MESSAGE_MAP()
	virtual BOOL PreTranslateMessage(MSG* pMsg);
};

extern CCUGBLinkerApp theApp;