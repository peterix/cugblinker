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
	if(0 == m_pSocket->Connect(L"202.204.105.7",80))
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
					"Host: 202.204.105.7\r\n"
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

	CStringA recStr('\0',2000);
	int recLen;
	if((recLen=m_pSocket->Receive(recStr.GetBuffer(),2000)) == SOCKET_ERROR)
	{
		AfxMessageBox(L"�������ط���ʧ�ܣ�");
		return -3;
	}
	recStr.ReleaseBuffer();

	//�Է�����Ϣ����
	
	CStringA ans1="<IMG SRC=\"/images/sign.gif\" hspace=\"6\" vspace=\"0\" align=\"middle\">";
	CStringA ans2="�������ӳɹ�";

	int* conSuccess=new int(-1);
	recStr=recStr.Mid(recStr.Find("<table"));
	Change(&recStr);

	int pos=0;
	if((pos=recStr.Find(ans1)) != -1)
	{
		recStr=recStr.Mid(pos+66);
		recStr=recStr.Left(recStr.Find("</table>"));
	}
	else if((pos=recStr.Find(ans2)) != -1)
	{
		recStr=recStr.Mid(pos);
		recStr=recStr.Left(recStr.Find("</font>"));
		*conSuccess=1;
	}
	else
	{
		recStr="���ӳ���\r\n���¼IP��������";
	}

	CString* str=new CString('\0',recStr.GetLength());
	MultiByteToWideChar( CP_ACP, 0, recStr, recStr.GetLength(), str->GetBuffer(), str->GetLength() );
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
	if(0 == m_pSocket->Connect(L"202.204.105.7",80))
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
					"Host: 202.204.105.7\r\n"
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

	CStringA recStr('\0',2000);
	int recLen;
	if((recLen=m_pSocket->Receive(recStr.GetBuffer(),2000)) == SOCKET_ERROR)
	{
		AfxMessageBox(L"�������ط���ʧ�ܣ�");
		return -3;
	}
	recStr.ReleaseBuffer();


	// �Է�����Ϣ����
	CStringA ans1="<IMG SRC=\"/images/sign.gif\" hspace=\"6\" vspace=\"0\" align=\"middle\">";
	CStringA ans2="����Ͽ��ɹ�";
	CStringA ans3="�Ͽ�ȫ�����ӳɹ�";

	recStr=recStr.Mid(recStr.Find("<table"));
	Change(&recStr);

	int* disSuccess=new int(-2);
	int pos=0;
	if((pos=recStr.Find(ans1)) != -1)
	{
		recStr=recStr.Mid(pos+66);
		recStr=recStr.Left(recStr.Find("</table>"));
	}
	else if((pos=recStr.Find(ans2)) != -1)
	{
		recStr=recStr.Mid(pos);
		recStr=recStr.Left(recStr.Find("</table>"));
		*disSuccess=2;
	}
	else if ((pos=recStr.Find(ans3)) != -1)
	{
		recStr=recStr.Mid(pos);
		recStr=recStr.Left(recStr.Find("</table>"));
		*disSuccess=2;
	}
	else
	{
		recStr="�Ͽ�����\r\n�����¼IP���ضϿ���";
	}

	// ����淢����Ϣ��������ʾ
	CString* str=new CString('\0',recStr.GetLength());
	MultiByteToWideChar( CP_ACP, 0, recStr, recStr.GetLength(), str->GetBuffer(), str->GetLength() );
	pLinkerPage->PostMessage(WM_UPDATEINFO,(WPARAM)str,(LPARAM)disSuccess);


	delete m_pSocket;
	return 0;
}

void Change(CStringA *str)
{
	str->Replace("</td>"," ");
	str->Replace("<td>","");
	str->Replace("</tr>","\r\n");
	str->Replace("<tr>","");
	str->Replace("<table noborder>","");
	str->Replace("&nbsp;"," ");
	str->Replace("<br>","\r\n");
	str->Replace("<p>","\r\n");
	str->Replace("<td  colspan=2><font color=\"#cc0000\">","");
}