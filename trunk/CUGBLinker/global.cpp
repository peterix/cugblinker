#include "stdafx.h"
#include "global.h"
#include "CUGBLinker.h"
#include "CUGBLinkerDlg.h"
#include "LinkerPage.h"
#include "TrafficPage.h"

BOOLEAN connecting=FALSE;
BOOLEAN disconnecting=FALSE;

double curSpeed=0.0;
double maxSpeed=0.0;
float* TrafficStats=NULL;
DWORD TrafficEntries;
pcap_t *fp=NULL;
bool tip_flag=true; //用于记录是否提示过的表示

UINT Connect(LPVOID pvParam)
{
	//if (theApp.curAccount.m_username=="" || theApp.curAccount.m_password=="")
	//	return 0;
	if (connecting)
		return 0;
	connecting=TRUE;
	CCUGBLinkerDlg* pMainWnd=(CCUGBLinkerDlg*)theApp.m_pMainWnd;
	CLinkerPage* pLinkerPage=(CLinkerPage*)&(pMainWnd->m_linkerPage);

	// 创建socket并连接目标地址
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
		AfxMessageBox(L"网关连接失败！");
		connecting=FALSE;
		return -1;
	}

	// 发送消息
	// range表示访问范围，1表示国外，2表示国内
	// timeout表示超时检查，0表示20分钟，1表示8小时
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
		AfxMessageBox(L"发送帐号信息失败！");
		connecting=FALSE;
		return -2;
	}

	// 接收消息

	CStringA recStr('\0',3000);
	int recLen;
	if((recLen=m_pSocket->Receive(recStr.GetBuffer(),3000)) == SOCKET_ERROR)
	{
		AfxMessageBox(L"接收网关反馈失败！");
		connecting=FALSE;
		return -3;
	}
	// 编码转换
	int wcsLen = ::MultiByteToWideChar(CP_UTF8, NULL, recStr.GetBuffer(), recStr.GetLength(), NULL, 0);
	CString wszStr('\0',wcsLen+1);
	::MultiByteToWideChar(CP_UTF8, NULL, recStr.GetBuffer(),recStr.GetLength(), wszStr.GetBuffer(), wcsLen);
	recStr.ReleaseBuffer();
	wszStr.ReleaseBuffer();

	//对返回信息处理

	CString ans1=L"<IMG SRC=\"/images/sign.gif\" hspace=\"6\" vspace=\"0\" align=\"middle\">";
	CString ans2=L"网络连接成功";

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
		wszStr=L"连接出错\r\n请登录IP网关连接";
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
	delete pvParam;
	//if (dis==1 && (theApp.curAccount.m_username=="" || theApp.curAccount.m_password==""))
	//	return 0;

	if (disconnecting)
		return 0;
	disconnecting=TRUE;
	CCUGBLinkerDlg* pMainWnd=(CCUGBLinkerDlg*)theApp.m_pMainWnd;
	CLinkerPage* pLinkerPage=(CLinkerPage*)&(pMainWnd->m_linkerPage);


	// 创建socket并连接目标地址
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
		AfxMessageBox(L"网关连接失败！");
		disconnecting=FALSE;
		return -1;
	}

	// 发送消息
	// range表示访问范围，1表示国外，2表示国内
	// timeout表示超时检查，0表示20分钟，1表示8小时
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
		AfxMessageBox(L"发送帐号信息失败！");
		disconnecting=FALSE;
		return -2;
	}

	// 接收消息

	CStringA recStr('\0',3000);
	int recLen;
	if((recLen=m_pSocket->Receive(recStr.GetBuffer(),3000)) == SOCKET_ERROR)
	{
		AfxMessageBox(L"接收网关反馈失败！");
		disconnecting=FALSE;
		return -3;
	}
	// 编码转换
	int wcsLen = ::MultiByteToWideChar(CP_UTF8, NULL, recStr.GetBuffer(), recStr.GetLength(), NULL, 0);
	CString wszStr('\0',wcsLen+1);
	::MultiByteToWideChar(CP_UTF8, NULL, recStr.GetBuffer(),recStr.GetLength(), wszStr.GetBuffer(), wcsLen);
	recStr.ReleaseBuffer();
	wszStr.ReleaseBuffer();


	// 对返回信息处理
	CString ans1=L"<IMG SRC=\"/images/sign.gif\" hspace=\"6\" vspace=\"0\" align=\"middle\">";
	CString ans2=L"网络断开成功";
	CString ans3=L"断开全部连接成功";

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
		wszStr=L"断开出错\r\n请请登录IP网关断开。";
	}

	// 像界面发送消息，更新显示
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
	str->Replace(L"<font id=flashing style=\"COLOR: #ffffff; FONT-FAMILY: 黑体; HEIGHT: 13px; WIDTH: 100px\">",L"");
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
		str->Format(L"Error in pcap_findalldevs: %S",errbuf);
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
	CCUGBLinkerDlg* pMainWnd=(CCUGBLinkerDlg*)theApp.m_pMainWnd;
	CTrafficPage* pTrafficPage=(CTrafficPage*)&(pMainWnd->m_trafficPage);

	struct timeval *old_ts = (struct timeval *)state;
	u_int delay;
	LARGE_INTEGER Bps,Pps;
#ifdef _DEBUG
	//AfxMessageBox(L"有速度！");
#endif

	/* Calculate the delay in microseconds from the last sample. */
	/* This value is obtained from the timestamp that the associated with the sample. */
	delay=(header->ts.tv_sec - old_ts->tv_sec) * 1000000 - old_ts->tv_usec + header->ts.tv_usec;
	/* Get the number of Bits per second */
	Bps.QuadPart=(((*(LONGLONG*)(pkt_data + 8)) * 1000000) / (delay));
	//                                               ^
	//												 |
	//												 |
	//			delay is expressed in microseconds --

	/* Get the number of Packets per second */
	Pps.QuadPart=(((*(LONGLONG*)(pkt_data)) * 1000000) / (delay));

	// 计算当前速度及当前流量
	theApp.curAccount.m_curTraffic+=Bps.QuadPart-Pps.QuadPart*68.43;
	if (tip_flag && (theApp.curAccount.m_curTraffic>theApp.curAccount.m_maxTraffic*1024.0*1024))
	{
		if (pTrafficPage->m_chkShowTip.GetCheck())
		{
			tip_flag=false;
			CString *infoStr=new CString();
			int* flag=new int;
			*infoStr=L"流量超标了！";
			*flag=BALLOON_WARNING;
			if (pTrafficPage->m_chkAutoDis.GetCheck())
			{
				int *dis=new int;
				*dis=0;
				AfxBeginThread(DisConnect, dis);
				*infoStr+=L"\n已自动断开！";
			}
			pMainWnd->PostMessage(WM_UPDATENOTIFY,(WPARAM)infoStr,(LPARAM)flag);
		}
	}
	curSpeed=Bps.QuadPart-Pps.QuadPart*68.43;
	maxSpeed=curSpeed>maxSpeed?curSpeed:maxSpeed;

	for(DWORD x=0; x<TrafficEntries; x++)
		TrafficStats[x]	= TrafficStats[x+1];
	TrafficStats[TrafficEntries]=curSpeed/1024.0;

	//store current timestamp
	old_ts->tv_sec=header->ts.tv_sec;
	old_ts->tv_usec=header->ts.tv_usec;
}

UINT statistic_traffic(LPVOID pvParam)
{
	CCUGBLinkerDlg* pMainWnd=(CCUGBLinkerDlg*)theApp.m_pMainWnd;
	CTrafficPage* pTrafficPage=(CTrafficPage*)&(pMainWnd->m_trafficPage);

	CString* errorInfo=new CString();
	int* flag=new int;

	char errbuf[PCAP_ERRBUF_SIZE];
	struct timeval st_ts;
	u_int netmask;
	struct bpf_program fcode;

	while(1) // 切换统计网卡后，对新网卡继续统计流量 
	{
		CStringA filter="";// 过滤器
		/* Open the output adapter */
		CStringA temp=CStringA(pTrafficPage->m_curNIC);
		if ( (fp= pcap_open(temp.GetBuffer(), 100, PCAP_OPENFLAG_NOCAPTURE_LOCAL, 1000, NULL, errbuf) ) == NULL)
		{
			errorInfo->Format(L"网卡打开失败,请检查是否已选择网卡. \n%S\n%S",temp.GetBuffer(), errbuf);
			*flag=BALLOON_ERROR;
			pMainWnd->PostMessage(WM_UPDATENOTIFY,(WPARAM)errorInfo,(LPARAM)flag);
			temp.ReleaseBuffer();
			return 1;
		}
		temp.ReleaseBuffer();

		/* Don't care about netmask, it won't be used for this filter */
		netmask=0xffffff; 

		// 配置过滤器，需读取本机网关，并获得网关mac地址
		char ipAddr[16]={0};
		char gatewayIP[16]={0};
		char gatewayMAC[18]={0};
		HKEY hKey;
		LONG lRet;
		DWORD BufferSize = 40;
		UCHAR* IPPerfData = new UCHAR[BufferSize];
		UCHAR* PerfData = new UCHAR[BufferSize];
		lRet = RegOpenKeyEx( HKEY_LOCAL_MACHINE,
			CString("SYSTEM\\CurrentControlSet\\Services\\Tcpip\\Parameters\\Interfaces\\")
			+pTrafficPage->m_curNIC.Mid(12), 0, KEY_QUERY_VALUE, &hKey );

		if( lRet == ERROR_SUCCESS )
		{
			lRet=RegQueryValueEx( hKey,
				TEXT("EnableDHCP"),
				NULL,
				NULL,
				PerfData,
				&BufferSize );
			if( lRet == ERROR_SUCCESS )
			{
				BufferSize=40;
				if (PerfData[0]==1)
				{
					lRet=RegQueryValueEx( hKey,
						TEXT("DhcpIPAddress"),
						NULL,
						NULL,
						IPPerfData,
						&BufferSize );
					lRet=RegQueryValueEx( hKey,
						TEXT("DhcpDefaultGateway"),
						NULL,
						NULL,
						PerfData,
						&BufferSize );
				}
				else
				{
					lRet=RegQueryValueEx( hKey,
						TEXT("IPAddress"),
						NULL,
						NULL,
						IPPerfData,
						&BufferSize );
					lRet=RegQueryValueEx( hKey,
						TEXT("DefaultGateway"),
						NULL,
						NULL,
						PerfData,
						&BufferSize );
				}
			}
		}
		RegCloseKey( hKey );

		for (int i=0,j=0,k=0; i<15; i++,j++,k++)
		{
			if (PerfData[j]=='\0')
			{
				j++;
			}
			gatewayIP[i]=PerfData[j];
			if (IPPerfData[k]=='\0')
			{
				k++;
			}
			ipAddr[i]=IPPerfData[k];
		}
		CString IP(ipAddr);
		IP=IP.Trim();
		if (IP.Find(L"10.")==0 || IP.Find(L"172.")==0 || IP.Find(L"192.168.")==0)
		{
			if (CStringA(gatewayIP).Trim()!="")
			{
				// 获取网关mac地址
				ULONG MacAddr[2];       /* for 6-byte hardware addresses */
				ULONG PhysAddrLen = 6;  /* default to length of six bytes */
				memset(&MacAddr, 0xff, sizeof (MacAddr));
				SendARP(inet_addr(gatewayIP), 0, &MacAddr, &PhysAddrLen);

				BYTE *bPhysAddr = (BYTE *) & MacAddr;
				for (int i = 0; i < (int)PhysAddrLen; i++) 
				{
					if (i<(int)PhysAddrLen-1)
					{
						sprintf(gatewayMAC+i*3,"%.2X:",(int)bPhysAddr[i]);
					}
					else
					{
						sprintf(gatewayMAC+i*3,"%.2X",(int)bPhysAddr[i]);
					}
				}
				if (CStringA(gatewayMAC).Trim()!="")
				{
					filter+=CStringA("ether host ")+CStringA(gatewayMAC)+CStringA(" and not host ")+CStringA(gatewayIP)+CStringA(" and ");
				}
			}
		}

		filter+=CStringA(FILTER);
#ifdef _DEBUG
		AfxMessageBox(CString(filter));
#endif
		//compile the filter
		if (pcap_compile(fp, &fcode, filter, 1, netmask) <0 )
		{
			errorInfo->Format(L"Unable to compile the packet filter. Check the syntax.");
			*flag=BALLOON_ERROR;
			pMainWnd->PostMessage(WM_UPDATENOTIFY,(WPARAM)errorInfo,(LPARAM)flag);
			/* Free the device list */
			pcap_close(fp);
			return 1;
		}

		//set the filter
		if (pcap_setfilter(fp, &fcode)<0)
		{
			errorInfo->Format(L"Error setting the filter.");
			*flag=BALLOON_ERROR;
			pMainWnd->PostMessage(WM_UPDATENOTIFY,(WPARAM)errorInfo,(LPARAM)flag);
			/* Free the device list */
			pcap_close(fp);
			return 1;
		}

		/* Put the interface in statstics mode */
		if (pcap_setmode(fp, MODE_STAT)<0)
		{
			errorInfo->Format(L"Error setting the mode.");
			*flag=BALLOON_ERROR;
			pMainWnd->PostMessage(WM_UPDATENOTIFY,(WPARAM)errorInfo,(LPARAM)flag);
			/* Free the device list */
			pcap_close(fp);
			return 1;
		}

		/* Start the main loop */
		pcap_loop(fp, 0, dispatcher_handler, (PUCHAR)&st_ts);

		pcap_close(fp);
		fp=NULL;
	}
	return 0;
}