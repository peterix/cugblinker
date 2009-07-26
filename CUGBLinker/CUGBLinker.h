// CUGBLinker.h : PROJECT_NAME 应用程序的主头文件
//

#pragma once

#ifndef __AFXWIN_H__
	#error "在包含此文件之前包含“stdafx.h”以生成 PCH 文件"
#endif

#include "resource.h"		// 主符号
#include "AccountInfo.h"

// CCUGBLinkerApp:
// 有关此类的实现，请参阅 CUGBLinker.cpp
//

class CCUGBLinkerApp : public CWinApp
{
public:
	CCUGBLinkerApp();

// 重写
public:
	virtual BOOL InitInstance();

// 实现

// 帐号信息
	CArray<CAccountInfo> accounts;
	// 当前用户
	int curAccount;

	DECLARE_MESSAGE_MAP()
};

extern CCUGBLinkerApp theApp;