// AdvComboBox.cpp : 实现文件
//

#include "stdafx.h"
#include "AdvComboBox.h"


// CAdvComboBox

IMPLEMENT_DYNAMIC(CAdvComboBox, CComboBox)

CAdvComboBox::CAdvComboBox()
: m_bAutoComplete(false)
{

}

CAdvComboBox::~CAdvComboBox()
{
}


BEGIN_MESSAGE_MAP(CAdvComboBox, CComboBox)
	ON_CONTROL_REFLECT(CBN_EDITUPDATE, &CAdvComboBox::OnCbnEditupdate)
END_MESSAGE_MAP()



// CAdvComboBox 消息处理程序



BOOL CAdvComboBox::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 在此添加专用代码和/或调用基类

	if (pMsg->message == WM_KEYDOWN)
	{
		m_bAutoComplete = TRUE;

		int nVirtKey = (int) pMsg->wParam;
		if (nVirtKey == VK_DELETE || nVirtKey == VK_BACK)
			m_bAutoComplete = FALSE;

		// 显示下拉列表
		//if (nVirtKey >= 0x30 && nVirtKey <= 0x5A)
		//{
		//	ShowDropDown(TRUE);
		//}
	}

	return CComboBox::PreTranslateMessage(pMsg);
}

void CAdvComboBox::OnCbnEditupdate()
{
	// 不需要自动完成时返回
	if (!m_bAutoComplete) 
		return;

	CString str;
	GetWindowText(str); // 获得输入框内文本
	int nLength = str.GetLength();

	// 选定文字内容范围
	DWORD dwCurSel = GetEditSel();
	WORD dStart = LOWORD(dwCurSel);
	WORD dEnd   = HIWORD(dwCurSel);
	TRACE(L"%d %d %d\n",dStart,dEnd,nLength);

	// 查找并将相符项填入输入框中
	int nSel = SelectString(-1, str);
	if (nSel != CB_ERR)
	{
		//TRACE("sel:%d\n",nSel);
		//SetCurSel(nSel);
		SetEditSel(nLength, -1);
	}
	else
	{
		SetWindowText(str);		// 没有相符项，显示原输入项
		if (dwCurSel != CB_ERR)
			SetEditSel(dStart, dEnd);	// 重设输入位置
		//ShowDropDown(FALSE);
	}

}
