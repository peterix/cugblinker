#include "stdafx.h"
#include "global.h"
#include "CUGBLinker.h"
#include "CUGBLinkerDlg.h"
#include "LinkerPage.h"

BOOLEAN connecting=FALSE;
BOOLEAN disconnecting=FALSE;

UINT Connect(LPVOID pvParam)
{
	//if (theApp.curAccount.m_username=="" || theApp.curAccount.m_password=="")
	//	return 0;
	if (connecting)
		return 0;
	connecting=TRUE;
	CCUGBLinkerDlg* pMainWnd=(CCUGBLinkerDlg*)theApp.m_pMainWnd;
	CLinkerPage* pLinkerPage=(CLinkerPage*)&(pMainWnd->m_linkerPage);

	// ����socket������Ŀ���ַ
	if (!AfxSocketInit())
	{
		AfxMessageBox(IDP_SOCKETS_INIT_FAILED);
		connecting=FALSE;
		return FALSE;
	}

	CSocket* m_pSocket=new CSocket();
	m_pSocket->Create();
	if(0 == m_pSocket->Connect(L"202.204.105.27",80))
	{
		AfxMessageBox(L"��������ʧ�ܣ�");
		connecting=FALSE;
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
		connecting=FALSE;
		return -2;
	}

	// ������Ϣ

	CStringA recStr('\0',3000);
	int recLen;
	if((recLen=m_pSocket->Receive(recStr.GetBuffer(),3000)) == SOCKET_ERROR)
	{
		AfxMessageBox(L"�������ط���ʧ�ܣ�");
		connecting=FALSE;
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
		wszStr=wszStr.Mid(pos+65);
		wszStr=wszStr.Left(wszStr.Find(L"</table>"));
	}
	else if((pos=wszStr.Find(ans2)) != -1)
	{
		wszStr=wszStr.Mid(pos);
		wszStr=wszStr.Left(wszStr.Find(L"</table>"));
		*conSuccess=1;
	}
	else
	{
		wszStr=L"���ӳ���\r\n���¼IP��������";
	}
	
	CString* str=new CString(wszStr);
	pLinkerPage->PostMessage(WM_UPDATEINFO,(WPARAM)str,(LPARAM)conSuccess);

	delete m_pSocket;
	connecting=FALSE;
	return 0;
}

UINT DisConnect(LPVOID pvParam)
{
	int dis=*(int*)pvParam;
	//if (dis==1 && (theApp.curAccount.m_username=="" || theApp.curAccount.m_password==""))
	//	return 0;

	if (disconnecting)
		return 0;
	disconnecting=TRUE;
	CCUGBLinkerDlg* pMainWnd=(CCUGBLinkerDlg*)theApp.m_pMainWnd;
	CLinkerPage* pLinkerPage=(CLinkerPage*)&(pMainWnd->m_linkerPage);


	// ����socket������Ŀ���ַ
	if (!AfxSocketInit())
	{
		AfxMessageBox(IDP_SOCKETS_INIT_FAILED);
		disconnecting=FALSE;
		return FALSE;
	}
	CSocket* m_pSocket=new CSocket();
	m_pSocket->Create();
	if(0 == m_pSocket->Connect(L"202.204.105.27",80))
	{
		AfxMessageBox(L"��������ʧ�ܣ�");
		disconnecting=FALSE;
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
		disconnecting=FALSE;
		return -2;
	}

	// ������Ϣ

	CStringA recStr('\0',3000);
	int recLen;
	if((recLen=m_pSocket->Receive(recStr.GetBuffer(),3000)) == SOCKET_ERROR)
	{
		AfxMessageBox(L"�������ط���ʧ�ܣ�");
		disconnecting=FALSE;
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
		wszStr=wszStr.Mid(pos+65);
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
	disconnecting=FALSE;
	return 0;
}

void Change(CString *str)
{
	str->Replace(L"\r\n",L"");
	str->Replace(L"<tr><td>",L"");
	str->Replace(L"</td><td>",L" ");
	str->Replace(L"</td></tr>",L"\r\n");
	str->Replace(L"</td>",L" ");
	str->Replace(L"<td>",L"");
	str->Replace(L"</tr>",L"\r\n");
	str->Replace(L"<tr>",L"");
	str->Replace(L"<b>",L"");
	str->Replace(L"</b>",L"");
	str->Replace(L"<table noborder>",L"");
	str->Replace(L"&nbsp;",L" ");
	str->Replace(L"<br>",L"\r\n");
	str->Replace(L"<BR>",L"");
	str->Replace(L"<p>",L"\r\n");
	str->Replace(L"<td  colspan=2>",L"");
	str->Replace(L"<font id=flashing style=\"COLOR: #ffffff; FONT-FAMILY: ����; HEIGHT: 13px; WIDTH: 100px\">",L"");
	str->Replace(L"</font>",L"");
	str->Replace(L"<font color=\"#cc0000\">",L"");	
}

pcap_if_t* finddevs()
{
	CCUGBLinkerDlg* pMainWnd=(CCUGBLinkerDlg*)theApp.m_pMainWnd;

	char errbuf[PCAP_ERRBUF_SIZE];

	pcap_if_t *alldevs;

	/* Retrieve the device list */
	if(pcap_findalldevs(&alldevs, errbuf) == -1)
	{
		CString* str=new CString();
		str->Format(L"Error in pcap_findalldevs: %s",errbuf);
		int* flag=new int(BALLOON_ERROR);
		pMainWnd->PostMessage(WM_UPDATENOTIFY,(WPARAM)str,(LPARAM)flag);
	}
	return alldevs;
}

#define IPTOSBUFFERS    12
char* iptos(u_long in)	// From tcptraceroute, convert a numeric IP address to a string
{
	static char output[IPTOSBUFFERS][3*4+3+1];
	static short which;
	u_char *p;

	p = (u_char *)&in;
	which = (which + 1 == IPTOSBUFFERS ? 0 : which + 1);
	_snprintf_s(output[which], sizeof(output[which]), sizeof(output[which]),"%d.%d.%d.%d", p[0], p[1], p[2], p[3]);
	return output[which];
}

char* ip6tos(struct sockaddr *sockaddr, char *address, int addrlen)
{
	socklen_t sockaddrlen;
	sockaddrlen = sizeof(struct sockaddr_in6);

	if(getnameinfo(sockaddr, 
		sockaddrlen, 
		address, 
		addrlen, 
		NULL, 
		0, 
		NI_NUMERICHOST) != 0) address = NULL;

	return address;
}

void dispatcher_handler(u_char *state, const struct pcap_pkthdr *header, const u_char *pkt_data)
{
	struct timeval *old_ts = (struct timeval *)state;
	u_int delay;
	LARGE_INTEGER Bps,Pps;
	struct tm ltime;
	char timestr[16];
	time_t local_tv_sec;

	/* Calculate the delay in microseconds from the last sample. */
	/* This value is obtained from the timestamp that the associated with the sample. */
	delay=(header->ts.tv_sec - old_ts->tv_sec) * 1000000 - old_ts->tv_usec + header->ts.tv_usec;
	/* Get the number of Bits per second */
	Bps.QuadPart=(((*(LONGLONG*)(pkt_data + 8)) * 1000000) / (delay));
	/*                                                   ^
														 |
														 |
					delay is expressed in microseconds --
	*/

	/* Get the number of Packets per second */
	Pps.QuadPart=(((*(LONGLONG*)(pkt_data)) * 1000000) / (delay));

	/* Convert the timestamp to readable format */
	local_tv_sec = header->ts.tv_sec;
	localtime_s(&ltime, &local_tv_sec);
	strftime( timestr, sizeof timestr, "%H:%M:%S", &ltime);

	/* Print timestamp*/
	printf("%s ", timestr);

	/* Print the samples */
	printf("BPS=%I64u ", Bps.QuadPart);
	printf("PPS=%I64u\n", Pps.QuadPart);

	//store current timestamp
	old_ts->tv_sec=header->ts.tv_sec;
	old_ts->tv_usec=header->ts.tv_usec;
}