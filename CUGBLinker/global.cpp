#include "stdafx.h"
#include "global.h"
#include "CUGBLinker.h"
#include "CUGBLinkerDlg.h"
#include "LinkerPage.h"

UINT Connect(LPVOID pvParam)
{

	CCUGBLinkerDlg* pMainWnd=(CCUGBLinkerDlg*)theApp.m_pMainWnd;
	CLinkerPage* pLinkerPage=(CLinkerPage*)&(pMainWnd->m_linkerPage);

	// ����socket������Ŀ���ַ
	CSocket* m_pSocket=new CSocket();
	m_pSocket->Create();
	if(0 == m_pSocket->Connect(L"202.204.105.27",80))
	{
		AfxMessageBox(L"��������ʧ�ܣ�");
		return -1;
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
					"Host: 202.204.105.27\r\n"
					"Content-Length: %d\r\n"
					"Content-Type: application/x-www-form-urlencoded\r\n\r\n",
					userStr.GetLength());
	sendStr+=userStr;

	if (m_pSocket->Send(sendStr,sendStr.GetLength(),0) == SOCKET_ERROR) 
	{
		AfxMessageBox(L"�����ʺ���Ϣʧ�ܣ�");
		return -2;
	}

	// ������Ϣ

	CStringA recStr('\0',3000);
	int recLen;
	if((recLen=m_pSocket->Receive(recStr.GetBuffer(),3000)) == SOCKET_ERROR)
	{
		AfxMessageBox(L"�������ط���ʧ�ܣ�");
		return -3;
	}
	// ����ת��
	int wcsLen = ::MultiByteToWideChar(CP_UTF8, NULL, recStr.GetBuffer(), recStr.GetLength(), NULL, 0);
	CString wszStr('\0',wcsLen+1);
	::MultiByteToWideChar(CP_UTF8, NULL, recStr.GetBuffer(),recStr.GetLength(), wszStr.GetBuffer(), wcsLen);
	recStr.ReleaseBuffer();
	wszStr.ReleaseBuffer();

	//�Է�����Ϣ����
	
	CString ans1=L"<IMG SRC=\"/images/sign.gif\" hspace=\"6\" vspace=\"0\" align=\"middle\">";
	CString ans2=L"�������ӳɹ�";

	int* conSuccess=new int(-1);
	wszStr=wszStr.Mid(wszStr.Find(L"<table"));
	Change(&wszStr);

	int pos=0;
	if((pos=wszStr.Find(ans1)) != -1)
	{
		wszStr=wszStr.Mid(pos+66);
		wszStr=wszStr.Left(wszStr.Find(L"</table>"));
	}
	else if((pos=wszStr.Find(ans2)) != -1)
	{
		wszStr=wszStr.Mid(pos);
		wszStr=wszStr.Left(wszStr.Find(L"</font>"));
		*conSuccess=1;
	}
	else
	{
		wszStr=L"���ӳ���\r\n���¼IP��������";
	}
	
	CString* str=new CString(wszStr);
	pLinkerPage->PostMessage(WM_UPDATEINFO,(WPARAM)str,(LPARAM)conSuccess);

	delete m_pSocket;
	return 0;
}

UINT DisConnect(LPVOID pvParam)
{
	CCUGBLinkerDlg* pMainWnd=(CCUGBLinkerDlg*)theApp.m_pMainWnd;
	CLinkerPage* pLinkerPage=(CLinkerPage*)&(pMainWnd->m_linkerPage);

	int dis=*(int*)pvParam;

	// ����socket������Ŀ���ַ
	CSocket* m_pSocket=new CSocket();
	m_pSocket->Create();
	if(0 == m_pSocket->Connect(L"202.204.105.27",80))
	{
		AfxMessageBox(L"��������ʧ�ܣ�");
		return -1;
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
					"Host: 202.204.105.27\r\n"
					"Content-Length: %d\r\n"
					"Content-Type: application/x-www-form-urlencoded\r\n\r\n",
					userStr.GetLength());
	sendStr+=userStr;

	if (m_pSocket->Send(sendStr,sendStr.GetLength(),0) == SOCKET_ERROR) 
	{
		AfxMessageBox(L"�����ʺ���Ϣʧ�ܣ�");
		return -2;
	}

	// ������Ϣ

	CStringA recStr('\0',3000);
	int recLen;
	if((recLen=m_pSocket->Receive(recStr.GetBuffer(),3000)) == SOCKET_ERROR)
	{
		AfxMessageBox(L"�������ط���ʧ�ܣ�");
		return -3;
	}
	// ����ת��
	int wcsLen = ::MultiByteToWideChar(CP_UTF8, NULL, recStr.GetBuffer(), recStr.GetLength(), NULL, 0);
	CString wszStr('\0',wcsLen+1);
	::MultiByteToWideChar(CP_UTF8, NULL, recStr.GetBuffer(),recStr.GetLength(), wszStr.GetBuffer(), wcsLen);
	recStr.ReleaseBuffer();
	wszStr.ReleaseBuffer();


	// �Է�����Ϣ����
	CString ans1=L"<IMG SRC=\"/images/sign.gif\" hspace=\"6\" vspace=\"0\" align=\"middle\">";
	CString ans2=L"����Ͽ��ɹ�";
	CString ans3=L"�Ͽ�ȫ�����ӳɹ�";

	wszStr=wszStr.Mid(wszStr.Find(L"<table"));
	Change(&wszStr);

	int* disSuccess=new int(-2);
	int pos=0;
	if((pos=wszStr.Find(ans1)) != -1)
	{
		wszStr=wszStr.Mid(pos+66);
		wszStr=wszStr.Left(wszStr.Find(L"</table>"));
	}
	else if((pos=wszStr.Find(ans2)) != -1)
	{
		wszStr=wszStr.Mid(pos);
		wszStr=wszStr.Left(wszStr.Find(L"</table>"));
		*disSuccess=2;
	}
	else if ((pos=wszStr.Find(ans3)) != -1)
	{
		wszStr=wszStr.Mid(pos);
		wszStr=wszStr.Left(wszStr.Find(L"</table>"));
		*disSuccess=2;
	}
	else
	{
		wszStr=L"�Ͽ�����\r\n�����¼IP���ضϿ���";
	}

	// ����淢����Ϣ��������ʾ
	CString* str=new CString(wszStr);
	pLinkerPage->PostMessage(WM_UPDATEINFO,(WPARAM)str,(LPARAM)disSuccess);

	delete m_pSocket;
	return 0;
}

void Change(CString *str)
{
	str->Replace(L"</td>",L" ");
	str->Replace(L"<td>",L"");
	str->Replace(L"</tr>",L"\r\n");
	str->Replace(L"<tr>",L"");
	str->Replace(L"<table noborder>",L"");
	str->Replace(L"&nbsp;",L" ");
	str->Replace(L"<br>",L"\r\n");
	str->Replace(L"<p>",L"\r\n");
	str->Replace(L"<td  colspan=2><font color=\"#cc0000\">",L"");
}