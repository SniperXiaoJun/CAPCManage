// PinDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "CAPCManage.h"
#include "PinDlg.h"
#include "ReadUKey.h"

extern CReadUKey* g_readUKey;
// CPinDlg �Ի���

IMPLEMENT_DYNAMIC(CPinDlg, CDialog)

CPinDlg::CPinDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CPinDlg::IDD, pParent)
{

}

CPinDlg::~CPinDlg()
{
}

void CPinDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CPinDlg, CDialog)
	ON_BN_CLICKED(IDOK, &CPinDlg::OnBnClickedOk)
END_MESSAGE_MAP()


// CPinDlg ��Ϣ�������

void CPinDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString strPin;
	GetDlgItemText(IDC_PIN_EDIT,strPin);
	if (strPin.IsEmpty())
	{
		return;
	}

	int rv = -1;

	//int rv = g_readUKey->GetApp(g_readUKey->m_hDev,&(g_readUKey->m_hApp),"EnterSafe");
	//if (rv)
	//{
	//	return;
	//}

	rv = g_readUKey->CheckPin(g_readUKey->m_hDev,g_readUKey->m_hApp,strPin.GetBuffer());
	if (rv)
	{
		AfxMessageBox("PIN �� �������������룡");
		return;
	}
	

	OnOK();
}
