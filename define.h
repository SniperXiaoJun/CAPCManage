#pragma once

#include "../Include/Guomi/SKFAPI.h"


#define CERT_SUBJECT	1	//�û���
#define CERT_UNIQUEID	2	//֤��ʵ��Ψһ��ʶ
#define CERT_DEPT	3	//����
#define CERT_ISSUE	4	//�䷢��DN
#define CERT_DEVICETYPE	8	//֤���������
#define CERT_CATYPE	9	//CA����
#define CERT_KEYTYPE	10	//�û�֤����Կ���ͣ���˫֤��֤��
#define CERT_DEVICENAME	13	//�û�֤���������
#define CERT_DEVICEPROVIDER	14	//�û�֤������ṩ�߼�csp����
#define CERT_DEVICEAFFIX	15	//�û�֤����ʸ��ӿ�
#define CERT_SIGNPATH	16	//�û�ǩ��֤��·��
#define CERT_EXCHPATH	17	//�û�����֤��·��
#define CERT_SIGNPFXPATH	18	//�û�ǩ��P12֤��·��
#define CERT_EXCHPFXPATH	19	//�û�����P12֤��·��
#define CERT_UNIQUEIDOID	22	//�û�֤��UniqueID��OID


typedef struct READ_CERT_INFO
{
	DEVHANDLE m_hDev; //�豸ID
	HAPPLICATION m_hApp;//Ӧ��ID
	HCONTAINER  m_hAContainer;//����ID
	BOOL m_bSignFlag; //TRUE:ǩ��֤�飬FALSE������֤��
	BYTE* m_pCert;//֤������
	ULONG m_ulCertLen;
	void* m_pReadUkey;
	BOOL m_bCloseApp;
	BOOL m_bCloseContainer;
	char m_byPath[500];
	struct READ_CERT_INFO()
	{
		m_hDev = NULL;
		m_hApp = NULL;
		m_hAContainer = NULL;
		m_bSignFlag = TRUE;
		m_pCert = NULL;
		m_ulCertLen = 0;
		m_pReadUkey = NULL;
		m_bCloseApp = FALSE;
		m_bCloseContainer = FALSE;
		memset(m_byPath,0,500);

	}
}ReadCertInfo;

typedef struct REG_WIN_INFO
{
	std::string m_szVID;
	std::string m_szPID;
	std::string m_szName;
	std::string m_szPath;

}RegWinInfo;

typedef struct DEV_NAME_DLL
{
	std::string m_szDevName;//�豸����
	std::string m_szDllFile;//dllȫ·��
	BOOL m_bOnline;//�豸�Ƿ�����
	void* m_pReadUkey;
	struct DEV_NAME_DLL()
	{
		m_pReadUkey = NULL;
		m_bOnline = FALSE;
	}

}DevNameDll;