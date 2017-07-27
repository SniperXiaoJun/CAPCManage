
// CAPCManage.cpp : ����Ӧ�ó��������Ϊ��
//

#include "stdafx.h"
#include "CAPCManage.h"
#include "CAPCManageDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CCAPCManageApp

BEGIN_MESSAGE_MAP(CCAPCManageApp, CWinAppEx)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CCAPCManageApp ����

CCAPCManageApp::CCAPCManageApp()
{
	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
	HANDLE hHandle = NULL;
	hHandle = ::CreateMutex(NULL,FALSE, "USAFE_TESTTERM");
	if(GetLastError() == ERROR_ALREADY_EXISTS)
	{
		CloseHandle(hHandle);
		ExitProcess(0);

	/*	HWND hWnd = ::FindWindow(NULL, _T("��ѡ��֤��"));
		if (hWnd == NULL)
		{
			hWnd = ::FindWindow(NULL, _T("��ѡ��֤��"));
		}
		if (hWnd)
		{
			::ShowWindow(hWnd, SW_SHOW);
			::SetForegroundWindow(hWnd);
			::ExitProcess(0);
		}
		else
		{
			ExitProcess(0);
		}*/
	}
}


// Ψһ��һ�� CCAPCManageApp ����

CCAPCManageApp theApp;


// CCAPCManageApp ��ʼ��

BOOL CCAPCManageApp::InitInstance()
{
	// ���һ�������� Windows XP �ϵ�Ӧ�ó����嵥ָ��Ҫ
	// ʹ�� ComCtl32.dll �汾 6 ����߰汾�����ÿ��ӻ���ʽ��
	//����Ҫ InitCommonControlsEx()�����򣬽��޷��������ڡ�
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// ��������Ϊ��������Ҫ��Ӧ�ó�����ʹ�õ�
	// �����ؼ��ࡣ
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinAppEx::InitInstance();

	AfxEnableControlContainer();

	// ��׼��ʼ��
	// ���δʹ����Щ���ܲ�ϣ����С
	// ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
	// ����Ҫ���ض���ʼ������
	// �������ڴ洢���õ�ע�����
	// TODO: Ӧ�ʵ��޸ĸ��ַ�����
	// �����޸�Ϊ��˾����֯��
	SetRegistryKey(_T("Ӧ�ó��������ɵı���Ӧ�ó���"));

	CCAPCManageDlg dlg;
	m_pMainWnd = &dlg;
	INT_PTR nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: �ڴ˷��ô����ʱ��
		//  ��ȷ�������رնԻ���Ĵ���
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: �ڴ˷��ô����ʱ��
		//  ��ȡ�������رնԻ���Ĵ���
	}

	// ���ڶԻ����ѹرգ����Խ����� FALSE �Ա��˳�Ӧ�ó���
	//  ����������Ӧ�ó������Ϣ�á�
	return FALSE;
}
