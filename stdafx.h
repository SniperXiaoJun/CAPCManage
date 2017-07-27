
// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���Ǿ���ʹ�õ��������ĵ�
// �ض�����Ŀ�İ����ļ�

#pragma once

#ifndef _SECURE_ATL
#define _SECURE_ATL 1
#endif

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // �� Windows ͷ���ų�����ʹ�õ�����
#endif

#include "targetver.h"

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // ĳЩ CString ���캯��������ʽ��

// �ر� MFC ��ĳЩ�����������ɷ��ĺ��Եľ�����Ϣ������
#define _AFX_ALL_WARNINGS

#include <afxwin.h>         // MFC ��������ͱ�׼���
#include <afxext.h>         // MFC ��չ


#include <afxdisp.h>        // MFC �Զ�����



#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // MFC �� Internet Explorer 4 �����ؼ���֧��
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>             // MFC �� Windows �����ؼ���֧��
#endif // _AFX_NO_AFXCMN_SUPPORT

#include <afxcontrolbars.h>     // �������Ϳؼ����� MFC ֧��
#include <afxdhtml.h>

#include "CDALog.h"
#include <atlwin.h>
#include "EncodeDecodeMiME.h"

#define LOG_MSG			WM_USER+1
#define DATA_MSG		WM_USER+2
#define LOGIN_MSG		WM_USER+3

#define GLOBAL_ENCODING_TYPE  (PKCS_7_ASN_ENCODING | X509_ASN_ENCODING)
#define CERT_ERR_INVALIDPARAM -1
#define CERT_ERR_OK 0;
#define CERT_ERR_INVILIDCALL -2
#define CERT_ERR_BUFFER_TOO_SMALL -3
#define CERT_ERR_ALG_UNKNOWN -4
#define CERT_KEY_ALG_RSA 0
#define CERT_KEY_ALG_ECC 1
#define CERT_USAGE_SIGN 0
#define CERT_USAGE_EXCH 1
#define CERT_ERR_USAGE_UNKNOWN -1
#define CERT_SIGNATURE_ALG_RSA_RSA  "1.2.840.113549.1.1.1"   //RSAֱ��ǩ��  
#define CERT_SIGNATURE_ALG_MD2RSA   "1.2.840.113549.1.1.2"   //MD2��Hash��Ȼ��RSAǩ��  
#define CERT_SIGNATURE_ALG_MD4RSA   "1.2.840.113549.1.1.3"   //MD4��Hash��Ȼ��RSAǩ��  
#define CERT_SIGNATURE_ALG_MD5RSA   "1.2.840.113549.1.1.4"   //MD5��Hash��Ȼ��RSAǩ��  
#define CERT_SIGNATURE_ALG_SHA1RSA  "1.2.840.113549.1.1.5"   //SHA1��Hash��Ȼ��RSAǩ��  
#define CERT_SIGNATURE_ALG_SM3SM2   "1.2.156.10197.1.501"    //SM3��Hash��Ȼ��SM2ǩ��  
#define CERT_ERR_FAILED -1









#ifdef _UNICODE
#if defined _M_IX86
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_IA64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='ia64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif
#endif


