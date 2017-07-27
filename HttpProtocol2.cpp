#include "StdAfx.h"
#include "HttpProtocol2.h"
#include "httpserver/HttpProtocol.h"
#include "CAPCManage.h"
#include "ParserPostMsg.h"
#include "CAPCManageDlg.h"
#include "EnDecodeClass.h"



/// �궨��
#define DATA_BUFSIZE 65536


/// ȫ�ֺ�������
CString g_szRevData;
extern CCAPCManageDlg* g_pCADlg;

// ��������ʱ�������ת��
extern char *week[];

// ��������ʱ����·�ת��
extern char *month[];



///////////////////////////////////////////////////////////////////////
//
// ������       : InitWinsock
// ��������     : ��ʼ��WINSOCK
// ����ֵ       : void
//
///////////////////////////////////////////////////////////////////////
void InitWinsock()
{
	// ��ʼ��WINSOCK
	WSADATA wsd;
	if( WSAStartup(MAKEWORD(2, 2), &wsd) != 0)
		return ;

}

///////////////////////////////////////////////////////////////////////
//
// ������       : BindServerOverlapped
// ��������     : �󶨶˿ڣ�������һ�� Overlapped ��Listen Socket
// ����         : int nPort
// ����ֵ       : SOCKET
//
///////////////////////////////////////////////////////////////////////
SOCKET BindServerOverlapped(int nPort)
{
	// ����socket
	SOCKET sServer = WSASocket(AF_INET, SOCK_STREAM, 0, NULL, 0, WSA_FLAG_OVERLAPPED);

	// �󶨶˿�
	struct sockaddr_in servAddr;
	servAddr.sin_family = AF_INET;
	servAddr.sin_port = htons(nPort);
	servAddr.sin_addr.s_addr = htonl(INADDR_ANY);

	if(bind(sServer, (struct sockaddr *)&servAddr, sizeof(servAddr)) < 0)
	{
		LOG_ERROR("bind Failed!");
		return NULL;
	}

	// ���ü�������Ϊ200
	if(listen(sServer, 200) != 0)
	{
		LOG_ERROR("listen Failed!");
		return NULL;
	}
	return sServer;
}


/// �ṹ�嶨��
typedef struct
{
	OVERLAPPED Overlapped;
	WSABUF DataBuf;
	CHAR Buffer[DATA_BUFSIZE];
} PER_IO_OPERATION_DATA, * LPPER_IO_OPERATION_DATA;


typedef struct
{
	SOCKET Socket;
} PER_HANDLE_DATA, * LPPER_HANDLE_DATA;


void CHttpProtocol2::SendLoginResp(PREQUEST pReq,std::string szResp)
{

	char msg[12048] = " ";
	char curTime[50] = " ";
	GetCurentTime((char*)curTime);

	// ȡ���ļ���last-modifiedʱ��
	char last_modified[60] = " ";
	GetLastModified(pReq->hFile, (char*)last_modified);	
	// ȡ���ļ�������
	char ContenType[50] = " ";
	GetContenType(pReq, (char*)ContenType);
	//szResp="{\"resultCode\":1,\"resultMsg\":\"CA��֤ʧ�ܣ�\"}";

	CEnDecodeClass::Gbk2Utf(szResp);
	DWORD length = szResp.length();


	sprintf((char*)msg, "HTTP/1.1 200 OK\r\n%s\r\n%s\r\nContent-Type: %s\r\nContent-Length: %d\r\n%s\r\n\r\n%s\r\n",
		"Server: Apache-Coyote/1.1",				// Date
		"Access-Control-Allow-Origin: *",       // Server
		"application/json;charset=UTF-8",				// Content-Type
		length,					// Content-length
		curTime,
		szResp.c_str());			// Last-Modified

	// ������Ӧ

	int sdf = strlen(msg);

	send(pReq->Socket, msg, strlen(msg), 0);	

	LOG_INFO(szResp.c_str());
}

DWORD WINAPI ProcessIO(LPVOID lpParam)
{
	HANDLE CompletionPort = (HANDLE)lpParam;
	DWORD BytesTransferred;
	LPPER_HANDLE_DATA PerHandleData;
	LPPER_IO_OPERATION_DATA PerIoData;

	while(true)
	{

		if(0 == GetQueuedCompletionStatus(CompletionPort, &BytesTransferred, (LPDWORD)&PerHandleData, (LPOVERLAPPED*)&PerIoData, INFINITE))
		{
			if( (GetLastError() == WAIT_TIMEOUT) || (GetLastError() == ERROR_NETNAME_DELETED) )
			{
//				cout << "closing socket" << PerHandleData->Socket << endl;

				closesocket(PerHandleData->Socket);

				delete PerIoData;
				delete PerHandleData;
				continue;
			}
			else
			{
				LOG_ERROR("GetQueuedCompletionStatus failed!");
			}
			return 0;
		}

		// ˵���ͻ����Ѿ��˳�
		if(BytesTransferred == 0)
		{
		//	cout << "closing socket" << PerHandleData->Socket << endl;
			closesocket(PerHandleData->Socket);
			delete PerIoData;
			delete PerHandleData;
			continue;
		}


		// ȡ�����ݲ�����
	//	cout << PerHandleData->Socket << "���͹�������Ϣ��" << PerIoData->Buffer << endl;
		CString strData = CString(PerIoData->Buffer,BytesTransferred);
		if (0 == strData.Find("POST /caclient"))
		{
			g_szRevData = strData;
		}
		else
		{
			g_szRevData += strData;
		}

		if (DATA_BUFSIZE != BytesTransferred)
		{
			int nRet =  g_pCADlg->m_parsermsg.JustMsgFormat(g_szRevData);
			if (0 == nRet)
			{
				PREQUEST pReq = new REQUEST;
				pReq->pHttpProtocol = g_pCADlg->m_pHttpProtocol;
				pReq->Socket = PerHandleData->Socket;

				// ����request��Ϣ
				g_pCADlg->m_parsermsg.Analyze(pReq,(LPBYTE)g_szRevData.GetBuffer());
				g_szRevData.Empty();
			}
			else if (-2 == nRet)
			{
				g_szRevData.Empty();
			}
		}

		

		// ������ socket Ͷ��WSARecv����
		DWORD Flags = 0;
		DWORD dwRecv = 0;
		ZeroMemory(PerIoData, sizeof(PER_IO_OPERATION_DATA));
		PerIoData->DataBuf.buf = PerIoData->Buffer;
		PerIoData->DataBuf.len = DATA_BUFSIZE;
		WSARecv(PerHandleData->Socket, &PerIoData->DataBuf, 1, &dwRecv, &Flags, &PerIoData->Overlapped, NULL); 
	}

	return 0;
}



bool CHttpProtocol2::StartHttpSrv()
{
	InitWinsock();

	m_CompletionPort = CreateIoCompletionPort(INVALID_HANDLE_VALUE, NULL, 0, 0);

	// ����ϵͳ��CPU�������������߳�
	SYSTEM_INFO SystemInfo;
	GetSystemInfo(&SystemInfo);

	//for(int i = 0; i < SystemInfo.dwNumberOfProcessors * 2; i++)
	//{
	//	// if(hProcessIO)
	//}

	HANDLE hProcessIO = CreateThread(NULL, 0, ProcessIO, m_CompletionPort, 0, NULL);

	// ��������SOCKET
	m_listenSocket = BindServerOverlapped(m_nPort);

	CWinThread* m_pListenThread = AfxBeginThread(ListenThread, this);
	if (!m_pListenThread)
	{
		// �̴߳���ʧ��
		LOG_ERROR("Could not create listening thread" );
		closesocket(m_listenSocket);	// �Ͽ�����
		return false;
	}


	return true;
}

UINT CHttpProtocol2::ListenThread(LPVOID param)
{
	CHttpProtocol2* pHttpPor2 = (CHttpProtocol2*)param;
	SOCKET sClient;
	LPPER_HANDLE_DATA PerHandleData;
	LPPER_IO_OPERATION_DATA PerIoData;
	while(true)
	{
		// �ȴ��ͻ��˽���
		//sClient = WSAAccept(sListen, NULL, NULL, NULL, 0);
		sClient = accept(pHttpPor2->m_listenSocket, 0, 0);
		//���ͻ�����
		int nSendBuf=1024;//����Ϊ32K
		//setsockopt(sClient,SOL_SOCKET,SO_SNDBUF,(const char*)&nSendBuf,sizeof(int));

		//cout << "Socket " << sClient << "���ӽ���" << endl;

		PerHandleData = new PER_HANDLE_DATA();
		PerHandleData->Socket = sClient;

		// ������Ŀͻ��˺���ɶ˿���ϵ����
		CreateIoCompletionPort((HANDLE)sClient, pHttpPor2->m_CompletionPort, (DWORD)PerHandleData, 0);

		// ����һ��Overlapped����ʹ�����Overlapped�ṹ��socketͶ�ݲ���
		PerIoData = new PER_IO_OPERATION_DATA();

		ZeroMemory(PerIoData, sizeof(PER_IO_OPERATION_DATA));
		PerIoData->DataBuf.buf = PerIoData->Buffer;
		PerIoData->DataBuf.len = DATA_BUFSIZE;

		// Ͷ��һ��WSARecv����
		DWORD Flags = 0;
		DWORD dwRecv = 0;
		WSARecv(sClient, &PerIoData->DataBuf, 1, &dwRecv, &Flags, &PerIoData->Overlapped, NULL);
	}

	DWORD dwByteTrans;
	PostQueuedCompletionStatus(pHttpPor2->m_CompletionPort, dwByteTrans, 0, 0);
	closesocket(pHttpPor2->m_listenSocket);
}

CHttpProtocol2::CHttpProtocol2(void)
{
}

CHttpProtocol2::~CHttpProtocol2(void)
{
}

// �����ʱ��
void CHttpProtocol2::GetCurentTime(LPSTR lpszString)
{  
	// �����ʱ��
	SYSTEMTIME st;
	GetLocalTime(&st);
	// ʱ���ʽ��
	wsprintf(lpszString, "%s %02d %s %d %02d:%02d:%02d GMT",week[st.wDayOfWeek], st.wDay,month[st.wMonth-1],
		st.wYear, st.wHour, st.wMinute, st.wSecond);
}

bool CHttpProtocol2::GetLastModified(HANDLE hFile, LPSTR lpszString)
{
	// ����ļ���last-modified ʱ��
	FILETIME ftCreate, ftAccess, ftWrite;
	SYSTEMTIME stCreate;
	FILETIME ftime;	
	// ����ļ���last-modified��UTCʱ��
	if (!GetFileTime(hFile, &ftCreate, &ftAccess, &ftWrite))   
		return false;
	FileTimeToLocalFileTime(&ftWrite,&ftime);
	// UTCʱ��ת���ɱ���ʱ��
	FileTimeToSystemTime(&ftime, &stCreate);	
	// ʱ���ʽ��
	wsprintf(lpszString, "%s %02d %s %d %02d:%02d:%02d GMT", week[stCreate.wDayOfWeek],
		stCreate.wDay, month[stCreate.wMonth-1], stCreate.wYear, stCreate.wHour,
		stCreate.wMinute, stCreate.wSecond);
	return TRUE;
}

bool CHttpProtocol2::GetContenType(PREQUEST pReq, LPSTR type)
{   
	wsprintf(type,"%s","wwwserver/isapi");
	return TRUE;

	//// ȡ���ļ�������
	//CString cpToken;
	//cpToken = strstr(pReq->szFileName, ".");
	//strcpy(pReq->postfix, cpToken);
	//// �����������ļ����Ͷ�Ӧ��content-type
	//map<CString, char *>::iterator it = m_typeMap.find(pReq->postfix);
	//if(it != m_typeMap.end()) 	
	//{
	//	wsprintf(type,"%s",(*it).second);
	//}
	//return TRUE;
}

void CHttpProtocol2::StopHttpSrv()
{


	LOG_INFO("Server Stopped");

}