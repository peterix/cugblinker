#include "stdafx.h"
#include "global.h"
#include "CUGBLinker.h"
#include "CUGBLinkerDlg.h"
#include "LinkerPage.h"

BOOLEAN connecting=FALSE;
BOOLEAN disconnecting=FALSE;

UINT Connect(LPVOID pvParam)
{
	if(connecting)return 0;
	connecting=TRUE;
	CCUGBLinkerDlg* pMainWnd=(CCUGBLinkerDlg*)theApp.m_pMainWnd;
	CLinkerPage* pLinkerPage=(CLinkerPage*)&(pMainWnd->m_linkerPage);

	// 创建socket并连接目标地址
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
		wszStr=wszStr.Mid(pos+66);
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
	if(disconnecting)return 0;
	disconnecting=TRUE;
	CCUGBLinkerDlg* pMainWnd=(CCUGBLinkerDlg*)theApp.m_pMainWnd;
	CLinkerPage* pLinkerPage=(CLinkerPage*)&(pMainWnd->m_linkerPage);

	int dis=*(int*)pvParam;

	// 创建socket并连接目标地址
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