#pragma once

class CAccountInfo
{
public:
	CAccountInfo(void);
	~CAccountInfo(void);

public:
	CString	m_username;		//�û���
	CString m_password;		//����
	INT		m_range;		//Ĭ�Ϸ��ʷ�Χ
	BOOL	m_savePwd;		//�Ƿ񱣴�����
	INT		m_curTraffic;	//��ǰ����
	INT		m_maxTraffic;	//����������ֵ
	BOOL	m_showTip;		//������ʱ�Ƿ���ʾ
	BOOL	m_autoDis;		//������ʱ�Ƿ��Զ�����
	CString m_curNIC;		//��ǰͳ������������

	//��ϵͳ��������Զ�����Ӧ�������������
	//BOOL	m_autoCon;		//�Ƿ��Զ�����
	//BOOL	m_autoStart;	//�Ƿ��Զ���ϵͳ����

public:
	CAccountInfo& operator=(const CAccountInfo& rhs);
};
