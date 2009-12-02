#include "StdAfx.h"
#include "ConfigXml.h"

CConfigXml::CConfigXml(void)
{
}

CConfigXml::~CConfigXml(void)
{
}

void CConfigXml::Init(void)
{
	HRESULT hr;
	TCHAR szPath[MAX_PATH];
		if (SUCCEEDED (hr = SHGetFolderPathAndSubDir(NULL,                // hWnd	
			CSIDL_APPDATA|CSIDL_FLAG_CREATE,       // csidl
			NULL,                // hToken
			SHGFP_TYPE_CURRENT,  // dwFlags
			TEXT("CUGBLinker"),    // pszSubDir
			szPath)))            // pszPath
		{
			PathAppend(szPath, TEXT("CUGBLinker.xml"));
		}

	CStringA path(szPath);
	if(!doc.LoadFile(path))
	{
		//AfxMessageBox(CString(path));
		TiXmlDeclaration* decl = new TiXmlDeclaration( "1.0", "UTF-8", "" );
		doc.LinkEndChild(decl);
		TiXmlElement* root = new TiXmlElement( "CUGBLinker" );
		doc.LinkEndChild(root);
		TiXmlElement* common = new TiXmlElement("Common");
		root->LinkEndChild(common);
		TiXmlElement* activeAccount = new TiXmlElement("ActiveAccount");
		activeAccount->SetAttribute("value",0);
		common->LinkEndChild(activeAccount);
		TiXmlElement* autoConnect = new TiXmlElement("AutoConnect");
		autoConnect->SetAttribute("value",0);
		common->LinkEndChild(autoConnect);
		TiXmlElement* disBtnStatus = new TiXmlElement("DisBtnStatus");
		disBtnStatus->SetAttribute("value",0);
		common->LinkEndChild(disBtnStatus);
		TiXmlElement* curNIC = new TiXmlElement("CurNIC");
		curNIC->SetAttribute("value","");
		common->LinkEndChild(curNIC);
		TiXmlElement* date = new TiXmlElement("Date");
		date->SetAttribute("value","");
		common->LinkEndChild(date);
		TiXmlElement* accounts = new TiXmlElement("Accounts");
		root->LinkEndChild(accounts);
		doc.SaveFile();
	}
	else
	{
		TiXmlHandle hDoc(&doc);
		if (hDoc.FirstChild("CUGBLinker").ToElement()==NULL)
		{
			TiXmlElement* root = new TiXmlElement( "CUGBLinker" );
			doc.LinkEndChild(root);
		}
		if (hDoc.FirstChild("CUGBLinker").FirstChild("Common").ToElement()==NULL)
		{
			TiXmlElement* common = new TiXmlElement("Common");
			hDoc.FirstChild("CUGBLinker").ToElement()->LinkEndChild(common);
		}
		if (hDoc.FirstChild("CUGBLinker").FirstChild("Accounts").ToElement()==NULL)
		{
			TiXmlElement* accounts = new TiXmlElement("Accounts");
			hDoc.FirstChild("CUGBLinker").ToElement()->LinkEndChild(accounts);
		}
	}
}

void CConfigXml::SaveFile(void)
{
	doc.SaveFile();
}

void CConfigXml::SetAccount(CAccountInfo& accountInfo)
{
	TiXmlHandle hDoc(&doc);
	CStringA accountName="Account_";
	accountName+=accountInfo.m_username;
	char* name=accountName.GetBuffer();
	TiXmlElement* account=hDoc.FirstChild("CUGBLinker").FirstChild("Accounts").FirstChild(name).ToElement();
	if (account==NULL)
	{
		TiXmlElement* newAccount=new TiXmlElement(name);
		TiXmlElement* accounts=hDoc.FirstChild("CUGBLinker").FirstChild("Accounts").ToElement();
		accounts->LinkEndChild(newAccount);
	}
	account=hDoc.FirstChild("CUGBLinker").FirstChild("Accounts").FirstChild(name).ToElement();
	accountName.ReleaseBuffer();
	
	CStringA pwd;
	if (accountInfo.m_savePwd)
	{
		pwd=CStringA(accountInfo.m_password);	
	}
	else
		pwd="";
	account->SetAttribute("password",pwd.GetBuffer());
	pwd.ReleaseBuffer();
	
	account->SetAttribute("range",accountInfo.m_range);
	account->SetAttribute("savePwd",accountInfo.m_savePwd);
	account->SetDoubleAttribute("curTraffic",accountInfo.m_curTraffic);
	account->SetAttribute("maxTraffic",accountInfo.m_maxTraffic);
	account->SetAttribute("showTip",accountInfo.m_showTip);
	account->SetAttribute("autoDis",accountInfo.m_autoDis);
}

CAccountInfo CConfigXml::GetAccount(int i)
{
	CAccountInfo accountInfo;
	TiXmlHandle hDoc(&doc);
	TiXmlElement* account=hDoc.FirstChild("CUGBLinker").FirstChild("Accounts").Child(i).ToElement();
	if (account)
	{
		accountInfo.m_username=account->Value();
		accountInfo.m_username=accountInfo.m_username.Mid(8);
		accountInfo.m_password=account->Attribute("password");
		account->Attribute("range",&(accountInfo.m_range));
		account->Attribute("savePwd",&(accountInfo.m_savePwd));
		account->Attribute("curTraffic",&(accountInfo.m_curTraffic));
		account->Attribute("maxTraffic",&(accountInfo.m_maxTraffic));
		account->Attribute("showTip",&(accountInfo.m_showTip));
		account->Attribute("autoDis",&(accountInfo.m_autoDis));
	}
	return accountInfo;
}

void CConfigXml::DelAccount(int i)
{
	TiXmlHandle hDoc(&doc);
	TiXmlElement* account=hDoc.FirstChild("CUGBLinker").FirstChild("Accounts").Child(i).ToElement();
	if (account)
	{
		account->Parent()->RemoveChild(account);
	}
}

void CConfigXml::SetActiveAccount(int val)
{
	TiXmlHandle hDoc(&doc);
	TiXmlElement* activeAccount=hDoc.FirstChild("CUGBLinker").FirstChild("Common").FirstChild("ActiveAccount").ToElement();
	if (activeAccount==NULL)
	{
		TiXmlElement* common=hDoc.FirstChild("CUGBLinker").FirstChild("Common").ToElement();
		if (common)
		{
			TiXmlElement* newElement = new TiXmlElement("ActiveAccount");
			newElement->SetAttribute("value",val);
			common->LinkEndChild(newElement);
		}
	}
	else
	{
		activeAccount->SetAttribute("value",val);
	}
}

int CConfigXml::GetActiveAccount(void)
{
	int ret=0;
	TiXmlHandle hDoc(&doc);
	TiXmlElement* activeAccount=hDoc.FirstChild("CUGBLinker").FirstChild("Common").FirstChild("ActiveAccount").ToElement();
	if (activeAccount)
	{
		activeAccount->Attribute("value",&ret);
	}
	return ret;
}

void CConfigXml::SetAutoConnect(int val)
{
	TiXmlHandle hDoc(&doc);
	TiXmlElement* autoConnect=hDoc.FirstChild("CUGBLinker").FirstChild("Common").FirstChild("AutoConnect").ToElement();
	if (autoConnect==NULL)
	{
		TiXmlElement* common=hDoc.FirstChild("CUGBLinker").FirstChild("Common").ToElement();
		if (common)
		{
			TiXmlElement* newElement = new TiXmlElement("AutoConnect");
			newElement->SetAttribute("value",val);
			common->LinkEndChild(newElement);
		}
	}
	else
	{
		autoConnect->SetAttribute("value",val);
	}
}

int CConfigXml::GetAutoConnect(void)
{
	int ret=0;
	TiXmlHandle hDoc(&doc);
	TiXmlElement* autoConnect=hDoc.FirstChild("CUGBLinker").FirstChild("Common").FirstChild("AutoConnect").ToElement();
	if (autoConnect)
	{
		autoConnect->Attribute("value",&ret);
	}
	return ret;
}

void CConfigXml::SetDisBtnStatus(int val)
{
	TiXmlHandle hDoc(&doc);
	TiXmlElement* disBtnStatus=hDoc.FirstChild("CUGBLinker").FirstChild("Common").FirstChild("DisBtnStatus").ToElement();
	if (disBtnStatus==NULL)
	{
		TiXmlElement* common=hDoc.FirstChild("CUGBLinker").FirstChild("Common").ToElement();
		if (common)
		{
			TiXmlElement* newElement = new TiXmlElement("DisBtnStatus");
			newElement->SetAttribute("value",val);
			common->LinkEndChild(newElement);
		}
	}
	else
	{
		disBtnStatus->SetAttribute("value",val);
	}
}

int CConfigXml::GetDisBtnStatus(void)
{
	int ret=0;
	TiXmlHandle hDoc(&doc);
	TiXmlElement* disBtnStatus=hDoc.FirstChild("CUGBLinker").FirstChild("Common").FirstChild("DisBtnStatus").ToElement();
	if (disBtnStatus)
	{
		disBtnStatus->Attribute("value",&ret);
	}
	return ret;
}

int CConfigXml::GetAccountCount(void)
{
	int len=0;
	TiXmlHandle hDoc(&doc);
	TiXmlHandle accounts=hDoc.FirstChild("CUGBLinker").FirstChild("Accounts");
	while(accounts.Child(len).ToElement())
	{
		len++;
	}

	return len;
}

void CConfigXml::SetCurNIC(CString nic)
{
	TiXmlHandle hDoc(&doc);
	TiXmlElement* curNIC=hDoc.FirstChild("CUGBLinker").FirstChild("Common").FirstChild("CurNIC").ToElement();
	if (curNIC==NULL)
	{
		TiXmlElement* common=hDoc.FirstChild("CUGBLinker").FirstChild("Common").ToElement();
		if (common)
		{
			TiXmlElement* newElement = new TiXmlElement("CurNIC");
			CStringA temp=CStringA(nic);
			newElement->SetAttribute("value",temp.GetBuffer());
			temp.ReleaseBuffer();
			common->LinkEndChild(newElement);
		}
	}
	else
	{
		CStringA temp=CStringA(nic);
		curNIC->SetAttribute("value",temp.GetBuffer());
		temp.ReleaseBuffer();
	}
}

CString CConfigXml::GetCurNIC(void)
{
	CString nic;
	TiXmlHandle hDoc(&doc);
	TiXmlElement* curNIC=hDoc.FirstChild("CUGBLinker").FirstChild("Common").FirstChild("CurNIC").ToElement();
	if (curNIC)
	{
		nic=curNIC->Attribute("value");
	}
	return nic;
}

void CConfigXml::SetCurTraffic(CAccountInfo& accountInfo)
{
	TiXmlHandle hDoc(&doc);
	CStringA accountName="Account_";
	accountName+=accountInfo.m_username;
	char* name=accountName.GetBuffer();
	TiXmlElement* account=hDoc.FirstChild("CUGBLinker").FirstChild("Accounts").FirstChild(name).ToElement();
	if (account)
	{
		account->SetDoubleAttribute("curTraffic",accountInfo.m_curTraffic);
	}
}

void CConfigXml::SetDate(CString date)
{
	TiXmlHandle hDoc(&doc);
	TiXmlElement* dateElement=hDoc.FirstChild("CUGBLinker").FirstChild("Common").FirstChild("Date").ToElement();
	if (dateElement==NULL)
	{
		TiXmlElement* common=hDoc.FirstChild("CUGBLinker").FirstChild("Common").ToElement();
		if (common)
		{
			TiXmlElement* newElement = new TiXmlElement("Date");
			CStringA temp=CStringA(date);
			newElement->SetAttribute("value",temp.GetBuffer());
			temp.ReleaseBuffer();
			common->LinkEndChild(newElement);
		}
	}
	else
	{
		CStringA temp=CStringA(date);
		dateElement->SetAttribute("value",temp.GetBuffer());
		temp.ReleaseBuffer();
	}
}

CString CConfigXml::GetDate()
{
	CString date;
	TiXmlHandle hDoc(&doc);
	TiXmlElement* dateElement=hDoc.FirstChild("CUGBLinker").FirstChild("Common").FirstChild("Date").ToElement();
	if (dateElement)
	{
		date=dateElement->Attribute("value");
	}
	return date;
}