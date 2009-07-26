#pragma once

class CAccountInfo
{
public:
	CAccountInfo(void);
	~CAccountInfo(void);

public:
	CString	m_username;		//用户名
	CString m_password;		//密码
	int		m_range;		//默认访问范围
	BOOL	m_savePwd;		//是否保存密码
	BOOL	m_autoCon;		//是否自动连接
	//随系统启动项应归属于软件设置
	//bool	m_autoStart;	//是否自动随系统启动
	long	m_curTraffic;	//当前流量
	long	m_maxTraffic;	//流量控制阈值
	BOOL	m_showTip;		//超流量时是否提示
	BOOL	m_autoDis;		//超流量时是否自动断网
	CAccountInfo& operator=(const CAccountInfo& rhs);
};
