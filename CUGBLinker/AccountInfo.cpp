#include "StdAfx.h"
#include "AccountInfo.h"

CAccountInfo::CAccountInfo(void)
	: m_username(L"")
	, m_password(L"")
	, m_range(0)
	, m_savePwd(FALSE)
	, m_curTraffic(0)
	, m_maxTraffic(2000)
	, m_showTip(FALSE)
	, m_autoDis(FALSE)
{
}

CAccountInfo::~CAccountInfo(void)
{
}

CAccountInfo& CAccountInfo::operator=(const CAccountInfo& rhs)
{
	if (this == &rhs) 
		return *this;

	this->m_username=rhs.m_username;
	this->m_password=rhs.m_password;
	this->m_range=rhs.m_range;
	this->m_savePwd=rhs.m_savePwd;
	this->m_curTraffic=rhs.m_curTraffic;
	this->m_maxTraffic=rhs.m_maxTraffic;
	this->m_showTip=rhs.m_showTip;
	this->m_autoDis=rhs.m_autoDis;

	return *this;
}
