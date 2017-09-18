
// CAPCManageDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "CAPCManage.h"
#include "CAPCManageDlg.h"
#include <string>

#include "TestCADlg2.h"
#include "TestUKeyDlg.h"
#include "../soapSender/WebService.h"
#include "PinDlg.h"
#include "define.h"
#include <Setupapi.h>
#include "XMLDOMParser.h"

#include "CSPCertificate.h"
#include "ParserPostMsg.h"
#include "Base64.h"
#include "EnDecodeClass.h"

#define  TEST_MODE 0
#define  RUN_MODE 1


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CString g_strExePath;
CReadUKey* g_readUKey = NULL;
static int g_i = 2; 
std::string g_szbase64Cert;
CString g_strTokenId="1234";//��ʱֵ
CCAPCManageDlg* g_pCADlg = NULL;

// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CCAPCManageDlg �Ի���




CCAPCManageDlg::CCAPCManageDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCAPCManageDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_nSelect = -1;
	m_pHttpProtocol = NULL;
	m_bStart = FALSE;
	m_dwReceived = 0;
	m_dwTransferred = 0;

	m_pReq = NULL;
	m_nMode = 1;
	g_pCADlg = this;
}

void CCAPCManageDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_listCert);
}

BEGIN_MESSAGE_MAP(CCAPCManageDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON1, &CCAPCManageDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CCAPCManageDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BTN_LOGIN, &CCAPCManageDlg::OnBnClickedBtnLogin)
	ON_BN_CLICKED(IDC_BTN_REQUEST, &CCAPCManageDlg::OnBnClickedBtnRequest)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST1, &CCAPCManageDlg::OnLvnItemchangedList1)
	ON_WM_DESTROY()
	ON_MESSAGE(LOG_MSG, AddLog)
	ON_MESSAGE(DATA_MSG, ShowData)
	ON_MESSAGE(LOGIN_MSG, OnLogin)
	ON_WM_NCPAINT()
	ON_WM_TIMER()
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDCANCEL, &CCAPCManageDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDOK, &CCAPCManageDlg::OnBnClickedOk)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST1, &CCAPCManageDlg::OnNMDblclkList1)
	ON_BN_CLICKED(IDC_BUTTON3, &CCAPCManageDlg::OnBnClickedButton3)
END_MESSAGE_MAP()


// CCAPCManageDlg ��Ϣ�������

BOOL CCAPCManageDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	LOG_INFO(" CCAPCManageDlg::OnInitDialog");

	
	

	GetExePath();
	std::string szConfig = g_strExePath+"\\config\\config.ini";

	//�õ��������ĵ�ַ�Ͷ˿�
	//soapSender::GetServerInfo(szConfig);

	//�õ�����ģʽ�������֣�0������ģʽ��1����ʽģʽ
	m_nMode = GetPrivateProfileIntA("Common","mode", m_nMode,szConfig.c_str());
	
	


	if(RUN_MODE ==m_nMode)
	{
		GetDlgItem(IDC_BTN_REQUEST)->ShowWindow(SW_HIDE);
		ModifyStyleEx(WS_EX_APPWINDOW,WS_EX_TOOLWINDOW);
		//GetDlgItem(IDOK)->ShowWindow(SW_HIDE);
		//GetDlgItem(IDCANCEL)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_BUTTON1)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_BUTTON2)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_BUTTON3)->ShowWindow(SW_HIDE);
	}


	//��regwin.xml�ļ�
	CXMLDOMParser xmlPas;
	std::string szRWI = g_strExePath+"\\config\\regwin.xml";
	xmlPas.ReadRegWinXml(szRWI,m_vecRWI);

	

	initList();

	StartServer();

	GetDlgItem(IDC_BTN_LOGIN)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON1)->ShowWindow(SW_HIDE);
	GetDlgItem(IDC_BUTTON2)->ShowWindow(SW_HIDE);


	/*Base64 b64;
	string sdf = b64.base64_decode("5rGf6IuP55yB55S15a2Q5ZWG5Yqh5pyN5Yqh5Lit5b+D5pyJ6ZmQ6LSj5Lu75YWs5Y+45a6J5YWo5LqL5Lia6YOo");
	CEnDecodeClass::Utf2Gbk(sdf);*/


	//analysisCert();

	//CParserPostMsg dsdl;
	//std::string szData = "weafeaf";
	//dsdl.WriteFileInfo("D:\\testfile\\vv.cer",szData);

	//

//	GetDlgItem(IDC_BUTTON2)->ShowWindow(SW_HIDE);

	//std::string szTmp;
	//m_parsermsg.ReadFileInfo("D:\\test2.log", szTmp);
	//CEnDecodeClass::Utf2Gbk(szTmp);

	

	
	

	//CollectUSBInfo();

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

BOOL CCAPCManageDlg::StartServer()
{
	std::string szConfig = g_strExePath+"\\config\\config.ini";
	int nLocPort = 0;
	nLocPort = GetPrivateProfileIntA("Common","LocalServerPort", nLocPort,szConfig.c_str());

	m_pHttpProtocol = new CHttpProtocol2;
	m_pHttpProtocol->m_strRootDir = "";
	m_pHttpProtocol->m_nPort = nLocPort;
	m_pHttpProtocol->m_hwndDlg = m_hWnd;

	if (m_pHttpProtocol->StartHttpSrv())
	{
		m_bStart = TRUE;
		return TRUE;
	}
	else
	{
		if(m_pHttpProtocol)
		{
			delete m_pHttpProtocol;
			m_pHttpProtocol = NULL;
		}

		return FALSE;
	}
}

void CCAPCManageDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CCAPCManageDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
		
	}
	else
	{
		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CCAPCManageDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

typedef std::string VNCString ;
void CCAPCManageDlg::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������	int iRet;
	CTestCADlg2 dlg;
	dlg.DoModal();
	

	
}

void CCAPCManageDlg::OnBnClickedButton2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CTestUKeyDlg dlg;
	dlg.DoModal();
	
}

void CCAPCManageDlg::GetExePath()
{
	char szPath[MAX_PATH] = {0};
	GetModuleFileName(NULL,   szPath,   MAX_PATH);
	CString strExePath = szPath;
	int nPos = strExePath.ReverseFind('\\');
	g_strExePath = strExePath.Left(nPos);

}
void CCAPCManageDlg::OnBnClickedBtnLogin()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_nSelect = m_listCert.GetSelectionMark();
	if (m_nSelect < 0)
	{
		return;
	}

	m_szRandom.clear();

	if (!GetGenRandomFromServer(m_szRandom))
	{
		AfxMessageBox("�ӷ�������������ʧ��");
		GetDlgItem(IDC_BTN_REQUEST)->EnableWindow(TRUE);
		return;
	}

	//test
	//m_szRandom ="<name><first>Bill</first><last>Gates</last></name>";

	ReadCertInfo& tagRCF =  m_vecCert[m_nSelect];
	BYTE* pbSignature = NULL;
	ULONG ulSignLen = 0;
	g_readUKey = (CReadUKey*)tagRCF.m_pReadUkey;
	g_readUKey->m_hDev = tagRCF.m_hDev;
	g_readUKey->m_hApp = tagRCF.m_hApp;
	g_readUKey->m_hAContainer = tagRCF.m_hAContainer;

	BYTE* pbHashData = NULL;
	ULONG ulHashLen=0;

	CPinDlg dlg;
	if (IDOK == dlg.DoModal())
	{
		//�õ������hashֵ
		ULONG rv = 0;
		BYTE pbAllData[36]={0};

		

		//�õ�֤������
		CCSPCertificate cspCert;
		cspCert._DecodeX509Cert(tagRCF.m_pCert, tagRCF.m_ulCertLen);
		cspCert.get_KeyType(&(g_readUKey->m_ulType));

		if (g_readUKey->m_ulType == CERT_KEY_ALG_RSA)
		{
			ULONG nType=0;
			cspCert.get_KeyHash(&nType);
			//rv = g_readUKey->DigestEx(m_szRandom,tagRCF.m_hDev,pbHashData,&ulHashLen,nType);
			if (SGD_SM3 == nType)
			{
				rv = g_readUKey->DigestEx(m_szRandom,tagRCF.m_hDev,pbHashData,&ulHashLen,nType);
				rv = g_readUKey->RSASignDataEx2(tagRCF.m_hAContainer,pbHashData,ulHashLen, pbSignature, &ulSignLen);
			}
			else if (SGD_SHA256 == nType)
			{
				rv = g_readUKey->DigestEx2(m_szRandom,tagRCF.m_hDev,pbHashData,&ulHashLen,nType);
				rv = g_readUKey->RSASignDataEx2(tagRCF.m_hAContainer,pbHashData,ulHashLen, pbSignature, &ulSignLen);
			}
			else
			{
				rv = g_readUKey->DigestEx(m_szRandom,tagRCF.m_hDev,pbHashData,&ulHashLen,nType);
				m_parsermsg.SetAsn1Value(pbAllData);
				memcpy(pbAllData+15,pbHashData,ulHashLen);
				rv = g_readUKey->RSASignDataEx2(tagRCF.m_hAContainer,pbAllData,35, pbSignature, &ulSignLen);
			}
		}
		else
		{
			rv = g_readUKey->DigestEx(m_szRandom,tagRCF.m_hDev,pbHashData,&ulHashLen,SGD_SM3);
			rv = g_readUKey->ECCSignDataEx2(tagRCF.m_hAContainer,pbHashData,ulHashLen, pbSignature, &ulSignLen);
			
			
			
	/*		Base64 b64;
			string sTemp = b64.base64_encode(pbSignature,ulSignLen);
			free(pbSignature);
			pbSignature = NULL;
			ulSignLen = 0;

			rv = g_readUKey->ECCSignDataEx2(tagRCF.m_hAContainer,pbHashData,ulHashLen, pbSignature, &ulSignLen);

			string sTemp2 = b64.base64_encode(pbSignature,ulSignLen);*/


		}

		
		
		
		if (rv)
		{
			if (pbSignature!= NULL)
			{
				free(pbSignature);
				pbSignature = NULL;
			}
			//��ӡ���������֤������
			char* szBuf = new char[tagRCF.m_ulCertLen*2];
			memset(szBuf, 0, tagRCF.m_ulCertLen*2);
			int nbase64 = Base64Encode(szBuf,tagRCF.m_pCert,tagRCF.m_ulCertLen);
			LOG_INFO("�����������ǩ��ʧ�ܣ� �����=%s,֤������=%s", m_szRandom.c_str(),szBuf);
			delete szBuf;


			AfxMessageBox("�����������ǩ��ʧ�ܣ�");
			return;
		}

		////������ǩ
		//ECCPUBLICKEYBLOB pEccSignKey = {0};
		//ULONG ulEccPubKeyLen = sizeof(ECCPUBLICKEYBLOB);


		//rv = g_readUKey->m_PSKF_ExportPublicKey(g_readUKey->m_hAContainer,TRUE,(unsigned char *)&pEccSignKey,&ulEccPubKeyLen);


		//ECCSIGNATUREBLOB signdata;
		//memset(&signdata,0,sizeof(ECCSIGNATUREBLOB));
		//memcpy(signdata.r+32,pbSignature,32);
		//memcpy(signdata.s+32,pbSignature+32,32);

		//rv = g_readUKey->m_PSKF_ECCVerify(g_readUKey->m_hDev,&pEccSignKey,pbHashData,ulHashLen,&signdata);
		//if(rv)
		//{
		//	return ;
		//}


		////������֤ǩ��
	/*	RSAPUBLICKEYBLOB pPubKey;
		ULONG ulPubKeyLen = 0;
		ulPubKeyLen = sizeof(pPubKey);
		rv = g_readUKey->m_PSKF_ExportPublicKey(g_readUKey->m_hAContainer,TRUE,(unsigned char *)&pPubKey,&ulPubKeyLen);
		if(rv != SAR_OK)
		{
			return ;
		}

		rv = g_readUKey->m_PSKF_RSAVerify(g_readUKey->m_hDev,&pPubKey,(BYTE*)m_szRandom.c_str(),m_szRandom.length(),pbSignature,ulSignLen);
		if(rv)
		{
			return ;
		}*/


		//hashֵתΪbase64
		Base64 b64;
		string sHashTemp = b64.base64_encode(pbHashData,ulHashLen);
		free(pbHashData);
		pbHashData = NULL;


		//ǩ��ֵתΪbase64
		string sTemp = b64.base64_encode(pbSignature,ulSignLen);
		free(pbSignature);
		pbSignature = NULL;

		//unsigned char *sfbuf = new unsigned char[500];
		//memset(sfbuf, 0, 500);

		//int nesf = Base64Decode(sfbuf,sTemp.c_str());

		

		//֤��תΪbase64
		string szCert = b64.base64_encode(tagRCF.m_pCert,tagRCF.m_ulCertLen);
		LOG_INFO("sofRequest.base64EncodeCert=%s", szCert.c_str());

	

		ns1__SOF_USCOREVerifySignedData sofRequest;
		BOOL bResp = FALSE;

		std::string szToken("9877654433");
		//sofRequest.tokenId = &szToken;
	

		//sTemp = "JDUlDpI6Iu4LubX8vl1REAZ+9PSzO2PxOYpkMM+4z3Mu/UUAd159/hgZsTy3gl/EnXyN1KsYa095Ni/2MeZV5Fzn/T+ghdhkzCkQe5r8BEg31sDawDFXanSi+6cVh4PBsSLiDKuZZh7q37wTftRc04OrTvXPhJN1U7X26rcwV1M=";
		//m_szRandom = "qwer1234";
		//szCert ="MIIEETCCA3qgAwIBAgIIIBcFIwMAZAMwDQYJKoZIhvcNAQEFBQAwgY4xDTALBgNVBAYeBABDAE4xDzANBgNVBAgeBmxfgs93ATEPMA0GA1UEBx4GU1dOrF4CMS8wLQYDVQQKHiZsX4LPdwF1NVtQVUZSoYvBTmaLpIvBTi1fw2cJllCNI077UWxT+DERMA8GA1UECx4IAEoAUwBDAEExFzAVBgNVBAMeDgBKAFMAQwBBAF8AQwBBMB4XDTE2MTExNDAzMDE1N1oXDTE4MDUyMzA2MzU1OFowgekxDjAMBgNVBFgMBTAwMDAxMQ8wDQYDVQQaHgafE2l8UzoxLTArBgNVBAEeJAAzADIAMAAxADEAMgAxADkAOAAxADAANQAxADEAMAAwADEANDEWMBQGBFUEiFceDAAxADAAMgA0ADUAMTEbMBkGA1UELR4SAHUAcwBlAHIAQwBlAHIAdAAyMQ0wCwYDVQQGHgQAQwBOMQ8wDQYDVQQIHgZsX4LPdwExDzANBgNVBAceBlNXTqxeAjEPMA0GA1UECx4GADkAOQA3MQ8wDQYDVQQqHgaYfmW5Zg4xDzANBgNVBAMeBph+ZblmDjCBnzANBgkqhkiG9w0BAQEFAAOBjQAwgYkCgYEAr5gQMfxEYK3ZnFk0I5C8UYtOFajpKsFa+8TSM4Jd4DnlsNA9DsMfUeN6MuIJhZFotSnvQqY6ZtsTFYyoEuot2B4jTrvaK1mt5yOjxWAFdKXBzWhCzikuu0HqS27AfnmUtxgysnxFYafMBsuaN1p4Q8o8lViWfYrafD4wxp/ueA0CAwEAAaOCARkwggEVMAkGA1UdEwQCMAAwCwYDVR0PBAQDAgbAMDEGA1UdJQQqMCgGCCsGAQUFBwMCBggrBgEFBQcDCAYIKwYBBQUHAwQGCCsGAQUFBwMIMB8GA1UdIwQYMBaAFFbAyBFUVTYGSn3tJlDoiL23o3oJMEcGCCsGAQUFBwEBBDswOTA3BggrBgEFBQcwAoYraHR0cDovLzEwLjEwOC41LjI6ODg4MC9kb3dubG9hZC9KU0NBX0NBLmNlcjA/BgNVHR8EODA2MDSgMqAwhi5odHRwOi8vd3d3LmpzY2EuY29tLmNuL2NybGRvd25sb2FkL0pTQ0FfQ0EuY3JsMB0GA1UdDgQWBBTDNGwP6Uo8840VpW+tbf6AJAalWTANBgkqhkiG9w0BAQUFAAOBgQAsNfb0tjbn0G5Lskrdv6iH6mmk0ekmHBaWtYnM3a+cFiShNqyVKRGyTHo5/4FVZW6SLw2jiJR50DBLZ2HQis+EpUYPQo5X1D9EkvS6JbG64KtZb6tnjthmOEAeD07lZbhkJBSWTguFeMklehm4HAe0kRcbNtTItx5AS41tr9UItA==";

		sofRequest.signValue = &sTemp;
		sofRequest.inData =&m_szRandom;
		sofRequest.base64EncodeCert =&szCert;

		

		LOG_INFO("soapSender::SOF_VerifySignedData");
		int nReturn_ = soapSender::SOF_VerifySignedData(sofRequest, bResp);

		std::string szResp;
		if (bResp)
		{
			szResp="{\"resultCode\":\"0\",\"resultMsg\":\"CA��֤�ɹ���\"}";
			LOG_INFO(szResp.c_str());
			SendLoginResp(szResp);
			SetTimer(1,100,NULL);
			
		}
		else
		{
			szResp="{\"resultCode\":\"1\",\"resultMsg\":\"CA��֤ʧ�ܣ�\"}";
			LOG_INFO(szResp.c_str());
			SendLoginResp(szResp);
			SetTimer(1,100,NULL);
			if (TEST_MODE == m_nMode)
			{
				AfxMessageBox("CA��֤ʧ�ܣ�");
			}
		}
	}

}

BOOL CCAPCManageDlg::SendLoginResp(std::string szResp)
{
	if (m_pReq != NULL)
	{
		CHttpProtocol2 *pHttpProtocol = (CHttpProtocol2 *)m_pReq->pHttpProtocol;
		pHttpProtocol->SendLoginResp(m_pReq,szResp);


	//	pHttpProtocol->Disconnect(m_pReq);
		delete m_pReq;
		m_pReq = NULL;
	//	pHttpProtocol->CountDown();	// client������1

		return TRUE;
	}

	return FALSE;

}

BOOL CCAPCManageDlg::GetGenRandomFromServer(std::string& szResp)
{
	ns1__SOF_USCOREGenRandom sofRequest;

	std::string szToken("9877654433");
	//sofRequest.tokenId = &szToken;
	sofRequest.len= 8;

	int nReturn_ = soapSender::SOF_USCOREGenRandom(sofRequest, szResp);
	if (0 == nReturn_)
	{
		LOG_INFO("Get service genrandom succeed,tokenid=%s,random len=%d,szResp=%s",szToken.c_str(),sofRequest.len,szResp.c_str());

		//
		/*int len = szResp.length();
		unsigned char* szBuf = new unsigned char[len];
		memset(szBuf, 0, len);
		int nbase64 = Base64Decode(szBuf, szResp.c_str());

		szResp = (char*)szBuf;
		delete szBuf;*/

		return TRUE;
	}
	else
	{
		LOG_ERROR("Get service genrandom failed,tokenid=%s,random len=%d",szToken.c_str(),sofRequest.len);
		return FALSE;
	}
}

BOOL CCAPCManageDlg::initList()
{
	DWORD dwStyle = m_listCert.GetExtendedStyle();
	dwStyle |= LVS_EX_FULLROWSELECT;//ѡ��ĳ��ʹ���и�����ֻ������report����listctrl��
	dwStyle |= LVS_EX_GRIDLINES;//�����ߣ�ֻ������report����listctrl��
	//dwStyle |= LVS_EX_CHECKBOXES;//itemǰ����checkbox�ؼ�
	m_listCert.SetExtendedStyle(dwStyle); //������չ���

	m_listCert.InsertColumn(0,"��ѡ��������ǩ����֤��",LVCFMT_LEFT, 1200);
	//m_listCert.InsertColumn(1,"֤��䷢��",LVCFMT_LEFT, 160);
	//m_listCert.InsertColumn(2,"����ʱ��",LVCFMT_LEFT, 80);
	//m_listCert.InsertColumn(3,"֤������",LVCFMT_LEFT,70);
	//int nRow = m_listCert.InsertItem(0,"xzt");//������
	//m_listCert.SetItemText(nRow,1,"jsca");
	return TRUE;
}

void CCAPCManageDlg::SetContainerCloseStatus(HCONTAINER  hAContainer)
{
	int nCount = m_vecCert.size();
	for (int i =0; i< nCount;i++)
	{
		if (m_vecCert[i].m_hAContainer == hAContainer)
		{
			m_vecCert[i].m_bCloseContainer = TRUE;
		}
	}
}

void CCAPCManageDlg::SetAppCloseStatus(HCONTAINER  hApp)
{
	int nCount = m_vecCert.size();
	for (int i =0; i< nCount;i++)
	{
		if (m_vecCert[i].m_hApp == hApp)
		{
			m_vecCert[i].m_bCloseApp = TRUE;
		}
	}
}

void CCAPCManageDlg::ClearData()
{
	int nCount = m_vecCert.size();
	for (int i =0; i< nCount;i++)
	{
		if (!m_vecCert[i].m_bCloseContainer)
		{
			g_readUKey= (CReadUKey*)(m_vecCert[i].m_pReadUkey);
			g_readUKey->m_PSKF_CloseContainer(m_vecCert[i].m_hAContainer);
			SetContainerCloseStatus(m_vecCert[i].m_hAContainer);
		}
		

		free(m_vecCert[i].m_pCert);
	}

	for (int i =0; i< nCount;i++)
	{
		if (!m_vecCert[i].m_bCloseApp)
		{
			g_readUKey= (CReadUKey*)(m_vecCert[i].m_pReadUkey);
			g_readUKey->m_PSKF_CloseApplication(m_vecCert[i].m_hApp);
			SetAppCloseStatus(m_vecCert[i].m_hApp);
		}
		
	}

	m_vecCert.clear();

	m_listCert.DeleteAllItems();

	//���еĵ����dll��Ϣ
	nCount = m_vecDev.size();
	for (int i=0; i<nCount;i++)
	{
		g_readUKey= (CReadUKey*)(m_vecDev[i].m_pReadUkey);
		g_readUKey->ClearDLL();
		delete g_readUKey;
		g_readUKey = NULL;
	}

	m_vecDev.clear();
}


void CCAPCManageDlg::OnBnClickedBtnRequest()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	LOG_INFO("login request");

	ClearData();

	GetDlgItem(IDC_BTN_REQUEST)->EnableWindow(FALSE);

	
	
	//if (m_szRandom.length()>8)
	//{
	//	m_szRandom = m_szRandom.substr(0,8);
	//}
	//else
	//{
	//	m_szRandom="qwer1234";
	//}

	//m_szRandom="qwer1234qwertyui";
	
//	Base64 bs;
//	m_szRandom = bs.base64_encode(m_szRandom);

//	m_szRandom="qwertyuiop1234567890asdfghjkl13211";


	//string sfd = "��΢���2";
	//int nwe = sfd.length();
	//BYTE p[50];
	//memset(p,0,50);
	//memcpy(p,sfd.c_str(),sfd.length());
	//int nLen = strlen((char*)p);


	//Base64 bs;
	//string sf = bs.B64_Encode(p,nLen);

	//string sSigTemp = (char*)p;
	//
	//int nLen2 = sSigTemp.length();
	//CEnDecodeClass::Gbk2Utf(sSigTemp);
	//nLen2 = sSigTemp.length();

	//string sf2 = bs.B64_Encode((unsigned char*)sSigTemp.c_str(),nLen2);
	
	
	

	//�õ�UKey Dll
	CollectUSBInfo();

	//����dll·������dll
	ImportUKeyDlls();

	

	//֤����Щ��Ϣ��Ҫ��ʾ�ڽ����ϣ����û�ѡ��--xzt
	//ѡ��֤��

	int nCount = m_vecCert.size();
	if (nCount<=0)
	{
		AfxMessageBox("û���ҵ�֤��");
		GetDlgItem(IDC_BTN_REQUEST)->EnableWindow(TRUE);
		return;
	}
	int nRow = 0;
	for (int i =0; i< nCount;i++)
	{
		//nRow = m_listCert.InsertItem(nRow,m_vecCert[i].m_szName.c_str());//������
		//m_listCert.SetItemText(nRow,1,m_vecCert[i].m_szCertName.c_str());
		//nRow++;

		//analysisCert2(m_vecCert[i].m_pCert,m_vecCert[i].m_ulCertLen,nRow, (CReadUKey*)m_vecCert[i].m_pReadUkey);
		if (m_vecCert[i].m_bSignFlag)
		{
			analysisCert3(m_vecCert[i].m_pCert,m_vecCert[i].m_ulCertLen,nRow, (CReadUKey*)m_vecCert[i].m_pReadUkey);
			//m_listCert.SetItemText(nRow,3,"ǩ��֤��");
			nRow++;
		}
	/*	else
		{
			m_listCert.SetItemText(nRow,3,"����֤��");
		}*/
		

		


	}

	GetDlgItem(IDC_BTN_REQUEST)->EnableWindow(TRUE);
}

void CCAPCManageDlg::ImportUKeyDlls()
{
	DevNameDll tagDND;
	int nCount = m_vecDev.size();
	for (int i=0; i<nCount;i++)
	{
		m_vecDev[i].m_pReadUkey = new CReadUKey();
		g_readUKey= (CReadUKey*)(m_vecDev[i].m_pReadUkey);
		g_readUKey->m_szDevName = m_vecDev[i].m_szDevName;
		g_readUKey->m_szDLLName = m_vecDev[i].m_szDllFile;
		//g_readUKey->m_szDLLName = "C:\\Windows\\SysWOW64\\USBKey_API_YY.dll";
		m_vecDev[i].m_bOnline = g_readUKey->initDll(m_vecDev[i].m_szDllFile);
		if (m_vecDev[i].m_bOnline)
		{
			g_readUKey->GetDevInfo2(m_vecCert);
		}
	}
}

void CCAPCManageDlg::CollectUSBInfo()
{
	// ��ȡ��ǰϵͳ����ʹ�õ��豸
	DWORD dwFlag = (DIGCF_ALLCLASSES | DIGCF_PRESENT);
	HDEVINFO hDevInfo = SetupDiGetClassDevs(NULL, NULL, NULL, dwFlag);
	if( INVALID_HANDLE_VALUE == hDevInfo )
	{
		AfxMessageBox( _T("��ȡϵͳ�豸�б�ʧ��") );
		return;
	}

	// ׼�����������豸����USB
	SP_DEVINFO_DATA sDevInfoData;
	sDevInfoData.cbSize = sizeof(SP_DEVINFO_DATA);


	//VID: ZYZW  ��˾�������̺�
	CString strText;
	TCHAR szDIS[MAX_PATH]; // Device Identification Strings, 
	DWORD nSize = 0 ;
	for(int i = 0; SetupDiEnumDeviceInfo(hDevInfo,i,&sDevInfoData); i++ )
	{
		nSize = 0;
		if ( !SetupDiGetDeviceInstanceId(hDevInfo, &sDevInfoData, szDIS, sizeof(szDIS), &nSize) )
		{
			AfxMessageBox( _T("��ȡ�豸ʶ���ַ���ʧ��") );
			break;
		}

		// �豸ʶ�𴮵�ǰ�����ַ��Ƿ���"USB", ģ�壺 USB\VID_XXXX&PID_XXXX\00000xxxxxxx
		CString strDIS( szDIS );
		strDIS.MakeLower();
		CString strVID,strPID;
		if( strDIS.Left( 3 ) == _T("usb") )
		{
			strText += strDIS;
			int iVID_Pos = strDIS.Find( "vid_");
			

			if( iVID_Pos != -1)
			{
				// VID: ���̺�
				int iVID_End = strDIS.Find("&",iVID_Pos);
				if (iVID_End>iVID_Pos)
				{
					strVID = strDIS.Mid(iVID_Pos,(iVID_End-iVID_Pos));
				}

				// PID :��Ʒ��
				int iPID_Pos = strDIS.Find("pid_",iVID_End );
				if (iPID_Pos != -1)
				{
					int iSlashPos = strDIS.Find(_T('\\'),iPID_Pos);
					int iPIDEnd = strDIS.Find(_T('&'),iPID_Pos);
					if (-1 != iPIDEnd && iPIDEnd<iSlashPos)
					{
						iSlashPos = iPIDEnd;
					}

					if (iSlashPos>iPID_Pos)
					{
						strPID = strDIS.Mid( iPID_Pos, (iSlashPos - iPID_Pos) );
					}
				}
				
				
			}

			if (!strVID.IsEmpty()&&!strPID.IsEmpty())
			{
				LOG_INFO("VID=%s,PID=%s",strVID,strPID);
				//�õ��豸����
				RegWinInfo* pTagRWI = GetDevName(strPID.GetBuffer(), strVID.GetBuffer());

				//�豸����Ѿ����أ��ı�״̬�����û�м��أ���ע����еõ�dll·��
				if(NULL !=pTagRWI && !IsDevExist(pTagRWI->m_szName))
				{
					LOG_INFO("DevName=%s",pTagRWI->m_szName.c_str());
					std::string szDllPath = GetDLlFromName(pTagRWI);
					if (!szDllPath.empty())
					{
						DevNameDll tagDND;
						tagDND.m_szDevName = pTagRWI->m_szName;
						tagDND.m_szDllFile = szDllPath;
						m_vecDev.push_back(tagDND);

					}
					else
					{
						LOG_ERROR("UKey name=%s,dll path is empty",pTagRWI->m_szName.c_str());
					}
				}
			}
		}
	}


	// �ͷ��豸
	SetupDiDestroyDeviceInfoList(hDevInfo);
}

RegWinInfo* CCAPCManageDlg::GetDevName(std::string szPID,std::string szVID)
{
	RegWinInfo* pTagRWI=NULL;
	int nCount = m_vecRWI.size();
	for (int i=0; i<nCount;i++)
	{
		pTagRWI = &(m_vecRWI[i]);
		if (0 == pTagRWI->m_szPID.compare(szPID)&& 0 == pTagRWI->m_szVID.compare(szVID))
		{
			return pTagRWI;
		}
	}

	return NULL;
}

BOOL CCAPCManageDlg::IsDevExist(std::string szDevName)
{
	DevNameDll tagDND;
	int nCount = m_vecDev.size();
	for (int i=0; i<nCount;i++)
	{
		tagDND = m_vecDev[i];

		if (0 == tagDND.m_szDevName.compare(szDevName))
		{
			return TRUE;
		}
	}

	return FALSE;
}

BOOL Is64BitOS()
{
	typedef VOID (WINAPI *LPFN_GetNativeSystemInfo)( __out LPSYSTEM_INFO lpSystemInfo );
	LPFN_GetNativeSystemInfo fnGetNativeSystemInfo = (LPFN_GetNativeSystemInfo)GetProcAddress( GetModuleHandleW(L"kernel32"),"GetNativeSystemInfo");
	if(fnGetNativeSystemInfo)
	{
		SYSTEM_INFO stInfo = {0};
		fnGetNativeSystemInfo( &stInfo);
		if( stInfo.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_IA64
			|| stInfo.wProcessorArchitecture == PROCESSOR_ARCHITECTURE_AMD64)
		{
			return TRUE;
		}
	}
	return FALSE;
}


std::string CCAPCManageDlg::GetDLlFromName(RegWinInfo* pTagRWI)
{
	std::string szPath;
	if (Is64BitOS())
	{
		szPath = "SOFTWARE\\Wow6432Node\\Microsoft\\Cryptography\\Defaults\\Provider\\"+pTagRWI->m_szName;
	}
	else
	{
		szPath = "SOFTWARE\\Microsoft\\Cryptography\\Defaults\\Provider\\"+pTagRWI->m_szName;
	}

	CHAR szCompany[48]={0};


	HKEY hSoftKey = NULL;
	LONG nRet = RegOpenKeyExA(HKEY_LOCAL_MACHINE, szPath.c_str(), 0, KEY_READ,&hSoftKey);
	if (nRet == ERROR_SUCCESS)
	{
		int				nRet		= 0;
		DWORD			dwValueType = REG_SZ;
		DWORD			dwSize		= 0;
		char			szDllPath[MAX_PATH] = {0};
		dwValueType = REG_SZ;
		dwSize = sizeof(szDllPath);
		if (pTagRWI->m_szPath.empty())
		{
			nRet = RegQueryValueEx(hSoftKey, "SKFImage Path",NULL,&dwValueType, (LPBYTE)&szDllPath, &dwSize);
			if (0 != nRet)
			{
				nRet = RegQueryValueEx(hSoftKey, "Image Path",NULL,&dwValueType, (LPBYTE)&szDllPath, &dwSize);
				if (0 != nRet)
				{
					nRet = RegQueryValueEx(hSoftKey, "realPath",NULL,&dwValueType, (LPBYTE)&szDllPath, &dwSize);
					if (0 == nRet)
					{
						LOG_INFO("DevName=%s, realPath=%s",pTagRWI->m_szName.c_str(),szDllPath);
					}
				}
				else
				{
					LOG_INFO("DevName=%s, Image Path=%s",pTagRWI->m_szName.c_str(),szDllPath);
				}
			}
			else
			{
				LOG_INFO("DevName=%s, SKFImage Path=%s",pTagRWI->m_szName.c_str(),szDllPath);
			}
		}
		else
		{
			nRet = RegQueryValueEx(hSoftKey,pTagRWI->m_szPath.c_str(),NULL,&dwValueType, (LPBYTE)&szDllPath, &dwSize);
			if (0 == nRet)
			{
				LOG_INFO("DevName=%s, %s=%s",pTagRWI->m_szName.c_str(),pTagRWI->m_szPath.c_str(),szDllPath);
			}
		}
		

		return szDllPath;

	}
	if (hSoftKey != NULL)
		RegCloseKey(hSoftKey);


	return "";
}




LRESULT CCAPCManageDlg::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	// TODO: �ڴ����ר�ô����/����û���

	return CDialog::WindowProc(message, wParam, lParam);
}

BOOL CCAPCManageDlg::OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult)
{
	// TODO: �ڴ����ר�ô����/����û���
//	m_diskInfo.OnDeviceChange(this->GetSafeHwnd(),wParam,lParam);

	return CDialog::OnWndMsg(message, wParam, lParam, pResult);
}

void CCAPCManageDlg::OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_nSelect = m_listCert.GetSelectionMark();
	if (m_nSelect>=0)
	{
		GetDlgItem(IDC_BTN_LOGIN)->EnableWindow(TRUE);
	}
	else
	{
		GetDlgItem(IDC_BTN_LOGIN)->EnableWindow(FALSE);
	}
	*pResult = 0;
}

void CCAPCManageDlg::OnDestroy()
{
	CDialog::OnDestroy();
	if (m_bStart &&m_pHttpProtocol)	
	{
		m_pHttpProtocol->StopHttpSrv();
		delete m_pHttpProtocol;
		m_pHttpProtocol = NULL;
	}

	m_bStart = false;

	ClearData();

	// TODO: �ڴ˴������Ϣ����������
}

// ��ʾ��־��Ϣ
LRESULT CCAPCManageDlg::AddLog(WPARAM wParam, LPARAM lParam)
{
	char szBuf[284];
	CString *strTemp = (CString *)wParam; 

	SYSTEMTIME st;
	GetLocalTime(&st);
	wsprintf(szBuf,"%02d:%02d:%02d.%03d   %s", st.wHour, st.wMinute, st.wSecond, 
		st.wMilliseconds, *strTemp);
	LOG_INFO(szBuf);
	delete strTemp;
	strTemp = NULL;
	return 0;
}

// ��ʾ���պͷ��͵���������
LRESULT CCAPCManageDlg::ShowData(WPARAM wParam, LPARAM lParam)
{
	PHTTPSTATS pStats = (PHTTPSTATS)wParam;
	m_dwReceived += pStats->dwRecv;
	m_dwTransferred += pStats->dwSend;

	TRACE1("Rev %d\n", pStats->dwRecv);
	TRACE1("Send %d\n", pStats->dwSend);
	TRACE1("Total Rev %d\n", m_dwReceived);
	TRACE1("Total Send %d\n", m_dwTransferred);

	UpdateData(false);
	return 0;
}

LRESULT CCAPCManageDlg::OnLogin(WPARAM wParam, LPARAM lParam)
{
	ShowWindow(SW_SHOW);
	m_pReq = (PREQUEST)wParam;
	OnBnClickedBtnRequest();
	return 0;
}
void CCAPCManageDlg::OnNcPaint()
{
	// TODO: �ڴ˴������Ϣ����������
	// ��Ϊ��ͼ��Ϣ���� CDialog::OnNcPaint()
	//CDialog::OnNcPaint();
	
	if(g_i > 0 &&RUN_MODE ==m_nMode) 
	{ 
		g_i --; 
		ShowWindow(SW_HIDE); 
	} 
	else 
		CDialog::OnNcPaint(); 
}

void CCAPCManageDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ	
	if(nIDEvent ==1&&RUN_MODE ==m_nMode)
	{
		KillTimer(1);
		ShowWindow(SW_HIDE);
	}

	CDialog::OnTimer(nIDEvent);
}

void CCAPCManageDlg::OnClose()
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if (RUN_MODE == m_nMode)
	{
		SetTimer(1,100,NULL);
		return;
	}

	CDialog::OnClose();
}

void CCAPCManageDlg::OnBnClickedCancel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (RUN_MODE == m_nMode)
	{
		SetTimer(1,100,NULL);
		return;
	}
	OnCancel();
}

void CCAPCManageDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if (RUN_MODE == m_nMode)
	{
		SetTimer(1,100,NULL);
		return;
	}
	OnOK();
}

void CCAPCManageDlg::OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	
	*pResult = 0;
	m_nSelect = m_listCert.GetSelectionMark();
	if (m_nSelect<0)
	{
		return;
	}
	OnBnClickedBtnLogin();
}

BOOL CCAPCManageDlg::analysisCert()
{

	FILE    *fp;
	unsigned char buf[5000],*p;
	int     len;



	/* cert.cerΪDER���������֤��

	�û������windowsϵͳ�����Դ�IE�е���һ��x509v3������֤����Ϊ����Ŀ��

	*/

	fp=fopen("D:\\testfile\\33.cer","rb");

	if(!fp) return -1;

	len=fread(buf,1,5000,fp);
	fclose(fp);
	p=buf;

	char* szBuf = new char[len*2];
	memset(szBuf, 0, len*2);
	int nbase64 = Base64Encode(szBuf, buf, len);


	CString strFileName("D:\\1.txt");
	SaveBase64(szBuf,strFileName);



	CCSPCertificate cspCert;
	cspCert._DecodeX509Cert(p,len);

	//�õ�ʹ����
	char lpValue[500] = {0};
	ULONG ulLen = 500;
	cspCert.get_SubjectName(lpValue,&ulLen);

	//�õ��䷢��
	char lpIssuer[500] = {0};
	ULONG ulIssuerLen = 500;
	cspCert.get_Issuer(lpIssuer,&ulIssuerLen);

	//�õ���Ч��
	SYSTEMTIME tmStart;
	SYSTEMTIME tmEnd;
	cspCert.get_ValidDate(&tmStart, &tmEnd);
	

	return TRUE;
}

BOOL CCAPCManageDlg::analysisSM2Cert()
{

	FILE    *fp;
	unsigned char* p = NULL;
	char buf[5000];
	int     len;


	fp=fopen("D:\\testfile\\33.cer","rb");

	if(!fp) return -1;

	len=fread(buf,1,5000,fp);
	fclose(fp);

	unsigned char* szBuf = new unsigned char[len];
	memset(szBuf, 0, len);
	int nbase64 = Base64Decode(szBuf, buf);

	p = szBuf;


//	CString strFileName("D:\\1.txt");
//	SaveBase64(szBuf,strFileName);



	CCSPCertificate cspCert;
	cspCert._DecodeX509Cert(p,nbase64);

	//�õ�ʹ����
	char lpValue[500] = {0};
	ULONG ulLen = 500;
	cspCert.get_SubjectName(lpValue,&ulLen);

	//�õ��䷢��
	char lpIssuer[500] = {0};
	ULONG ulIssuerLen = 500;
	cspCert.get_Issuer(lpIssuer,&ulIssuerLen);

	//�õ���Ч��
	SYSTEMTIME tmStart;
	SYSTEMTIME tmEnd;
	cspCert.get_ValidDate(&tmStart, &tmEnd);

	ULONG lUsage=0;
	cspCert.get_KeyUsage(&lUsage);
	

	return TRUE;
}

BOOL CCAPCManageDlg::analysisCert3(unsigned char* p,int len,int& nRow, CReadUKey* pReadUKey)
{

	CCSPCertificate cspCert;
	cspCert._DecodeX509Cert(p,len);

	//�õ�ʹ����
	char lpValue[500] = {0};
	ULONG ulLen = 500;
	cspCert.get_SubjectName(lpValue,&ulLen);

	//OID.2.5.4.88=00001, OID.2.5.4.26=��Ͻ��, OID.2.5.4.45=entCert2, C=CN, S=����ʡ, 
	//L=�Ͼ���, O=����sm2֤��20170427, OU=666, CN=����sm2֤��20170427
	CString strTmp = lpValue;
	int nFind = strTmp.Find("CN=");
	if (nFind != -1)
	{
		strTmp = strTmp.Right(strTmp.GetLength()-(nFind+3));
	}


	


	//�õ��㷨����
	cspCert.get_KeyType(&(pReadUKey->m_ulType));

	CString szInfo;
	if (pReadUKey->m_ulType == CERT_KEY_ALG_RSA)
	{
		szInfo +="(RSA/SKF+ǩ��)[";
		szInfo +=strTmp;
		szInfo +="]";
	}
	else
	{
		szInfo +="(SM2/SKF+ǩ��)[";
		szInfo +=strTmp;
		szInfo +="]";
	}

	szInfo +=lpValue;
	nRow = m_listCert.InsertItem(nRow,szInfo);//������



	return TRUE;
}

BOOL CCAPCManageDlg::analysisCert2(unsigned char* p,int len,int& nRow, CReadUKey* pReadUKey)
{

	CCSPCertificate cspCert;
	cspCert._DecodeX509Cert(p,len);

	//�õ�ʹ����
	char lpValue[500] = {0};
	ULONG ulLen = 500;
	cspCert.get_SubjectName(lpValue,&ulLen);

	//OID.2.5.4.88=00001, OID.2.5.4.26=��Ͻ��, OID.2.5.4.45=entCert2, C=CN, S=����ʡ, 
	//L=�Ͼ���, O=����sm2֤��20170427, OU=666, CN=����sm2֤��20170427
	CString strTmp = lpValue;
	int nFind = strTmp.Find("CN=");
	if (nFind != -1)
	{
		strTmp = strTmp.Right(strTmp.GetLength()-(nFind+3));
	}


	nRow = m_listCert.InsertItem(nRow,strTmp);//������

	//�õ��䷢��
	char lpIssuer[500] = {0};
	ULONG ulIssuerLen = 500;
	cspCert.get_Issuer(lpIssuer,&ulIssuerLen);

	m_listCert.SetItemText(nRow,1,lpIssuer);

	//�õ���Ч��
	SYSTEMTIME tmStart;
	SYSTEMTIME tmEnd;
	cspCert.get_ValidDate(&tmStart, &tmEnd);

	CString strDate;
	strDate.Format("%d/%d/%d",tmEnd.wYear,tmEnd.wMonth,tmEnd.wDay);
	m_listCert.SetItemText(nRow,2,strDate);

	//�õ��㷨����
	cspCert.get_KeyType(&(pReadUKey->m_ulType));

	//�õ�֤������
	//ULONG ulUsage=0;
	//cspCert.get_KeyUsage(&ulUsage);
	

	return TRUE;
}

BOOL one_select_file(CString &strPath,CString &strFile,BOOL open_save)
{
	CFileDialog fileDlg(open_save ,  // TRUE��Open��FALSE����Save As�ļ��Ի���
		".txt",  // Ĭ�ϵĴ��ļ�������
		strFile, // Ĭ�ϴ򿪵��ļ��� 
		OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT | OFN_NOCHANGEDIR ,  // ��ѡ��
		"txt�ļ�(*.txt)|*.txt|�����ļ�(*.*) |*.*||"  // �򿪵��ļ�����
		);

	fileDlg.m_ofn.lpstrInitialDir=strPath;//��ʼ��·����
	if(fileDlg.DoModal() == IDOK)
	{
		strFile = fileDlg.GetPathName();//����ѡ���������ļ����ƣ�
		return TRUE;
	}
	return FALSE;
}

void CCAPCManageDlg::SaveBase64(char* szbuf, CString strFileName)
{
	FILE    *fp;
	int     len=0;


	fp=fopen(strFileName,"wb");

	if(!fp) return ;

	len = fwrite(szbuf,sizeof(char),strlen(szbuf),fp);

	fclose(fp);
}


void CCAPCManageDlg::OnBnClickedButton3()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������


//	analysisSM2Cert();
//	return;
	//�������������
	if (m_nSelect < 0)
	{
		AfxMessageBox("����ѡ��֤��");
		return;
	}
	ReadCertInfo& tagRCF =  m_vecCert[m_nSelect];
	g_readUKey = (CReadUKey*)tagRCF.m_pReadUkey;
	g_readUKey->m_hDev = tagRCF.m_hDev;
	g_readUKey->m_hApp = tagRCF.m_hApp;
	g_readUKey->m_hAContainer = tagRCF.m_hAContainer;


	//תΪbase64
	char* szBuf = new char[tagRCF.m_ulCertLen*2];
	memset(szBuf, 0, tagRCF.m_ulCertLen*2);
	int nbase64 = Base64Encode(szBuf,tagRCF.m_pCert,tagRCF.m_ulCertLen);
	LOG_INFO("sofRequest.base64EncodeCert=%s", szBuf);

	g_szbase64Cert = szBuf;

	//
	CString strPath="d:/";
	CString strFileName="1.txt";

	BOOL bRet =one_select_file(strPath,strFileName,FALSE); //FALSE����ļ�

	if (bRet)
	{
		SaveBase64(szBuf,strFileName);
	}

	


	delete szBuf;
}

