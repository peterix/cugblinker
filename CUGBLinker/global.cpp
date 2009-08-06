#include "stdafx.h"
#include "global.h"
#include "CUGBLinker.h"
#include "CUGBLinkerDlg.h"
#include "LinkerPage.h"


UINT Connect(LPVOID pvParam)
{

	CCUGBLinkerDlg* pMainWnd=(CCUGBLinkerDlg*)theApp.m_pMainWnd;
	CLinkerPage* pLinkerPage=(CLinkerPage*&)pMainWnd->m_linkerPage;

	// ����socket������Ŀ���ַ
	CSocket* m_pSocket=new CSocket();
	m_pSocket->Create();
	if(0 == m_pSocket->Connect(L"202.204.105.7",80))
	{
		AfxMessageBox(L"Connect Error!");
	}

	// ������Ϣ
	// range��ʾ���ʷ�Χ��1��ʾ���⣬2��ʾ����
	// timeout��ʾ��ʱ��飬0��ʾ20���ӣ�1��ʾ8Сʱ
	int range=theApp.curAccount.m_range==0?2:1;
	CStringA userStr;
	userStr.Format("uid=%S&password=%S&range=%d&timeout=1&operation=connect",
		theApp.curAccount.m_username,theApp.curAccount.m_password,range);
	CStringA sendStr;
	sendStr.Format( "POST /ipgw/ipgw.ipgw HTTP/1.1\r\n"
					"Host: 202.204.105.7\r\nContent-Length: %d\r\n"
					"Content-Type: application/x-www-form-urlencoded\r\n\r\n",
					userStr.GetLength());
	sendStr+=userStr;

	if (m_pSocket->Send(sendStr,sendStr.GetLength(),0) == SOCKET_ERROR) 
	{
		AfxMessageBox(L"����ʧ�ܣ�Connect��!");
	}

	// ������Ϣ

	CStringA recStr('\0',2000);
	int recLen;
	if((recLen=m_pSocket->Receive(recStr.GetBuffer(),2000)) == SOCKET_ERROR)
	{
		AfxMessageBox(L"Receive Error!");
	}

	recStr.ReleaseBuffer();
	delete m_pSocket;
	
	return 0;
}

UINT DisConnect(LPVOID pvParam)
{
	CCUGBLinkerDlg* pMainWnd=(CCUGBLinkerDlg*)theApp.m_pMainWnd;
	CLinkerPage* pLinkerPage=(CLinkerPage*&)pMainWnd->m_linkerPage;

	int dis=*(int*)pvParam;

	// ����socket������Ŀ���ַ
	CSocket* m_pSocket=new CSocket();
	m_pSocket->Create();
	if(0 == m_pSocket->Connect(L"202.204.105.7",80))
	{
		AfxMessageBox(L"Connect Error!");
	}

	// ������Ϣ
	// range��ʾ���ʷ�Χ��1��ʾ���⣬2��ʾ����
	// timeout��ʾ��ʱ��飬0��ʾ20���ӣ�1��ʾ8Сʱ
	int range=theApp.curAccount.m_range==0?2:1;
	CStringA disStr=dis==0?"disconnect":"disconnectall";
	CStringA userStr;
	userStr.Format("uid=%S&password=%S&range=%d&timeout=1&operation=",
		theApp.curAccount.m_username,theApp.curAccount.m_password,range);
	userStr+=disStr;
	CStringA sendStr;
	sendStr.Format( "POST /ipgw/ipgw.ipgw HTTP/1.1\r\n"
		"Host: 202.204.105.7\r\nContent-Length: %d\r\n"
		"Content-Type: application/x-www-form-urlencoded\r\n\r\n",
		userStr.GetLength());
	sendStr+=userStr;

	if (m_pSocket->Send(sendStr,sendStr.GetLength(),0) == SOCKET_ERROR) 
	{
		AfxMessageBox(L"����ʧ�ܣ�Connect��!");
	}

	// ������Ϣ

	CStringA recStr('\0',2000);
	int recLen;
	if((recLen=m_pSocket->Receive(recStr.GetBuffer(),2000)) == SOCKET_ERROR)
	{
		AfxMessageBox(L"Receive Error!");
	}

	recStr.ReleaseBuffer();
	delete m_pSocket;

	return 0;
}