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
	BOOL	m_savePwd;		//�Ƿ񱣴�����
	long	m_curTraffic;	//��ǰ����
	long	m_maxTraffic;	//����������ֵ
	BOOL	m_showTip;		//������ʱ�Ƿ���ʾ
	BOOL	m_autoDis;		//������ʱ�Ƿ��Զ�����

	//��ϵͳ��������Զ�����Ӧ�������������
	//BOOL	m_autoCon;		//�Ƿ��Զ�����
	//bool	m_autoStart;	//�Ƿ��Զ���ϵͳ����

public:
	CAccountInfo& operator=(const CAccountInfo& rhs);
};
