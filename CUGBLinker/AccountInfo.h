#pragma once

class CAccountInfo
{
public:
	CAccountInfo(void);
	~CAccountInfo(void);

public:
	CString	m_username;		//�û���
	CString m_password;		//����
	int		m_range;		//Ĭ�Ϸ��ʷ�Χ
	bool	m_savePwd;		//�Ƿ񱣴�����
	bool	m_autoCon;		//�Ƿ��Զ���¼
	bool	m_autoStart;	//�Ƿ��Զ���ϵͳ����
	long	m_curTraffic;	//��ǰ����
	long	m_maxTraffic;	//����������ֵ
	bool	m_showTip;		//������ʱ�Ƿ���ʾ
	bool	m_autoDis;		//������ʱ�Ƿ��Զ�����
};
