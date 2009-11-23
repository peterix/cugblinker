#pragma once

class CAccountInfo
{
public:
	CAccountInfo(void);
	~CAccountInfo(void);

public:
	CString	m_username;		//用户名
	CString m_password;		//密码
	INT		m_range;		//默认访问范围
	BOOL	m_savePwd;		//是否保存密码
	INT		m_curTraffic;	//当前流量
	INT		m_maxTraffic;	//流量控制阈值
	BOOL	m_showTip;		//超流量时是否提示
	BOOL	m_autoDis;		//超流量时是否自动断网
	CString m_curNIC;		//当前统计流量的网卡

	//随系统启动项和自动连接应归属于软件设置
	//BOOL	m_autoCon;		//是否自动连接
	//BOOL	m_autoStart;	//是否自动随系统启动

public:
	CAccountInfo& operator=(const CAccountInfo& rhs);
};
