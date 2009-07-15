// AdvComboBox.cpp : ʵ���ļ�
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



// CAdvComboBox ��Ϣ�������



BOOL CAdvComboBox::PreTranslateMessage(MSG* pMsg)
{
	// TODO: �ڴ����ר�ô����/����û���

	if (pMsg->message == WM_KEYDOWN)
	{
		m_bAutoComplete = TRUE;

		int nVirtKey = (int) pMsg->wParam;
		if (nVirtKey == VK_DELETE || nVirtKey == VK_BACK)
			m_bAutoComplete = FALSE;

		// ��ʾ�����б�
		//if (nVirtKey >= 0x30 && nVirtKey <= 0x5A)
		//{
		//	ShowDropDown(TRUE);
		//}
	}

	return CComboBox::PreTranslateMessage(pMsg);
}

void CAdvComboBox::OnCbnEditupdate()
{
	// ����Ҫ�Զ����ʱ����
	if (!m_bAutoComplete) 
		return;

	CString str;
	GetWindowText(str); // �����������ı�
	int nLength = str.GetLength();

	// ѡ���������ݷ�Χ
	DWORD dwCurSel = GetEditSel();
	WORD dStart = LOWORD(dwCurSel);
	WORD dEnd   = HIWORD(dwCurSel);
	TRACE(L"%d %d %d\n",dStart,dEnd,nLength);

	// ���Ҳ�������������������
	int nSel = SelectString(-1, str);
	if (nSel != CB_ERR)
	{
		//TRACE("sel:%d\n",nSel);
		//SetCurSel(nSel);
		SetEditSel(nLength, -1);
	}
	else
	{
		SetWindowText(str);		// û��������ʾԭ������
		if (dwCurSel != CB_ERR)
			SetEditSel(dStart, dEnd);	// ��������λ��
		//ShowDropDown(FALSE);
	}

}
