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
	if(!doc.LoadFile("CUGBLinker.xml"))
	{
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
		TiXmlElement* accounts = new TiXmlElement("Accounts");
		root->LinkEndChild(accounts);
		doc.SaveFile();
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
	activeAccount->SetAttribute("value",val);
}

int CConfigXml::GetActiveAccount(void)
{
	int ret=0;
	TiXmlHandle hDoc(&doc);
	TiXmlElement* activeAccount=hDoc.FirstChild("CUGBLinker").FirstChild("Common").FirstChild("ActiveAccount").ToElement();
	activeAccount->Attribute("value",&ret);
	return ret;
}

void CConfigXml::SetAutoConnect(int val)
{
	TiXmlHandle hDoc(&doc);
	TiXmlElement* autoConnect=hDoc.FirstChild("CUGBLinker").FirstChild("Common").FirstChild("AutoConnect").ToElement();
	autoConnect->SetAttribute("value",val);
}

int CConfigXml::GetAutoConnect(void)
{
	int ret=0;
	TiXmlHandle hDoc(&doc);
	TiXmlElement* autoConnect=hDoc.FirstChild("CUGBLinker").FirstChild("Common").FirstChild("AutoConnect").ToElement();
	autoConnect->Attribute("value",&ret);
	return ret;
}

void CConfigXml::SetDisBtnStatus(int val)
{
	TiXmlHandle hDoc(&doc);
	TiXmlElement* disBtnStatus=hDoc.FirstChild("CUGBLinker").FirstChild("Common").FirstChild("DisBtnStatus").ToElement();
	disBtnStatus->SetAttribute("value",val);
}

int CConfigXml::GetDisBtnStatus(void)
{
	int ret=0;
	TiXmlHandle hDoc(&doc);
	TiXmlElement* disBtnStatus=hDoc.FirstChild("CUGBLinker").FirstChild("Common").FirstChild("DisBtnStatus").ToElement();
	disBtnStatus->Attribute("value",&ret);
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
