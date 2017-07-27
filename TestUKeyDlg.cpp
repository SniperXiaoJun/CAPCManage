// TestUKeyDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "CAPCManage.h"
#include "TestUKeyDlg.h"
#include "ReadUKey.h"

extern CReadUKey* g_readUKey;
// CTestUKeyDlg �Ի���

IMPLEMENT_DYNAMIC(CTestUKeyDlg, CDialog)

CTestUKeyDlg::CTestUKeyDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CTestUKeyDlg::IDD, pParent)
{

}

CTestUKeyDlg::~CTestUKeyDlg()
{
}

void CTestUKeyDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CTestUKeyDlg, CDialog)
	ON_BN_CLICKED(IDC_BTN_GETDEVINFO, &CTestUKeyDlg::OnBnClickedBtnGetdevinfo)
	ON_BN_CLICKED(IDC_BTN_APP_MANAGE, &CTestUKeyDlg::OnBnClickedBtnAppManage)
END_MESSAGE_MAP()


// CTestUKeyDlg ��Ϣ�������

void CTestUKeyDlg::OnBnClickedBtnGetdevinfo()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	Test2();
	
}

BOOL CTestUKeyDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	GetDlgItem(IDC_BTN_APP_MANAGE)->ShowWindow(SW_HIDE);

	// TODO:  �ڴ���Ӷ���ĳ�ʼ��

	return TRUE;  // return TRUE unless you set the focus to a control
	// �쳣: OCX ����ҳӦ���� FALSE
}

void CTestUKeyDlg::OnBnClickedBtnAppManage()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}

int CTestUKeyDlg::Test2()
{
	if (NULL == g_readUKey)
	{
		AfxMessageBox("û����ȷ��UKey");
		return 1;
	}
	DEVHANDLE hDev;
	HAPPLICATION hApp;
	ULONG rv;

	rv = g_readUKey->GetDevInfo(&hDev);
	if(rv)
	{
		return 0;
	}
	rv = g_readUKey->AppManage(hDev,&hApp);
	if(rv)
	{
		return 0;
	}
	rv = g_readUKey->RasKeyPairTest(hDev,hApp);
	if(rv)
	{
		return 0;
	}

	rv = g_readUKey->ImportRSAKeyPairTest(hDev,hApp);
	if(rv)
	{
		return 0;
	}


	rv = g_readUKey->SM2KeyPairTest(hDev,hApp);
	if(rv)
	{
		return 0;
	}	
	rv = g_readUKey->ImportSM2KeyPair_Test(hDev,hApp);
	if(rv)
	{
		return 0;
	}

	rv = g_readUKey->ImportSessionKey_Test(hDev,hApp);
	if(rv)
	{
		return 0;
	}
	return 0;
}