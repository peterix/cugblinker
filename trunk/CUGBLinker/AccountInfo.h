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
	bool	m_savePwd;		//是否保存密码
	bool	m_autoCon;		//是否自动登录
	bool	m_autoStart;	//是否自动随系统启动
	long	m_curTraffic;	//当前流量
	long	m_maxTraffic;	//流量控制阈值
	bool	m_showTip;		//超流量时是否提示
	bool	m_autoDis;		//超流量时是否自动断网
};
