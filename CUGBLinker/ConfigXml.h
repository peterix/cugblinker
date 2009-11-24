#pragma once

#include "tinyxml.h"
#include "tinystr.h"
#include "AccountInfo.h"

class CConfigXml
{
public:
	CConfigXml(void);
	~CConfigXml(void);

public:
	TiXmlDocument doc;

public:
	void Init(void);
	void SaveFile(void);
	void SetAccount(CAccountInfo& accountInfo);
	CAccountInfo GetAccount(int i=0);
	void DelAccount(int i);
	void SetActiveAccount(int val);
	int GetActiveAccount(void);
	void SetAutoConnect(int val);
	int GetAutoConnect(void);
	void SetDisBtnStatus(int val);
	int GetDisBtnStatus(void);
	int GetAccountCount(void);
	void SetCurNIC(CString nic);
	CString GetCurNIC(void);

	void SetCurTraffic(CAccountInfo& accountInfo);
	//double GetCurTraffic(int i);
	//void SetMaxTraffic(int i,double maxTraffic);
	//double GetMaxTraffic(int i);
	//void SetShowTip(int i,int showTip);
	//int GetShowTip(int i);
	//void SetAutoDis(int i,int autoDis);
	//int GetAutoDis(int i);
};
