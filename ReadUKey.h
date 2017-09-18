#pragma once

#include "../Include/Guomi/SKFAPI.h"
#include <string>
#include "define.h"

class CReadUKey
{
public:
	CReadUKey(void);
	~CReadUKey(void);
	HMODULE m_hDll;
	DEVHANDLE m_hDev;
	HAPPLICATION m_hApp;
	HCONTAINER  m_hAContainer;//����ID

	std::string m_szDevName;
	std::string m_szDLLName;


	BOOL initDll();
	BOOL initDll(std::string szDll);
	BOOL LoadDLLEx(HMODULE&	hDll,std::string sDLLName);
	BOOL GetFunAdress(HMODULE hDll,char* csFunName,void*& pFunAdress);

	ULONG EnumCertsFromDev(DEVHANDLE hDev,std::vector<ReadCertInfo>& vecCert,char* pDevName);
	ULONG EnumCertsFromApp(DEVHANDLE hDev,HAPPLICATION phApp,std::vector<ReadCertInfo>& vecCert,char* pDevName,char* pAppName);
	ULONG ExportCert(DEVHANDLE hDev,char* sContainerName,HAPPLICATION phAp, 
		             std::vector<ReadCertInfo>& vecCert,char* pDevName,char* pAppName);

	ULONG RSASignDataEx(HCONTAINER hCon,std::string szGenRandom,BYTE*& pbSignature,ULONG* pulSignLen);
	ULONG RSASignDataEx2(HCONTAINER hCon,BYTE* pData,ULONG ulDataLen,BYTE*& pbSignature,ULONG* pulSignLen);
	ULONG ECCSignDataEx(HCONTAINER hCon,std::string szGenRandom,BYTE*& pbSignature,ULONG* pulSignLen);
	ULONG ECCSignDataEx2(HCONTAINER hCon,BYTE* pData,ULONG ulDataLen,BYTE*& pbSignature,ULONG* pulSignLen);

	ULONG DigestEx(std::string szGenRandom,DEVHANDLE hDev,BYTE*& pbHashData,ULONG* pulHashLen,int nType);
	ULONG DigestEx2(std::string szGenRandom,DEVHANDLE hDev,BYTE*& pbHashData,ULONG* pulHashLen,int nType);
	ULONG ECCDecryptEx2(IN HCONTAINER hContainer, IN PECCCIPHERBLOB pCipherText, 
		OUT BYTE*& pbOutData, IN OUT ULONG *pdwOutDataLen);

	//�������Ƶõ��������
	//ULONG GetContainerFromDevName(ReadCertInfo* pRCI,HCONTAINER& hCon);
	//ULONG GetContainerFromAppName(DEVHANDLE hDev,ReadCertInfo* pRCI,HCONTAINER& hCon);
	//ULONG GetContainerFromContainerName(DEVHANDLE hDev,HAPPLICATION phApp,ReadCertInfo* pRCI,HCONTAINER& hCon);

	BOOL DevManageInterfaces();
	BOOL CallControlInterfaces();
	BOOL AppsManageInterfaces();
	BOOL FileManageInterfaces();
	BOOL ContainerManageInterfaces();
	BOOL LoadCryptInterfaces();
	BOOL LoadOtherInterfaces();


	void PrintError(char *FunName,ULONG ErrorCode,char *Buf=NULL);

	ULONG GetDevInfo(DEVHANDLE *phDev);
	ULONG GetDevInfo2(std::vector<ReadCertInfo>& vecCert);

	ULONG AppManage(DEVHANDLE hDev,HAPPLICATION *phApp);
	ULONG RasKeyPairTest(DEVHANDLE hDev,HAPPLICATION hApp);
	ULONG ImportRSAKeyPairTest(DEVHANDLE hDev,HAPPLICATION hApp);
	ULONG SM2KeyPairTest(DEVHANDLE hDev,HAPPLICATION hApp);
	ULONG ImportSM2KeyPair_Test(DEVHANDLE hDev,HAPPLICATION hApp);
	ULONG ImportSessionKey_Test(DEVHANDLE hDev,HAPPLICATION hApp);

	ULONG GetApp(DEVHANDLE hDev,HAPPLICATION *phApp,std::string szAppName="");
	ULONG CheckPin(DEVHANDLE hDev,HAPPLICATION hApp,std::string szPin,ULONG& ulRetryCount);

	ULONG GetCertEx(HCONTAINER hContainer, BOOL bSignFlag,  BYTE*& pbCert, ULONG& ulCertLen);

	void ClearDLL();

	ULONG RSAPriKeyDecryptEx(HCONTAINER hContainer, std::string szInData, OUT BYTE*& pbOutData, IN OUT DWORD *pdwOutDataLen);
	ULONG RSAPubKeyEncryptEx(DEVHANDLE hDev, IN RSAPUBLICKEYBLOB *pRSAPubKeyBlob,std::string szInData, 
		                     OUT BYTE*& pbOutData, IN OUT DWORD *pdwOutDataLen);

	ULONG RSAPriKeyDecryptEx2(HCONTAINER hContainer, IN BYTE *pbInData, IN DWORD dwInDataLen, OUT BYTE*& pbOutData, IN OUT DWORD *pdwOutDataLen);

	ULONG m_ulType; 

public:
	
	/*
	*	�ȴ��豸�Ĳ���¼�
	*	szDevName		[OUT]���ط����¼����豸����
	*	pulDevNameLen	[IN,OUT]����/���������������ʱ��ʾ���������ȣ����ʱ��ʾ�豸���Ƶ���Ч����,���Ȱ����ַ���������
	*	pulEvent		[OUT]�¼����͡�1��ʾ���룬2��ʾ�γ�
	*	��ע: �ú������������õ�
	*/
	typedef ULONG (DEVAPI *PSKF_WaitForDevEvent)(LPSTR szDevName,ULONG *pulDevNameLen, ULONG *pulEvent);
	PSKF_WaitForDevEvent m_PSKF_WaitForDevEvent;

	typedef ULONG (DEVAPI *PSKF_CancelWaitForDevEvent)();
	PSKF_CancelWaitForDevEvent m_PSKF_CancelWaitForDevEvent;



	/*
	*	��õ�ǰϵͳ�е��豸�б�
	*	bPresent		[IN]ΪTRUE��ʾȡ��ǰ�豸״̬Ϊ���ڵ��豸�б�ΪFALSE��ʾȡ��ǰ����֧�ֵ��豸�б�
	*	szNameList		[OUT]�豸�����б�����ò���ΪNULL������pulSize��������Ҫ���ڴ�ռ��С��ÿ���豸�������Ե���'\0'��������˫'\0'��ʾ�б�Ľ���
	*	pulSize			[IN,OUT]��������������豸�����б�Ļ��������ȣ��������������szNameList����Ҫ�Ŀռ��С
	*/
	typedef ULONG (DEVAPI *PSKF_EnumDev)(BOOL bPresent, LPSTR szNameList, ULONG *pulSize);
	PSKF_EnumDev	m_PSKF_EnumDev;


	/*
	*	ͨ���豸���������豸�������豸�ľ��
	*	szName		[IN]�豸����
	*	phDev		[OUT]�����豸�������
	*/
	typedef ULONG (DEVAPI *PSKF_ConnectDev) (LPSTR szName, DEVHANDLE *phDev);
	PSKF_ConnectDev m_PSKF_ConnectDev;
	/*
	*	�Ͽ�һ���Ѿ����ӵ��豸�����ͷž����
	*	hDev		[IN]�����豸ʱ���ص��豸���
	*/
	typedef ULONG (DEVAPI *PSKF_DisConnectDev) (DEVHANDLE hDev);
	PSKF_DisConnectDev m_PSKF_DisConnectDev;
	/*
	*	��ȡ�豸�Ƿ���ڵ�״̬
	*	szDevName	[IN]��������
	*	pulDevState	[OUT]�����豸״̬
	*/
	typedef ULONG (DEVAPI *PSKF_GetDevState) (LPSTR szDevName, ULONG *pulDevState);
	PSKF_GetDevState m_PSKF_GetDevState;
	/*
	*	�����豸��ǩ
	*	hDev		[IN]�����豸ʱ���ص��豸���
	*	szLabel		[OUT]�豸��ǩ�ַ��������ַ���ӦС��32�ֽ�
	*/
	typedef ULONG (DEVAPI *PSKF_SetLabel) (DEVHANDLE hDev, LPSTR szLabel);
	PSKF_SetLabel m_PSKF_SetLabel;
	/*
	*	��ȡ�豸��һЩ������Ϣ�������豸��ǩ��������Ϣ��֧�ֵ��㷨��
	*	hDev		[IN]�����豸ʱ���ص��豸���
	*	pDevInfo	[OUT]�����豸��Ϣ
	*/
	typedef ULONG (DEVAPI *PSKF_GetDevInfo) (DEVHANDLE hDev, DEVINFO *pDevInfo);
	PSKF_GetDevInfo m_PSKF_GetDevInfo;
	/*
	*	����豸�Ķ�ռʹ��Ȩ
	*	hDev		[IN]�����豸ʱ���ص��豸���
	*	ulTimeOut	[IN]��ʱʱ�䣬��λΪ���롣���Ϊ0xFFFFFFFF��ʾ���޵ȴ�
	*/	
	typedef ULONG (DEVAPI *PSKF_LockDev) (DEVHANDLE hDev, ULONG ulTimeOut);
	PSKF_LockDev m_PSKF_LockDev;
	/*
	*	�ͷŶ��豸�Ķ�ռʹ��Ȩ
	*	hDev		[IN]�����豸ʱ���ص��豸���
	*/
	typedef ULONG (DEVAPI *PSKF_UnlockDev) (DEVHANDLE hDev);
	PSKF_UnlockDev m_PSKF_UnlockDev;

	/************************************************************************/
	/*  2. ���ʿ���				                                            */
	/*	SKF_ChangeDevAuthKey												*/
	/*	SKF_DevAuth															*/
	/*	SKF_ChangePIN														*/
	/*	SKF_GetPINInfo														*/
	/*	SKF_VerifyPIN														*/
	/*	SKF_UnblockPIN														*/
	/*	SKF_ClearSecureState												*/
	/************************************************************************/

	/*
	*	�����豸��֤��Կ
	*	hDev		[IN]����ʱ���ص��豸���
	*	pbKeyValue	[IN]��Կֵ
	*	ulKeyLen	[IN]��Կ����
	*/
	typedef ULONG (DEVAPI *PSKF_ChangeDevAuthKey) (DEVHANDLE hDev, BYTE *pbKeyValue, ULONG ulKeyLen);
	PSKF_ChangeDevAuthKey m_PSKF_ChangeDevAuthKey;

	/*
	*	�豸��֤���豸��Ӧ�ó������֤
	*	hDev			[IN]����ʱ���ص��豸���
	*	pbAuthData		[IN]��֤����
	*	ulLen			[IN]��֤���ݵĳ���
	*/
	typedef ULONG (DEVAPI *PSKF_DevAuth) (DEVHANDLE hDev, BYTE *pbAuthData,ULONG ulLen);
	PSKF_DevAuth m_PSKF_DevAuth;
	/*
	*	�޸�PIN�������޸�Admin��User��PIN�����ԭPIN���󣬷���ʣ�����Դ�������ʣ�����Ϊ0ʱ����ʾPIN�Ѿ�������
	*	hApplication	[IN]Ӧ�þ��
	*	ulPINType		[IN]PIN���ͣ�����ΪADMIN_TYPE=0����USER_TYPE=1
	*	szOldPIN		[IN]ԭPINֵ
	*	szNewPIN		[IN]��PINֵ
	*	pulRetryCount	[OUT]��������Դ���
	*/
	typedef ULONG (DEVAPI *PSKF_ChangePIN) (HAPPLICATION hApplication, ULONG ulPINType, LPSTR szOldPin, LPSTR szNewPin, ULONG *pulRetryCount);
	PSKF_ChangePIN m_PSKF_ChangePIN;

	/*
	*	��ȡPIN����Ϣ������������Դ�������ǰʣ�����Դ������Լ���ǰPIN���Ƿ�Ϊ����Ĭ��PIN��
	*	hApplication		[IN]Ӧ�þ��
	*	ulPINType			[IN]PIN����
	*	pulMaxRetryCount	[OUT]������Դ���
	*	pulRemainRetryCount	[OUT]��ǰʣ�����Դ�������Ϊ0ʱ��ʾ������
	*	pbDefaultPin		[OUT]�Ƿ�Ϊ����Ĭ��PIN��
	*/
	typedef ULONG (DEVAPI *PSKF_GetPINInfo)(HAPPLICATION hApplication, ULONG  ulPINType, ULONG *pulMaxRetryCount, ULONG *pulRemainRetryCount, BOOL *pbDefaultPin);
	PSKF_GetPINInfo m_PSKF_GetPINInfo;

	/*
	*	У��PIN�롣У��ɹ��󣬻�����Ӧ��Ȩ�ޣ����PIN����󣬻᷵��PIN������Դ����������Դ���Ϊ0ʱ��ʾPIN���Ѿ�����
	*	hApplication	[IN]Ӧ�þ��
	*	ulPINType		[IN]PIN���ͣ�����ΪADMIN_TYPE=0����USER_TYPE=1
	*	szPIN			[IN]PINֵ
	*	pulRetryCount	[OUT]����󷵻ص����Դ���
	*/
	typedef ULONG (DEVAPI *PSKF_VerifyPIN) (HAPPLICATION hApplication, ULONG  ulPINType, LPSTR szPIN, ULONG *pulRetryCount);
	PSKF_VerifyPIN m_PSKF_VerifyPIN;
	/*
	*	���û���PIN��������ͨ�����øú����������û�PIN�롣
	*	�������û�PIN�뱻���ó���ֵ���û�PIN������Դ���Ҳ�ָ���ԭֵ��
	*	hApplication	[IN]Ӧ�þ��
	*	szAdminPIN		[IN]����ԱPIN��
	*	szNewUserPIN	[IN]�µ��û�PIN��
	*	pulRetryCount	[OUT]����ԱPIN�����ʱ������ʣ�����Դ���
	*/
	typedef ULONG (DEVAPI *PSKF_UnblockPIN) (HAPPLICATION hApplication, LPSTR szAdminPIN, LPSTR szNewUserPIN,  ULONG *pulRetryCount);
	PSKF_UnblockPIN m_PSKF_UnblockPIN;

	/*
	*	���Ӧ�õ�ǰ�İ�ȫ״̬
	*	hApplication	[IN]Ӧ�þ��
	*/
	typedef ULONG (DEVAPI *PSKF_ClearSecureState) (HAPPLICATION hApplication);
	PSKF_ClearSecureState m_PSKF_ClearSecureState;

	/************************************************************************/
	/*  3. Ӧ�ù���				                                            */
	/*	SKF_CreateApplication												*/
	/*	SKF_EnumApplication													*/
	/*	SKF_DeleteApplication												*/
	/*	SKF_OpenApplication													*/
	/*	SKF_CloseApplication												*/
	/************************************************************************/

	/*
	*	����һ��Ӧ��
	*	hDev					[IN]�����豸ʱ���ص��豸���
	*	szAppName				[IN]Ӧ������
	*	szAdminPIN				[IN]����ԱPIN
	*	dwAdminPinRetryCount	[IN]����ԱPIN������Դ���
	*	szUserPIN				[IN]�û�PIN
	*	dwAdminPinRetryCount	[IN]�û�PIN������Դ���
	*	dwCreateFileRights		[IN]�ڸ�Ӧ���´����ļ���������Ȩ��
	*	phApplication			[OUT]Ӧ�õľ��
	*/
	typedef ULONG (DEVAPI *PSKF_CreateApplication)(DEVHANDLE hDev, LPSTR szAppName, LPSTR szAdminPin, DWORD dwAdminPinRetryCount,LPSTR szUserPin, DWORD dwUserPinRetryCount,DWORD dwCreateFileRights, HAPPLICATION *phApplication);
	PSKF_CreateApplication m_PSKF_CreateApplication;

	/*
	*	ö���豸�������ڵ�����Ӧ��
	*	hDev			[IN]�����豸ʱ���ص��豸���
	*	szAppName		[OUT]����Ӧ�������б�, ����ò���Ϊ�գ�����pulSize��������Ҫ���ڴ�ռ��С��
	*						 ÿ��Ӧ�õ������Ե���'\0'��������˫'\0'��ʾ�б�Ľ�����
	*	pulSize			[IN,OUT]�������������Ӧ�����ƵĻ��������ȣ��������������szAppName��ռ�õĵĿռ��С
	*/
	typedef ULONG (DEVAPI *PSKF_EnumApplication) (DEVHANDLE hDev, LPSTR szAppName,ULONG *pulSize);
	PSKF_EnumApplication m_PSKF_EnumApplication;
	/*
	*	ɾ��ָ����Ӧ��
	*	hDev			[IN]�����豸ʱ���ص��豸���
	*	szAppName		[IN]Ӧ������
	*/
	typedef ULONG (DEVAPI *PSKF_DeleteApplication) (DEVHANDLE hDev, LPSTR szAppName);
	PSKF_DeleteApplication m_PSKF_DeleteApplication;
	/*
	*	��ָ����Ӧ��
	*	hDev			[IN]�����豸ʱ���ص��豸���
	*	szAppName		[IN]Ӧ������
	*	phApplication	[OUT]Ӧ�õľ��
	*/
	typedef ULONG (DEVAPI *PSKF_OpenApplication) (DEVHANDLE hDev, LPSTR szAppName, HAPPLICATION *phApplication);
	PSKF_OpenApplication m_PSKF_OpenApplication;
	/*
	*	�ر�Ӧ�ò��ͷ�Ӧ�þ��
	*	hApplication	[IN]Ӧ�õľ��
	*/
	typedef ULONG (DEVAPI *PSKF_CloseApplication) (HAPPLICATION hApplication);
	PSKF_CloseApplication m_PSKF_CloseApplication;

	/************************************************************************/
	/*  4. �ļ�����				                                            */
	/*	SKF_CreateFile														*/
	/*	SKF_DeleteFile														*/
	/*	SKF_EnumFiles														*/
	/*	SKF_GetFileInfo														*/
	/*	SKF_ReadFile														*/
	/*	SKF_WriteFile														*/
	/************************************************************************/

	/*
	*	����һ���ļ��������ļ�ʱҪָ���ļ������ƣ���С���Լ��ļ��Ķ�дȨ��
	*	hApplication		[IN]Ӧ�þ��
	*	szFileName			[IN]�ļ����ƣ����Ȳ��ô���32���ֽ�
	*	ulFileSize			[IN]�ļ���С
	*	ulReadRights		[IN]�ļ���Ȩ��
	*	ulWriteRights		[IN]�ļ�дȨ��
	*/
	typedef ULONG (DEVAPI *PSKF_CreateFile ) (HAPPLICATION hApplication, LPSTR szFileName, ULONG ulFileSize, ULONG ulReadRights,ULONG ulWriteRights);
	PSKF_CreateFile m_PSKF_CreateFile;

	/*
	*	ɾ��ָ���ļ����ļ�ɾ�����ļ���д���������Ϣ����ʧ���ļ����豸�е�ռ�õĿռ佫���ͷš�
	*	hApplication		[IN]Ҫɾ���ļ����ڵ�Ӧ�þ��
	*	szFileName			[IN]Ҫɾ���ļ�������
	*/
	typedef ULONG (DEVAPI *PSKF_DeleteFile ) (HAPPLICATION hApplication, LPSTR szFileName);
	PSKF_DeleteFile m_PSKF_DeleteFile;
	/*
	*	ö��һ��Ӧ���´��ڵ������ļ�
	*	hApplication		[IN]Ӧ�õľ��
	*	szFileList			[OUT]�����ļ������б��ò���Ϊ�գ���pulSize�����ļ���Ϣ����Ҫ�Ŀռ��С��ÿ���ļ������Ե���'\0'��������˫'\0'��ʾ�б�Ľ�����
	*	pulSize				[OUT]����Ϊ���ݻ������Ĵ�С�����Ϊʵ���ļ����ƵĴ�С
	*/
	typedef ULONG (DEVAPI *PSKF_EnumFiles ) (HAPPLICATION hApplication, LPSTR szFileList, ULONG *pulSize);
	PSKF_EnumFiles m_PSKF_EnumFiles;

	/*
	*	��ȡӦ���ļ���������Ϣ�������ļ��Ĵ�С��Ȩ�޵�
	*	hApplication		[IN]�ļ�����Ӧ�õľ��
	*	szFileName			[IN]�ļ�����
	*	pFileInfo			[OUT]�ļ���Ϣ��ָ���ļ����Խṹ��ָ��
	*/
	typedef ULONG (DEVAPI *PSKF_GetFileInfo ) (HAPPLICATION hApplication, LPSTR szFileName, FILEATTRIBUTE *pFileInfo);
	PSKF_GetFileInfo m_PSKF_GetFileInfo;

	/*
	*	��ȡ�ļ�����
	*	hApplication		[IN]�ļ����ڵ�Ӧ�þ��
	*	szFileName			[IN]�ļ���
	*	ulOffset			[IN]�ļ���ȡƫ��λ��
	*	ulSize				[IN]Ҫ��ȡ�ĳ���
	*	pbOutData			[OUT]�������ݵĻ�����
	*	pulOutLen			[OUT]�����ʾ�����Ļ�������С�������ʾʵ�ʶ�ȡ���ص����ݴ�С
	*/
	typedef ULONG (DEVAPI *PSKF_ReadFile ) (HAPPLICATION hApplication, LPSTR szFileName, ULONG ulOffset, ULONG ulSize, BYTE * pbOutData, ULONG *pulOutLen);
	PSKF_ReadFile m_PSKF_ReadFile;

	/*
	*	д���ݵ��ļ���
	*	hApplication		[IN]�ļ����ڵ�Ӧ�þ��
	*	szFileName			[IN]�ļ���
	*	ulOffset			[IN]д���ļ���ƫ����
	*	pbData				[IN]д�����ݻ�����
	*	ulSize				[IN]д�����ݵĴ�С
	*/
	typedef ULONG (DEVAPI *PSKF_WriteFile ) (HAPPLICATION hApplication, LPSTR szFileName, ULONG  ulOffset, BYTE *pbData, ULONG ulSize);
	PSKF_WriteFile m_PSKF_WriteFile;


	/************************************************************************/
	/*  5. ��������				                                            */
	/*	SKF_CreateContainer													*/
	/*	SKF_DeleteContainer													*/
	/*	SKF_OpenContainer													*/
	/*	SKF_CloseContainer													*/
	/*	SKF_EnumContainer													*/
	/************************************************************************/

	/*
	*	��Ӧ���½���ָ�����Ƶ������������������
	*	hApplication		[IN]Ӧ�þ��
	*	szContainerName		[IN]ASCII�ַ�������ʾ���������������ƣ��������Ƶ���󳤶Ȳ��ܳ���64�ֽ�
	*	phContainer			[OUT]�����������������������
	*/
	typedef ULONG (DEVAPI *PSKF_CreateContainer ) (HAPPLICATION hApplication, LPSTR szContainerName, HCONTAINER *phContainer);
	PSKF_CreateContainer m_PSKF_CreateContainer;
	/*
	*	��Ӧ����ɾ��ָ�����Ƶ��������ͷ�������ص���Դ
	*	hApplication		[IN]Ӧ�þ��
	*	szContainerName		[IN]ָ��ɾ������������
	*/
	typedef ULONG (DEVAPI *PSKF_DeleteContainer) (HAPPLICATION hApplication, LPSTR szContainerName);
	PSKF_DeleteContainer m_PSKF_DeleteContainer;

	/*
	*	��ȡ�������
	*	hApplication		[IN]Ӧ�þ��
	*	szContainerName		[IN]��������
	*	phContainer			[OUT]�������������ľ��
	*/
	typedef ULONG (DEVAPI *PSKF_OpenContainer) (HAPPLICATION hApplication,LPSTR szContainerName,HCONTAINER *phContainer);
	PSKF_OpenContainer m_PSKF_OpenContainer;

	/*
	*	�ر�������������ͷ�������������Դ
	*	hContainer			[OUT]�������
	*/
	typedef ULONG (DEVAPI *PSKF_CloseContainer) (HCONTAINER hContainer);
	PSKF_CloseContainer m_PSKF_CloseContainer;

	/*
	*	ö��Ӧ���µ������������������������б�
	*	hApplication		[IN]Ӧ�þ��
	*	szContainerName		[OUT]ָ�����������б�����������˲���ΪNULLʱ��pulSize��ʾ������������Ҫ�������ĳ��ȣ�����˲�����ΪNULLʱ���������������б�ÿ���������Ե���'\0'Ϊ�������б���˫'\0'����
	*	pulSize				[OUT]����ǰ��ʾszContainerName�������ĳ��ȣ��������������б�ĳ���
	*/
	typedef ULONG (DEVAPI *PSKF_EnumContainer) (
		IN HAPPLICATION	hApplication,
		OUT LPSTR			szContainerName,
		OUT ULONG*		pulSize
		);

	PSKF_EnumContainer m_PSKF_EnumContainer;
	/*
	��ȡ����������
	hContainer	[IN] ���������
	pulContainerType	[OUT] ��õ��������͡�ָ��ָ���ֵΪ0��ʾδ������δ�������ͻ���Ϊ��������Ϊ1��ʾΪRSA������Ϊ2��ʾΪECC������
	*/

	typedef ULONG (DEVAPI *PSKF_GetContainerType) (HCONTAINER hContainer, ULONG *pulContainerType);
	PSKF_GetContainerType m_PSKF_GetContainerType;


	typedef ULONG (DEVAPI *PSKF_ImportCertificate) (HCONTAINER hContainer, BOOL bSignFlag,  BYTE* pbCert, ULONG ulCertLen);
	PSKF_ImportCertificate m_PSKF_ImportCertificate;

	typedef ULONG (DEVAPI *PSKF_ExportCertificate) (HCONTAINER hContainer, BOOL bSignFlag,  BYTE* pbCert, ULONG *pulCertLen);
	PSKF_ExportCertificate m_PSKF_ExportCertificate;

	/************************************************************************/
	/*  6. �������				                                            */
	/*	SKF_GetRandom														*/
	/*	SKF_GenExtRSAKey													*/
	/*	SKF_GenRSAKeyPair													*/
	/*	SKF_ImportRSAKeyPair												*/
	/*	SKF_RSASignData														*/
	/*	SKF_RSAVerify														*/
	/*	SKF_RSAExportSessionKey												*/
	/*	SKF_ExtRSAPubKeyOperation											*/
	/*	SKF_ExtRSAPriKeyOperation											*/
	/*	SKF_GenECCKeyPair													*/
	/*	SKF_ImportECCKeyPair												*/
	/*	SKF_ECCSignData														*/
	/*	SKF_ECCVerify														*/
	/*	SKF_ECCExportSessionKey												*/
	/*	SKF_ExtECCEncrypt													*/
	/*	SKF_ExtECCDecrypt													*/
	/*	SKF_ExtECCSign														*/
	/*	SKF_ExtECCVerify													*/
	/*	SKF_ExportPublicKey													*/
	/*	SKF_ImportSessionKey												*/
	/*	SKF_SetSymmKey														*/
	/*	SKF_EncryptInit														*/
	/*	SKF_Encrypt															*/
	/*	SKF_EncryptUpdate													*/
	/*	SKF_EncryptFinal													*/
	/*	SKF_DecryptInit														*/
	/*	SKF_Decrypt															*/
	/*	SKF_DecryptUpdate													*/
	/*	SKF_DecryptFinal													*/
	/*	SKF_DigestInit														*/
	/*	SKF_Digest															*/
	/*	SKF_DigestUpdate													*/
	/*	SKF_DigestFinal														*/
	/*	SKF_MACInit															*/
	/*	SKF_MAC																*/
	/*	SKF_MACUpdate														*/
	/*	SKF_MACFinal														*/
	/************************************************************************/

	/*
	*	����ָ�����ȵ������
	*	hDev			[IN] �豸���
	*	pbRandom		[OUT] ���ص������
	*	ulRandomLen		[IN] ���������
	*/
	typedef ULONG (DEVAPI *PSKF_GenRandom ) (DEVHANDLE hDev, BYTE *pbRandom,ULONG ulRandomLen);
	PSKF_GenRandom m_PSKF_GenRandom;

	/*
	*	���豸����RSA��Կ�Բ��������
	*	hDev			[IN] �豸���
	*	ulBitsLen		[IN] ��Կģ��
	*	pBlob			[OUT] ���ص�˽Կ���ݽṹ
	*/
	typedef ULONG (DEVAPI *PSKF_GenExtRSAKey ) (DEVHANDLE hDev, ULONG ulBitsLen, RSAPRIVATEKEYBLOB *pBlob);
	PSKF_GenExtRSAKey m_PSKF_GenExtRSAKey;
	/*
	*	����RSAǩ����Կ�Բ����ǩ����Կ
	*	hContainer		[IN] �������
	*	ulBitsLen		[IN] ��Կģ��
	*	pBlob			[OUT] ���ص�RSA��Կ���ݽṹ
	*/
	typedef ULONG (DEVAPI *PSKF_GenRSAKeyPair ) (HCONTAINER hContainer, ULONG ulBitsLen, RSAPUBLICKEYBLOB *pBlob);
	PSKF_GenRSAKeyPair m_PSKF_GenRSAKeyPair;

	/*
	*	����RSA���ܹ�˽Կ��
	*	hContainer		[IN] �������
	*	ulSymAlgId		[IN] �Գ��㷨��Կ��ʶ
	*	pbWrappedKey	[IN] ʹ�ø�������ǩ����Կ�����ĶԳ��㷨��Կ
	*	ulWrappedKeyLen	[IN] �����ĶԳ��㷨��Կ����
	*	pbEncryptedData	[IN] �Գ��㷨��Կ������RSA����˽Կ��˽Կ�ĸ�ʽ��ѭPKCS #1 v2.1: RSA Cryptography Standard�е�˽Կ��ʽ����
	*	ulEncryptedDataLen	[IN] �Գ��㷨��Կ������RSA���ܹ�˽Կ�Գ���
	*/
	typedef ULONG (DEVAPI *PSKF_ImportRSAKeyPair ) ( HCONTAINER hContainer, ULONG ulSymAlgId, 
		BYTE *pbWrappedKey, ULONG ulWrappedKeyLen,
		BYTE *pbEncryptedData, ULONG ulEncryptedDataLen);
	PSKF_ImportRSAKeyPair m_PSKF_ImportRSAKeyPair;

	/*
	*	ʹ��hContainerָ��������ǩ��˽Կ����ָ������pbData��������ǩ����ǩ����Ľ����ŵ�pbSignature������������pulSignLenΪǩ���ĳ���
	*	hContainer		[IN] ����ǩ����˽Կ�����������
	*	pbData			[IN] ��ǩ��������
	*	ulDataLen		[IN] ǩ�����ݳ��ȣ�Ӧ������RSA��Կģ��-11
	*	pbSignature		[OUT] ���ǩ������Ļ�����ָ�룬���ֵΪNULL������ȡ��ǩ���������
	*	pulSigLen		[IN,OUT] ����Ϊǩ�������������С�����Ϊǩ���������
	*/
	typedef ULONG (DEVAPI *PSKF_RSASignData) (HCONTAINER hContainer, BYTE *pbData, ULONG  ulDataLen, BYTE *pbSignature, ULONG *pulSignLen);
	PSKF_RSASignData m_PSKF_RSASignData;
	/*
	*	��֤RSAǩ������pRSAPubKeyBlob�ڵĹ�Կֵ�Դ���ǩ���ݽ�����ǩ��
	*	hDev			[IN] �����豸ʱ���ص��豸���
	*	pRSAPubKeyBlob	[IN] RSA��Կ���ݽṹ
	*	pbData			[IN] ����֤ǩ��������
	*	ulDataLen		[IN] ���ݳ��ȣ�Ӧ�����ڹ�Կģ��-11
	*	pbSignature		[IN] ����֤��ǩ��ֵ
	*	ulSigLen		[IN] ǩ��ֵ���ȣ�����Ϊ��Կģ��
	*/
	typedef ULONG (DEVAPI *PSKF_RSAVerify ) (DEVHANDLE hDev , RSAPUBLICKEYBLOB* pRSAPubKeyBlob, BYTE *pbData, ULONG  ulDataLen, BYTE *pbSignature, ULONG ulSignLen);
	PSKF_RSAVerify m_PSKF_RSAVerify;
	/*
	*	���ɻỰ��Կ�����ⲿ��Կ���������
	*	hContainer		[IN] �������
	*	ulAlgID			[IN] �Ự��Կ���㷨��ʶ
	*	pPubKey			[IN] ���ܻỰ��Կ��RSA��Կ���ݽṹ
	*	pbData			[OUT] �����ļ��ܻỰ��Կ���ģ�����PKCS#1v1.5��Ҫ���װ
	*	pulDataLen		[OUT] ���ص������ݳ���
	*	phSessionKey	[OUT] ��������Կ���
	*/

	typedef ULONG (DEVAPI *PSKF_RSAExportSessionKey ) (HCONTAINER hContainer, ULONG ulAlgId, RSAPUBLICKEYBLOB *pPubKey, BYTE *pbData, ULONG  *pulDataLen, HANDLE *phSessionKey);
	PSKF_RSAExportSessionKey m_PSKF_RSAExportSessionKey;

	/*
	*	ʹ���ⲿ�����RSA��Կ��������������Կ���㲢������
	*	hDev			[IN] �豸���
	*	pRSAPubKeyBlob	[IN] RSA��Կ���ݽṹ
	*	pbInput			[IN] ָ��������ԭʼ���ݻ�����
	*	ulInputLen		[IN] ������ԭʼ���ݵĳ��ȣ�����Ϊ��Կģ��
	*	pbOutput		[OUT] ָ��RSA��Կ������������������ò���ΪNULL������pulOutputLen������������ʵ�ʳ���
	*	pulOutputLen	[OUT] ����ǰ��ʾpbOutput�������ĳ��ȣ�����RSA��Կ��������ʵ�ʳ���
	*/
	typedef ULONG (DEVAPI *PSKF_ExtRSAPubKeyOperation ) (DEVHANDLE hDev, RSAPUBLICKEYBLOB* pRSAPubKeyBlob,BYTE* pbInput, ULONG ulInputLen, BYTE* pbOutput, ULONG* pulOutputLen);
	PSKF_ExtRSAPubKeyOperation m_PSKF_ExtRSAPubKeyOperation;

	/*
	*	ֱ��ʹ���ⲿ�����RSA˽Կ������������˽Կ���㲢������
	*	hDev			[IN] �豸���
	*	pRSAPriKeyBlob	[IN] RSA˽Կ���ݽṹ
	*	pbInput			[IN] ָ����������ݻ�����
	*	ulInputLen		[IN] ���������ݵĳ��ȣ�����Ϊ��Կģ��
	*	pbOutput		[OUT] RSA˽Կ������������ò���ΪNULL������pulOutputLen������������ʵ�ʳ���
	*	pulOutputLen	[OUT] ����ǰ��ʾpbOutput�������ĳ��ȣ�����RSA˽Կ��������ʵ�ʳ���
	*/
	typedef ULONG (DEVAPI *PSKF_ExtRSAPriKeyOperation ) (DEVHANDLE hDev, RSAPRIVATEKEYBLOB* pRSAPriKeyBlob,BYTE* pbInput, ULONG ulInputLen, BYTE* pbOutput, ULONG* pulOutputLen);
	PSKF_ExtRSAPriKeyOperation m_PSKF_ExtRSAPriKeyOperation;
	/*
	*	����ECCǩ����Կ�Բ����ǩ����Կ��
	*	hContainer		[IN] �������
	*	ֻ֧��SGD_SM2_1�㷨
	*	pBlob			[OUT] ����ECC��Կ���ݽṹ
	*/

	typedef ULONG (DEVAPI *PSKF_GenECCKeyPair ) (HCONTAINER hContainer, ULONG ulAlgId, ECCPUBLICKEYBLOB *pBlob);
	PSKF_GenECCKeyPair m_PSKF_GenECCKeyPair;

	/*
	*	����ECC��˽Կ��
	*	hContainer		[IN] �������
	*	pbWrapedData	[IN] ���ܱ�����ECC���ܹ�˽Կ������
	*	ulWrapedLen		[IN] ���ݳ���
	*/

	typedef ULONG (DEVAPI *PSKF_ImportECCKeyPair ) (  HCONTAINER hContainer, PENVELOPEDKEYBLOB pEnvelopedKeyBlob);
	PSKF_ImportECCKeyPair m_PSKF_ImportECCKeyPair;

	/*
	*	ECC����ǩ��������ECC�㷨��ָ��˽ԿhKey����ָ������pbData��������ǩ����ǩ����Ľ����ŵ�pbSignature������������pulSignLenΪǩ��ֵ�ĳ���
	*	hContainer		[IN] ����ǩ����˽Կ�����������
	*	pbData			[IN] ��ǩ��������
	*	ulDataLen		[IN] ��ǩ�����ݳ��ȣ�����С����Կģ��
	*	pbSignature		[OUT] ǩ��ֵ��ΪNULLʱ���ڻ��ǩ��ֵ�ĳ���
	*	pulSigLen		[IN,OUT] ����ǩ��ֵ���ȵ�ָ�� 
	*/

	typedef ULONG (DEVAPI *PSKF_ECCSignData ) (HCONTAINER hContainer, BYTE *pbData, ULONG  ulDataLen, PECCSIGNATUREBLOB pSignature);
	PSKF_ECCSignData m_PSKF_ECCSignData;

	/*
	*	��ECC��Կ�����ݽ�����ǩ
	*	hDev			[IN] �豸���
	*	pECCPubKeyBlob	[IN] ECC��Կ���ݽṹ
	*	pbData			[IN] ����֤ǩ��������
	*	ulDataLen		[IN] ���ݳ���
	*	pbSignature		[IN] ����֤��ǩ��ֵ
	*	ulSigLen		[IN] ǩ��ֵ����
	*/
	typedef ULONG (DEVAPI *PSKF_ECCVerify ) (DEVHANDLE hDev , ECCPUBLICKEYBLOB* pECCPubKeyBlob, BYTE *pbData, ULONG  ulDataLen, PECCSIGNATUREBLOB pSignature);
	PSKF_ECCVerify m_PSKF_ECCVerify;

	/*
	*	���ɻỰ��Կ�����ⲿ��Կ���������
	*	hContainer		[IN] �������
	*	ulAlgID			[IN] �Ự��Կ���㷨��ʶ
	*	pPubKey			[IN] ����������Կ����Կ�ṹ
	*	pbData			[OUT] �����ļ��ܻỰ��Կ����
	*	pulDataLen		[OUT] ���ص������ݳ���
	*	phSessionKey	[OUT] �Ự��Կ���
	*/
	typedef ULONG (DEVAPI *PSKF_ECCExportSessionKey ) (HCONTAINER hContainer, ULONG ulAlgId, ECCPUBLICKEYBLOB *pPubKey, PECCCIPHERBLOB pData, HANDLE *phSessionKey);
	PSKF_ECCExportSessionKey m_PSKF_ECCExportSessionKey;

	/*
	*	ʹ���ⲿ�����ECC��Կ�������������������㲢������
	*	hDev			[IN] �豸���
	*	pECCPubKeyBlob	[IN] ECC��Կ���ݽṹ
	*	pbPlainText		[IN] �����ܵ���������
	*	ulPlainTextLen	[IN] �������������ݵĳ���
	*	pbCipherText	[OUT] ָ���������ݻ�����������ò���ΪNULL������pulCipherTextLen�����������ݵ�ʵ�ʳ���
	*	pulCipherTextLen[OUT] ����ǰ��ʾpbCipherText�������ĳ��ȣ������������ݵ�ʵ�ʳ���
	*/

	typedef ULONG (DEVAPI *PSKF_ExtECCEncrypt ) (DEVHANDLE hDev, ECCPUBLICKEYBLOB*  pECCPubKeyBlob,BYTE* pbPlainText, ULONG ulPlainTextLen, PECCCIPHERBLOB pCipherText);
	PSKF_ExtECCEncrypt m_PSKF_ExtECCEncrypt;

	/*
	*	ʹ���ⲿ�����ECC˽Կ�������������������㲢������
	*	hDev			[IN] �豸���
	*	pRSAPriKeyBlob	[IN] ECC˽Կ���ݽṹ
	*	pbInput			[IN] �����ܵ���������
	*	ulInputLen		[IN] �������������ݵĳ���
	*	pbOutput		[OUT] �����������ݣ�����ò���ΪNULL������pulPlainTextLen�����������ݵ�ʵ�ʳ���
	*	pulOutputLen	[OUT] ����ǰ��ʾpbPlainText�������ĳ��ȣ������������ݵ�ʵ�ʳ���
	*/
	typedef ULONG (DEVAPI *PSKF_ExtECCDecrypt ) (DEVHANDLE hDev, ECCPRIVATEKEYBLOB*  pECCPriKeyBlob, PECCCIPHERBLOB pCipherText, BYTE* pbPlainText, ULONG* pulPlainTextLen);
	PSKF_ExtECCDecrypt m_PSKF_ExtECCDecrypt;

	/*
	*	ʹ���ⲿ�����ECC˽Կ������������ǩ�����㲢��������
	*	hDev			[IN] �豸���
	*	pRSAPriKeyBlob	[IN] ECC˽Կ���ݽṹ
	*	pbData			[IN] ��ǩ������
	*	ulDataLen		[IN] ��ǩ�����ݵĳ���
	*	pbSignature		[OUT] ǩ��ֵ������ò���ΪNULL������pulSignatureLen����ǩ�������ʵ�ʳ���
	*	pulSignatureLen	[OUT] ����ǰ��ʾpbSignature�������ĳ��ȣ�����ǩ�������ʵ�ʳ���
	*/
	typedef ULONG (DEVAPI *PSKF_ExtECCSign ) (DEVHANDLE hDev, ECCPRIVATEKEYBLOB*  pECCPriKeyBlob, BYTE* pbData, ULONG ulDataLen, PECCSIGNATUREBLOB pSignature);
	PSKF_ExtECCSign m_PSKF_ExtECCSign;

	/*
	*	�ⲿʹ�ô����ECC��Կ��ǩ����֤
	*	hDev			[IN] �豸���
	*	pECCPubKeyBlob	[IN] ECC��Կ���ݽṹ
	*	pbData			[IN] ����֤����
	*	ulDataLen		[IN] ����֤���ݵĳ���
	*	pbSignature		[OUT] ǩ��ֵ
	*	ulSignLen		[OUT] ǩ��ֵ�ĳ���
	*/
	typedef ULONG (DEVAPI *PSKF_ExtECCVerify ) (DEVHANDLE hDev, ECCPUBLICKEYBLOB*  pECCPubKeyBlob,BYTE* pbData, ULONG ulDataLen, PECCSIGNATUREBLOB pSignature);
	PSKF_ExtECCVerify m_PSKF_ExtECCVerify;

	/*
	*	ʹ��ECC��ԿЭ���㷨��Ϊ����Ự��Կ������Э�̲�����������ʱECC��Կ�ԵĹ�Կ��Э�̾��
	*	hContainer		[IN] �������
	*	ulAlgId			[IN] �Ự��Կ�㷨��ʶ
	*	pTempECCPubKeyBlob	[OUT] ������ʱECC��Կ
	*	pbID			[IN] ���𷽵�ID
	*	ulIDLen			[IN] ����ID�ĳ��ȣ�������32
	*	phAgreementHandle	[OUT] ���ص���ԿЭ�̾��
	*/
	typedef ULONG (DEVAPI *PSKF_GenerateAgreementDataWithECC ) (HCONTAINER hContainer, ULONG ulAlgId,ECCPUBLICKEYBLOB*  pTempECCPubKeyBlob,BYTE* pbID, ULONG ulIDLen,HANDLE *phAgreementHandle);
	PSKF_GenerateAgreementDataWithECC m_PSKF_GenerateAgreementDataWithECC;

	/*
	*	ʹ��ECC��ԿЭ���㷨������Э�̲���������Ự��Կ�������ʱECC��Կ�Թ�Կ�������ز�������Կ���
	*	hContainer					[IN] �������
	*	ulAlgId						[IN] �Ự��Կ�㷨��ʶ
	*	pSponsorECCPubKeyBlob		[IN] ���𷽵�ECC��Կ
	*	pSponsorTempECCPubKeyBlob	[IN] ���𷽵���ʱECC��Կ
	*	pTempECCPubKeyBlob			[OUT] ��Ӧ������ʱECC��Կ
	*	pbID						[IN] ��Ӧ����ID
	*	ulIDLen						[IN] ��Ӧ��ID�ĳ��ȣ�������32
	*	pbSponsorID					[IN] ���𷽵�ID
	*	ulSponsorIDLen				[IN] ����ID�ĳ��ȣ�������32
	*	phKeyHandle					[OUT] ���صĶԳ��㷨��Կ���
	*/
	typedef ULONG (DEVAPI *PSKF_GenerateAgreementDataAndKeyWithECC) (
		HANDLE hContainer, ULONG ulAlgId,
		ECCPUBLICKEYBLOB*  pSponsorECCPubKeyBlob,
		ECCPUBLICKEYBLOB*  pSponsorTempECCPubKeyBlob,
		ECCPUBLICKEYBLOB*  pTempECCPubKeyBlob,
		BYTE* pbID, ULONG ulIDLen, BYTE *pbSponsorID, ULONG ulSponsorIDLen,
		HANDLE *phKeyHandle);
	PSKF_GenerateAgreementDataAndKeyWithECC m_PSKF_GenerateAgreementDataAndKeyWithECC;

	/*
	*	ʹ��ECC��ԿЭ���㷨��ʹ������Э�̾������Ӧ����Э�̲�������Ự��Կ��ͬʱ���ػỰ��Կ���
	*	hAgreementHandle			[IN] ��ԿЭ�̾��
	*	pECCPubKeyBlob				[IN] �ⲿ�������Ӧ��ECC��Կ
	*	pTempECCPubKeyBlob			[IN] �ⲿ�������Ӧ����ʱECC��Կ
	*	pbID						[IN] ��Ӧ����ID
	*	ulIDLen						[IN] ��Ӧ��ID�ĳ��ȣ�������32
	*	phKeyHandle					[OUT] ���ص���Կ���
	*/
	typedef ULONG (DEVAPI *PSKF_GenerateKeyWithECC ) (HANDLE hAgreementHandle,
		ECCPUBLICKEYBLOB*  pECCPubKeyBlob,
		ECCPUBLICKEYBLOB*  pTempECCPubKeyBlob,
		BYTE* pbID, ULONG ulIDLen, HANDLE *phKeyHandle);
	PSKF_GenerateKeyWithECC m_PSKF_GenerateKeyWithECC;


	/*
	*	���������е�ǩ����Կ���߼��ܹ�Կ
	*	hContainer		[IN] �������
	*	bSignFlag		[IN] TRUE��ʾ����ǩ����Կ��FALSE��ʾ�������ܹ�Կ
	*	pbBlob			[OUT] ָ��RSA��Կ�ṹ��RSAPUBLICKEYBLOB������ECC��Կ�ṹ��ECCPUBLICKEYBLOB��������˲���ΪNULLʱ����pulBlobLen����pbBlob�ĳ���
	*	pulBlobLen		[IN,OUT] ����ʱ��ʾpbBlob�ĳ��ȣ����ص�����Կ�ṹ�Ĵ�С
	*/
	typedef ULONG (DEVAPI *PSKF_ExportPublicKey ) (HCONTAINER hContainer, BOOL bSignFlag, BYTE* pbBlob, ULONG* pulBlobLen);
	PSKF_ExportPublicKey m_PSKF_ExportPublicKey;

	/*
	*	����Ự��Կ
	*	hContainer		[IN] �������
	*	ulAlgID			[IN] �Ự��Կ���㷨��ʶ
	*	pbWrapedData	[IN] Ҫ���������
	*	ulWrapedLen		[IN] ���ݳ���
	*	phKey			[OUT] ���ػỰ��Կ���
	*/
	typedef ULONG (DEVAPI *PSKF_ImportSessionKey ) (HCONTAINER hContainer, ULONG ulAlgId,BYTE *pbWrapedData,ULONG ulWrapedLen,HANDLE *phKey);
	PSKF_ImportSessionKey m_PSKF_ImportSessionKey;


	/*
	*	�������ĶԳ���Կ��������Կ���
	*	hContainer		[IN] �������
	*	pbKey			[IN] ָ��Ự��Կֵ�Ļ�����
	*	ulAlgID			[IN] �Ự��Կ���㷨��ʶ
	*	phKey			[OUT] ���ػỰ��Կ���
	*/
	typedef ULONG (DEVAPI *PSKF_SetSymmKey ) (DEVHANDLE hDev, BYTE* pbKey, ULONG ulAlgID, HANDLE* phKey);
	PSKF_SetSymmKey m_PSKF_SetSymmKey;

	/*
	*	���ݼ��ܳ�ʼ�����������ݼ��ܵ��㷨��ز�����
	*	hKey			[IN] ������Կ���
	*	EncryptParam	[IN] ���������㷨��ز������㷨��ʶ�š���Կ���ȡ���ʼ��������ʼ�������ȡ���䷽��������ģʽ������ֵ��λ����
	*/
	typedef ULONG (DEVAPI *PSKF_EncryptInit ) (HANDLE hKey, BLOCKCIPHERPARAM EncryptParam);
	PSKF_EncryptInit m_PSKF_EncryptInit;

	/*
	*	��һ�������ݵļ��ܲ�����
	��ָ��������Կ��ָ�����ݽ��м��ܣ������ܵ�����ֻ����һ�����飬���ܺ�����ı��浽ָ���Ļ������С�
	SKF_Encryptֻ�Ե����������ݽ��м��ܣ��ڵ���SKF_Encrypt֮ǰ���������SKF_EncryptInit��ʼ�����ܲ�����
	SKF_Encypt�ȼ����ȵ���SKF_EncryptUpdate�ٵ���SKF_EncryptFinal��
	*	hKey			[IN] ������Կ���
	*	pbData			[IN] ����������
	*	ulDataLen		[IN] ���������ݳ���
	*	pbEncryptedData [OUT] ���ܺ�����ݻ�����ָ��
	*	pulEncryptedLen [IN,OUT] ���룬�����Ļ�������С����������ؼ��ܺ������
	����
	*	�ɹ�: SAR_OK
	*	ʧ��: SAR_FAIL SAR_MEMORYERR SAR_UNKNOWNERR  SAR_INVALIDPARAMERR SAR_BUFFER_TOO_SMALL   
	*/
	typedef ULONG (DEVAPI *PSKF_Encrypt) (HANDLE hKey, BYTE * pbData, ULONG ulDataLen, BYTE *pbEncryptedData, ULONG *pulEncryptedLen);
	PSKF_Encrypt m_PSKF_Encrypt;


	/*
	*	����������ݵļ��ܲ�����
	��ָ��������Կ��ָ�����ݽ��м��ܣ������ܵ����ݰ���������飬���ܺ�����ı��浽ָ���Ļ������С�
	SKF_EncryptUpdate�Զ���������ݽ��м��ܣ��ڵ���SKF_EncryptUpdate֮ǰ���������SKF_EncryptInit��ʼ�����ܲ�����
	�ڵ���SKF_EncryptUpdate֮�󣬱������SKF_EncryptFinal�������ܲ�����
	*	hKey			[IN] ������Կ���
	*	pbData			[IN] ����������
	*	ulDataLen		[IN] ���������ݳ���
	*	pbEncryptedData [OUT] ���ܺ�����ݻ�����ָ��
	*	pulEncryptedLen [OUT] ���ؼ��ܺ�����ݳ���
	*/
	typedef ULONG (DEVAPI *PSKF_EncryptUpdate) (HANDLE hKey, BYTE * pbData, ULONG ulDataLen, BYTE *pbEncryptedData, ULONG *pulEncryptedLen);
	PSKF_EncryptUpdate m_PSKF_EncryptUpdate;

	/*
	*	��������������ݵļ��ܣ�����ʣ����ܽ����
	�ȵ���SKF_EncryptInit��ʼ�����ܲ�����
	�ٵ���SKF_EncryptUpdate�Զ���������ݽ��м��ܣ�
	������SKF_EncryptFinal��������������ݵļ��ܡ�
	*	hKey			[IN] ������Կ���
	*	pbEncryptedData [OUT] ���ܽ���Ļ�����
	*	pulEncryptedLen [OUT] ���ܽ���ĳ���
	*/
	typedef ULONG (DEVAPI *PSKF_EncryptFinal ) (HANDLE hKey, BYTE *pbEncryptedData, ULONG *ulEncryptedDataLen );
	PSKF_EncryptFinal m_PSKF_EncryptFinal;

	/*
	*	���ݽ��ܳ�ʼ�������ý�����Կ��ز�����
	����SKF_DecryptInit֮�󣬿��Ե���SKF_Decrypt�Ե����������ݽ��н��ܣ�
	Ҳ���Զ�ε���SKF_DecryptUpdate֮���ٵ���SKF_DecryptFinal��ɶԶ���������ݵĽ��ܡ�
	*	hKey [IN] ������Կ���
	*	DecryptParam [IN] ���������㷨��ز������㷨��ʶ�š���Կ���ȡ���ʼ��������ʼ�������ȡ���䷽��������ģʽ������ֵ��λ����
	*/
	typedef ULONG (DEVAPI *PSKF_DecryptInit ) (HANDLE hKey, BLOCKCIPHERPARAM DecryptParam);
	PSKF_DecryptInit m_PSKF_DecryptInit;

	/*
	*	�����������ݵĽ��ܲ���
	��ָ��������Կ��ָ�����ݽ��н��ܣ������ܵ�����ֻ����һ�����飬���ܺ�����ı��浽ָ���Ļ�������
	SKF_Decryptֻ�Ե����������ݽ��н��ܣ��ڵ���SKF_Decrypt֮ǰ���������SKF_DecryptInit��ʼ�����ܲ���
	SKF_Decypt�ȼ����ȵ���SKF_DecryptUpdate�ٵ���SKF_DecryptFinal
	*	hKey			[IN] ������Կ���
	*	pbEncryptedData [IN] ����������
	*	ulEncryptedLen	[IN] ���������ݳ���
	*	pbData			[OUT] ָ����ܺ�����ݻ�����ָ�룬��ΪNULLʱ�ɻ�ý��ܺ�����ݳ���
	*	pulDataLen		[IN��OUT] ���ؽ��ܺ�����ݳ���
	*/
	typedef ULONG (DEVAPI *PSKF_Decrypt) (HANDLE hKey, BYTE * pbEncryptedData, ULONG ulEncryptedLen, BYTE * pbData, ULONG * pulDataLen);
	PSKF_Decrypt m_PSKF_Decrypt;

	/*
	*	����������ݵĽ��ܲ�����
	��ָ��������Կ��ָ�����ݽ��н��ܣ������ܵ����ݰ���������飬���ܺ�����ı��浽ָ���Ļ������С�
	SKF_DecryptUpdate�Զ���������ݽ��н��ܣ��ڵ���SKF_DecryptUpdate֮ǰ���������SKF_DecryptInit��ʼ�����ܲ�����
	�ڵ���SKF_DecryptUpdate֮�󣬱������SKF_DecryptFinal�������ܲ�����
	*	hKey			[IN] ������Կ���
	*	pbEncryptedData [IN] ����������
	*	ulEncryptedLen	[IN] ���������ݳ���
	*	pbData			[OUT] ָ����ܺ�����ݻ�����ָ��
	*	pulDataLen		[IN��OUT] ���ؽ��ܺ�����ݳ���
	*/
	typedef ULONG (DEVAPI *PSKF_DecryptUpdate) (HANDLE hKey, BYTE * pbEncryptedData, ULONG ulEncryptedLen, BYTE * pbData, ULONG * pulDataLen);
	PSKF_DecryptUpdate m_PSKF_DecryptUpdate;

	/*
	*	��������������ݵĽ��ܡ�
	*	hKey				[IN] ������Կ���
	*	pbPlainText			[OUT] ָ����ܽ���Ļ�����������˲���ΪNULLʱ����pulPlainTextLen���ؽ��ܽ���ĳ���
	*	pulDecyptedDataLen	[IN��OUT] ����ʱ��ʾpbPlainText�������ĳ��ȣ����ؽ��ܽ���ĳ��� 
	*/
	typedef ULONG (DEVAPI *PSKF_DecryptFinal ) (HANDLE hKey, BYTE *pbDecryptedData, ULONG *pulDecryptedDataLen);
	PSKF_DecryptFinal m_PSKF_DecryptFinal;

	/*
	*	��ʼ����Ϣ�Ӵռ��������ָ��������Ϣ�Ӵյ��㷨��
	*	hDev			[IN] �����豸ʱ���ص��豸���
	*	ulAlgID			[IN] �Ӵ��㷨��ʶ
	*	phHash			[OUT] �Ӵն�����
	*/
	typedef ULONG (DEVAPI *PSKF_DigestInit) (DEVHANDLE hDev, ULONG ulAlgID,  ECCPUBLICKEYBLOB *pPubKey, unsigned char *pucID, ULONG ulIDLen, HANDLE *phHash);
	PSKF_DigestInit m_PSKF_DigestInit;

	/*
	*	�Ե�һ�������Ϣ�����Ӵռ��㡣
	*	hHash			[IN] �Ӵն�����
	*	pbData			[IN] ָ����Ϣ���ݵĻ�����
	*	ulDataLen		[IN] ��Ϣ���ݵĳ���
	*	pbHashData		[OUT] �Ӵ����ݻ�����ָ�룬���˲���ΪNULLʱ����pulHashLen�����Ӵս���ĳ���
	*	pulHashLen		[IN��OUT] ����ʱ��ʾpbHashData�������ĳ��ȣ������Ӵս���ĳ���
	*/
	typedef ULONG (DEVAPI *PSKF_Digest ) (HANDLE hHash, BYTE *pbData, ULONG ulDataLen, BYTE *pbHashData, ULONG *pulHashLen);
	PSKF_Digest m_PSKF_Digest;
	/*
	*	�Զ���������Ϣ�����Ӵռ��㡣
	*	hHash			[IN] �Ӵն�����
	*	pbPart			[IN] ָ����Ϣ���ݵĻ�����
	*	ulPartLen		[IN] ��Ϣ���ݵĳ���
	*/
	typedef ULONG (DEVAPI *PSKF_DigestUpdate ) (HANDLE hHash, BYTE *pbData, ULONG  ulDataLen);
	PSKF_DigestUpdate m_PSKF_DigestUpdate;
	/*
	*	�������������Ϣ���Ӵռ�����������Ӵձ��浽ָ���Ļ�������
	*	hHash			[IN] ��ϣ������
	*	pHashData		[OUT] ���ص��Ӵ����ݻ�����ָ�룬����˲���NULLʱ����pulHashLen�����Ӵս���ĳ���
	*	pulHashLen		[IN��OUT] ����ʱ��ʾ�Ӵս���ĳ��ȣ������Ӵ����ݵĳ���
	*/
	typedef ULONG (DEVAPI *PSKF_DigestFinal ) (HANDLE hHash, BYTE *pHashData, ULONG  *pulHashLen);
	PSKF_DigestFinal m_PSKF_DigestFinal;

	/*
	*	��ʼ����Ϣ��֤�������������ü�����Ϣ��֤�����Կ��������������Ϣ��֤������
	*	hKey			[IN] ������Ϣ��֤�����Կ���
	*	MacParam		[IN] ��Ϣ��֤������ز�����������ʼ��������ʼ�������ȡ���䷽����
	*	phMac			[OUT] ��Ϣ��֤�������
	*/
	typedef ULONG (DEVAPI *PSKF_MacInit ) (HANDLE hKey, BLOCKCIPHERPARAM* pMacParam, HANDLE *phMac);
	PSKF_MacInit m_PSKF_MacInit;

	/*
	*	SKF_Mac���㵥һ�������ݵ���Ϣ��֤�롣
	*	hMac			[IN] ��Ϣ��֤����
	*	pbData			[IN] ָ����������ݵĻ�����
	*	ulDataLen		[IN] ���������ݵĳ���
	*	pbMacData		[OUT] ָ�������Mac���������˲���ΪNULLʱ����pulMacLen���ؼ����Mac����ĳ���
	*	pulMacLen		[IN��OUT] ����ʱ��ʾpbMacData�������ĳ��ȣ����ؼ���Mac����ĳ���
	*/
	typedef ULONG (DEVAPI *PSKF_Mac) (HANDLE hMac, BYTE* pbData, ULONG ulDataLen, BYTE *pbMacData, ULONG *pulMacLen);
	PSKF_Mac m_PSKF_Mac;
	/*
	*	�������������ݵ���Ϣ��֤�롣
	*	hMac			[IN] ��Ϣ��֤����
	*	pbData			[IN] ָ����������ݵĻ�����
	*	plDataLen		[IN] ���������ݵĳ���
	*/
	typedef ULONG (DEVAPI *PSKF_MacUpdate) (HANDLE hMac, BYTE * pbData, ULONG ulDataLen);
	PSKF_MacUpdate m_PSKF_MacUpdate;
	/*
	*	��������������ݵ���Ϣ��֤��������
	*	hMac			[IN] ��Ϣ��֤����
	*	pbMacData		[OUT] ָ����Ϣ��֤��Ļ����������˲���ΪNULLʱ����pulMacDataLen������Ϣ��֤�뷵�صĳ���
	*	pulMacDataLen	[OUT] ����ʱ��ʾ��Ϣ��֤�뻺��������󳤶ȣ�������Ϣ��֤��ĳ���
	*/
	typedef ULONG (DEVAPI *PSKF_MacFinal ) (HANDLE hMac, BYTE *pbMacData, ULONG *pulMacDataLen);
	PSKF_MacFinal m_PSKF_MacFinal;
	/*
	*	�رջỰ��Կ���Ӵա���Ϣ��֤������
	*	hHandle			[IN] Ҫ�رյĶ�����
	*/
	typedef ULONG (DEVAPI *PSKF_CloseHandle) (HANDLE hHandle);
	PSKF_CloseHandle m_PSKF_CloseHandle;


	// 1
	typedef DWORD (DEVAPI *PSKF_RSAPubKeyEncrypt)(IN DEVHANDLE hDev, IN RSAPUBLICKEYBLOB *pRSAPubKeyBlob,
		IN BYTE *pbInData, IN DWORD dwInDataLen, 
		OUT BYTE *pbOutData, IN OUT DWORD *pdwOutDataLen);
	PSKF_RSAPubKeyEncrypt m_PSKF_RSAPubKeyEncrypt;
	// 2
	typedef DWORD (DEVAPI *PSKF_RSAPriKeyDecrypt)(IN HCONTAINER hContainer, 
		IN BYTE *pbInData, IN DWORD dwInDataLen, 
		OUT BYTE *pbOutData, IN OUT DWORD *pdwOutDataLen);
	PSKF_RSAPriKeyDecrypt m_PSKF_RSAPriKeyDecrypt;

	typedef ULONG (DEVAPI *PSKF_ECCDecrypt)(IN HCONTAINER hContainer, IN PECCCIPHERBLOB pCipherText, 
		OUT BYTE *pbPlainText, IN OUT ULONG *pulPlainTextLen);
	PSKF_ECCDecrypt m_PSKF_ECCDecrypt;

};
