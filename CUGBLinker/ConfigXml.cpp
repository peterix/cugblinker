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
	TiXmlElement* accounts=hDoc.FirstChild("CUGBLinker").FirstChild("Accounts").ToElement();
	if (accounts)
	{
		//TiXmlElement* curAccount=accounts->FirstChild(CStringA("Account_").Append(accountInfo.m_username))->ToElement();
	}
}

void CConfigXml::GetAccount(CAccountInfo& accountInfo)
{
	
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
