#include "stdafx.h"
#include "global.h"
#include "CUGBLinker.h"
#include "CUGBLinkerDlg.h"
#include "LinkerPage.h"


UINT Connect(LPVOID pvParam)
{

	CCUGBLinkerDlg* pMainWnd=(CCUGBLinkerDlg*)theApp.m_pMainWnd;
	CLinkerPage* pLinkerPage=(CLinkerPage*)&(pMainWnd->m_linkerPage);

	// 创建socket并连接目标地址
	CSocket* m_pSocket=new CSocket();
	m_pSocket->Create();
	if(0 == m_pSocket->Connect(L"202.204.105.7",80))
	{
		AfxMessageBox(L"网关连接失败！");
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
					"Host: 202.204.105.7\r\n"
					"Content-Length: %d\r\n"
					"Content-Type: application/x-www-form-urlencoded\r\n\r\n",
					userStr.GetLength());
	sendStr+=userStr;

	if (m_pSocket->Send(sendStr,sendStr.GetLength(),0) == SOCKET_ERROR) 
	{
		AfxMessageBox(L"发送帐号信息失败！");
		return -2;
	}

	// 接收消息

	CStringA recStr('\0',2000);
	int recLen;
	if((recLen=m_pSocket->Receive(recStr.GetBuffer(),2000)) == SOCKET_ERROR)
	{
		AfxMessageBox(L"接收网关反馈失败！");
		return -3;
	}
	recStr.ReleaseBuffer();

	//对返回信息处理
	
	CStringA ans1="<IMG SRC=\"/images/sign.gif\" hspace=\"6\" vspace=\"0\" align=\"middle\">";
	CStringA ans2="网络连接成功";

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
		recStr="连接出错\r\n请登录IP网关连接";
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

	// 创建socket并连接目标地址
	CSocket* m_pSocket=new CSocket();
	m_pSocket->Create();
	if(0 == m_pSocket->Connect(L"202.204.105.7",80))
	{
		AfxMessageBox(L"网关连接失败！");
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
					"Host: 202.204.105.7\r\n"
					"Content-Length: %d\r\n"
					"Content-Type: application/x-www-form-urlencoded\r\n\r\n",
					userStr.GetLength());
	sendStr+=userStr;

	if (m_pSocket->Send(sendStr,sendStr.GetLength(),0) == SOCKET_ERROR) 
	{
		AfxMessageBox(L"发送帐号信息失败！");
		return -2;
	}

	// 接收消息

	CStringA recStr('\0',2000);
	int recLen;
	if((recLen=m_pSocket->Receive(recStr.GetBuffer(),2000)) == SOCKET_ERROR)
	{
		AfxMessageBox(L"接收网关反馈失败！");
		return -3;
	}
	recStr.ReleaseBuffer();


	// 对返回信息处理
	CStringA ans1="<IMG SRC=\"/images/sign.gif\" hspace=\"6\" vspace=\"0\" align=\"middle\">";
	CStringA ans2="网络断开成功";
	CStringA ans3="断开全部连接成功";

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
		recStr="断开出错\r\n请请登录IP网关断开。";
	}

	// 像界面发送消息，更新显示
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