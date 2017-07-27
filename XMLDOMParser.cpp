/********************************************************************
	created:	2006/01/17
	created:	17:1:2006   15:38
	filename: 	CXMLDOMParser.CPP
	file base:	CXMLDOMParser
	file ext:	CPP
	author:		xzt
	
	purpose:	Ϊ�˸�����Ķ�дXML�ĵ�,��MSXML4.0����з�װ
				��Ҫ���һЩ�ӿڲ���ת������
				ʹ��ǰȷ���Ѿ���װ��MSXML4.0�����úû���
*********************************************************************/
#include "StdAfx.h"
#include "XMLDOMParser.h"

#define EQUAL 0
const CString ACTION_NAME_FLAG = "ActName";
const CString PARAM_NAME_FLAG = "ParaName";
const CString  ACTION_FLAG = "ACTION";
const CString PARAM_FLAG = "Para";
const CString ACT_FLAG = "ActFlag";
const CString LOGIC_NAME_FLAG = "LogicName";
const CString LOGIC_FLAG = "LOGIC";
const CString PARA_TCL_NAME_FLAG = "ParaTclName";
// ����һ��XML�ĵ�,�ɹ�����true,ʧ�ܷ���false
bool CXMLDOMParser::ConstructXMLFile()
{
	IXMLDOMProcessingInstruction*	pIXMLPI		= NULL;
	HRESULT							hr;
	CComBSTR						bstrData;
	CComBSTR						bstrTarget;
	bool							bRetVal	= false;
	// �ͷ���ǰ���ĵ�
	SafeReleaseXMLDoc();
	// �������ĵ�
	hr = CoCreateInstance(	__uuidof(DOMDocument),
							NULL,
							CLSCTX_INPROC_SERVER,
							__uuidof(IXMLDOMDocument2),
							(void**)&m_pIXMLDoc);
	if(SUCCEEDED(hr))
	{
		// ���������XMLͷ
		bstrTarget = _T("xml");
		bstrData = _T(" version='1.0' encoding='gb2312'");
		hr = m_pIXMLDoc->createProcessingInstruction(bstrTarget, bstrData, &pIXMLPI);
		if(SUCCEEDED(hr))
		{
			hr = m_pIXMLDoc->appendChild(pIXMLPI, NULL);
			pIXMLPI->Release();
			pIXMLPI = NULL;
			if(SUCCEEDED(hr))
			{
				bRetVal = true;
			}
		}
	}
	// ���ʧ��,��ɾ���ĵ�,��Ϊ�ĵ�����XML�ĵ�
	if(!bRetVal)
	{
		SafeReleaseXMLDoc();
	}
	return bRetVal;
}

// ���ļ�����һ��XML�ļ�,���سɹ�����true,����ʧ�ܷ���false
bool CXMLDOMParser::LoadFromXMLFile(const std::string& fileName)
{
	HRESULT							hr;
	bool							bRetVal	= false;
	VARIANT_BOOL					varBool;
	// �ͷ���ǰ���ĵ�
	SafeReleaseXMLDoc();
	// �������ĵ�
	hr = CoCreateInstance(	__uuidof(DOMDocument),
							NULL,
							CLSCTX_INPROC_SERVER,
							__uuidof(IXMLDOMDocument2),
							(void**)&m_pIXMLDoc);
	if(SUCCEEDED(hr))
	{
		// ����
		hr = m_pIXMLDoc->load(CComVariant(CComBSTR(fileName.data())), &varBool);
		if(SUCCEEDED(hr) && varBool==VARIANT_TRUE)
		{
			bRetVal = true;
		}
	}
	// ���ʧ��,��ɾ���ĵ�,��Ϊ�ĵ�����Ϊһ��XML�ĵ�
	if(!bRetVal)
	{
		SafeReleaseXMLDoc();
	}
	return bRetVal;
}

// ����һ�������ݵ�XML�ļ���fileName
bool CXMLDOMParser::SaveToXMLFile(const std::string& fileName)
{
	bool							bRetVal	= false;
	HRESULT							hr;
	if(m_pIXMLDoc)
	{
		hr = m_pIXMLDoc->save(CComVariant(CComBSTR(fileName.data())));
		if(SUCCEEDED(hr))
		{
			bRetVal = true;
		}
		SetFileSave(false);
	}
	return bRetVal;
}

// ��ȫ�ͷ�XML�ĵ�
void CXMLDOMParser::SafeReleaseXMLDoc()
{
	if(m_pIXMLDoc)
	{
		m_pIXMLDoc->Release();
		m_pIXMLDoc = NULL;
	}
}


// ���ĵ�pIParentElemԪ�������nodeName�ڵ�,ֵΪnodeValue
bool CXMLDOMParser::AppendMemberNode(const std::string& nodeName,
							  const std::string& nodeValue,
							  IXMLDOMElement*    pIParentElem,
							  IXMLDOMNode**		 ppOutNewChild)
{
	IXMLDOMElement*		pIMember	= NULL;
	HRESULT				hr;
	bool				bRetVal		= false;
	
	if(m_pIXMLDoc)
	{
		hr = m_pIXMLDoc->createElement(CComBSTR(nodeName.data()), &pIMember);
		if(SUCCEEDED(hr))
		{
			pIMember->put_text(CComBSTR(nodeValue.data()));
			if(pIParentElem)
			{
				hr = pIParentElem->appendChild(pIMember, ppOutNewChild);
			}
			else
			{
				hr = m_pIXMLDoc->appendChild(pIMember, ppOutNewChild);
			}
			pIMember->Release();
			pIMember = NULL;
			if(SUCCEEDED(hr))
			{
				bRetVal = true;
			}
		}
	}
	return bRetVal;
}


// ΪԪ���������
bool CXMLDOMParser::AppendAttributeNode(const std::string&	nodeName,
								 const std::string&	nodeValue,
								 IXMLDOMElement*	pIParentElem)
{
	CComBSTR	bstrName;
	CComVariant	value;
	HRESULT		hr;
	bool		bRetVal	= false;
	
	if(pIParentElem)
	{
		bstrName = nodeName.data();
		value = nodeValue.data();

		hr = pIParentElem->setAttribute(bstrName, value);

		SysFreeString(bstrName.m_str);
		SysFreeString(value.bstrVal);
		if(SUCCEEDED(hr))
		{
			bRetVal = true;
		}
	}
	return bRetVal;
}

// ���Ԫ��pIParentElem������
bool CXMLDOMParser::GetAttributeNode(IXMLDOMNode*			pIParentElem,
							  const std::string&	nodeName,
							  std::string&			nodeValue)
{
	CComBSTR		bstrName;
	CComVariant		value;
	HRESULT			hr;
	IXMLDOMElement*	pIElem	= NULL;
	bool			bRetVal	= false;
	USES_CONVERSION;
	hr = pIParentElem->QueryInterface(__uuidof(IXMLDOMElement), (void**)&pIElem);
	if(SUCCEEDED(hr))
	{
		bstrName = nodeName.data();
		hr = pIElem->getAttribute(bstrName, &value);
		pIElem->Release();
		pIElem = NULL;
		SysFreeString(bstrName.m_str);
		if(SUCCEEDED(hr))
		{
			if (VT_NULL != value.vt)
			{
				nodeValue = W2A(value.bstrVal);
				SysFreeString(value.bstrVal);
			    bRetVal = true;
			}
			
		}
	}
	return bRetVal;
}



bool CXMLDOMParser::SetAttributeNode(IXMLDOMNode*		pIParentElem,
							 const std::string&	nodeName,
							 const std::string&		nodeValue)
{
	CComBSTR		bstrName;
	CComVariant		value;
	HRESULT			hr;
	IXMLDOMElement*	pIElem	= NULL;
	bool			bRetVal	= false;
	USES_CONVERSION;
	hr = pIParentElem->QueryInterface(__uuidof(IXMLDOMElement), (void**)&pIElem);
	if(SUCCEEDED(hr))
	{
		bstrName = nodeName.data();
        value = nodeValue.data();
		hr = pIElem->setAttribute(bstrName, value);
		pIElem->Release();
		pIElem = NULL;
		SysFreeString(bstrName.m_str);
		SysFreeString(value.bstrVal);
		if(SUCCEEDED(hr))
		{
			 bRetVal = true;			
		}
	}
	return bRetVal;	
}
// ����ĵ�Ԫ��
IXMLDOMElement*	CXMLDOMParser::GetDocElem()
{
	IXMLDOMElement*		pIXMLElem	= NULL;
	if(m_pIXMLDoc)
	{
		m_pIXMLDoc->get_documentElement(&pIXMLElem);
	}
	return pIXMLElem;
}

// ��ýڵ��nodeName����
IXMLDOMNode* CXMLDOMParser::GetChildNode(IXMLDOMNode*			pIParentElem,
								  const std::string&	nodeName,
								  std::string&			nodeValue)
{
	IXMLDOMNode*		pIChildNode		= NULL;
	IXMLDOMNode*		pIRetVal		= NULL;
	IXMLDOMNodeList*	pIChildNodes	= NULL;
	long				size = 0;
	long				i = 0;
	CComBSTR			tmpNodeName;
	CComVariant			tmpNodeValue;
	
	USES_CONVERSION;
	if(pIParentElem)
	{
		pIParentElem->get_childNodes(&pIChildNodes);
		if(pIChildNodes)
		{
			pIChildNodes->get_length(&size);
		}
		else
		{
		    return NULL;
		}
		for(i = 0; i < size; ++i)
		{
			pIChildNodes->get_item(i, &pIChildNode);
			if(pIChildNode)
			{
				pIChildNode->get_nodeName(&tmpNodeName);
				if(_stricmp(W2A(tmpNodeName.m_str), nodeName.data()) == 0)
				{
					pIChildNode->get_nodeTypedValue(&tmpNodeValue);
					nodeValue = W2A(tmpNodeValue.bstrVal);
					pIRetVal = pIChildNode;
					break;
				}
				pIChildNode->Release();
				pIChildNode = NULL;
			}
		}
		pIChildNodes->Release();
		pIChildNodes = NULL;
	}
	return pIRetVal;
}

// ���ĵ�pIParentElemԪ�������nodeName�ڵ�,ֵΪnodeValue
bool CXMLDOMParser::AppendMemberNodeNoValue(const std::string& nodeName,
							  const std::string& nodeValue,
							  IXMLDOMElement*    pIParentElem,
							  IXMLDOMNode**		 ppOutNewChild)
{
	IXMLDOMElement*		pIMember	= NULL;
	HRESULT				hr;
	bool				bRetVal		= false;
	
	if(m_pIXMLDoc)
	{
		hr = m_pIXMLDoc->createElement(CComBSTR(nodeName.data()), &pIMember);
		if(SUCCEEDED(hr))
		{
			if(pIParentElem)
			{
				hr = pIParentElem->appendChild(pIMember, ppOutNewChild);
			}
			else
			{
				hr = m_pIXMLDoc->appendChild(pIMember, ppOutNewChild);
			}
			pIMember->Release();
			pIMember = NULL;
			if(SUCCEEDED(hr))
			{
				bRetVal = true;
			}
		}
	}
	return bRetVal;
}


// ���ļ�����һ��XML�ļ�,���سɹ�����true,����ʧ�ܷ���false
bool CXMLDOMParser::LoadFromXMLFile(CString& fileName,CString& XSDFileName)
{
    bool	bRetVal	= false;
	// �ͷ���ǰ���ĵ�
	SafeReleaseXMLDoc();

   	//����Schema����
	
	IXMLDOMSchemaCollection *pIXMLDOMSchemaCollection=NULL;
	HRESULT hr;
	hr = CoCreateInstance(__uuidof(XMLSchemaCache40), NULL, CLSCTX_INPROC_SERVER, 
		   __uuidof(IXMLDOMSchemaCollection), (void**)&pIXMLDOMSchemaCollection);
	if (!SUCCEEDED(hr))
	{
		AfxMessageBox("Create Schema fail !");
		return FALSE;
	}

	VERIFY(pIXMLDOMSchemaCollection != NULL);


	//���XSD�ļ���Schema������
	CString sUrn="urn:awdefine";
	char* sAWDefineXSD = XSDFileName.GetBuffer(XSDFileName.GetLength());
	BSTR BstrUrn = sUrn.AllocSysString();
	_variant_t varXsdFile(sAWDefineXSD);
	hr = pIXMLDOMSchemaCollection->add(BstrUrn,varXsdFile);
	SysFreeString(BstrUrn);
	if (!SUCCEEDED(hr))
	{
		CString sTip;
		sTip.Format("Load %s is failed !", sAWDefineXSD);
		AfxMessageBox(sTip);

		pIXMLDOMSchemaCollection->Release();
		return FALSE;
	}
	
	// ����Document����
	hr = CoCreateInstance(__uuidof(DOMDocument40), NULL, CLSCTX_INPROC_SERVER, 
		   __uuidof(IXMLDOMDocument2), (void**)&m_pIXMLDoc);
	if (!SUCCEEDED(hr))
	{
		pIXMLDOMSchemaCollection->Release();
		AfxMessageBox("Create IID_IXMLDOMDocument2 is failed !");
		
		return FALSE;
	}
	VERIFY(m_pIXMLDoc != NULL);

	//��У�黺�����DOC
	m_pIXMLDoc->putref_schemas(_variant_t(pIXMLDOMSchemaCollection));
	char* m_sAWDefineFile = fileName.GetBuffer(fileName.GetLength());
	_variant_t varAWDefineFile(m_sAWDefineFile);
	VARIANT_BOOL vBool;
	
	//��XML�ļ����ص��ڴ���
	hr = m_pIXMLDoc->load(varAWDefineFile,&vBool);
	if (vBool == VARIANT_FALSE)
	{
		//���XML�ļ��еĴ��󣬲�ָ�������λ�ú�ԭ��
		CheckXmlLoad(m_pIXMLDoc);

		bRetVal= false;
	}
	else
	{
		IXMLDOMElement* pRootNode = GetDocElem();
		if ( NULL == pRootNode)
		{
			bRetVal = false;
		}
		else
		{
			std::string AttrName = "xmlns:x";
			std::string xmlns_xAttrValue;

			GetAttributeNode(pRootNode,AttrName,xmlns_xAttrValue);
		
			if (  0 != xmlns_xAttrValue.compare("urn:awdefine") )
			{
				bRetVal = false;
			}
			else
			{
				bRetVal = true;
			}
			pRootNode->Release();
			pRootNode = NULL;
		}
		if (!bRetVal)
		{
			CString str;
			str.Format("Failed to load file \"%s\"!",fileName);
			AfxMessageBox(str);
		}
		
	}

	pIXMLDOMSchemaCollection->Release();

	if(!bRetVal)
	{
		SafeReleaseXMLDoc();
	}
	return bRetVal;
}
int CXMLDOMParser::CheckXmlLoad(IXMLDOMDocument2 *pDoc)
{
	IXMLDOMParseError *pXMLError=NULL;
	long lErrorCode;
	
	if (SUCCEEDED(pDoc->get_parseError(&pXMLError)) 
		&& SUCCEEDED(pXMLError->get_errorCode(&lErrorCode))
		&& (lErrorCode !=0))
	{
		long lLine,lLinePos,lErrorCode;
		BSTR bstrFile = NULL,bstrReason = NULL;
		
		pXMLError->get_line(&lLine);
		pXMLError->get_linepos(&lLinePos);
		pXMLError->get_errorCode(&lErrorCode);
		pXMLError->get_reason(&bstrReason);
		pXMLError->get_url(&bstrFile);
		
		if (lLine>0)
		{
			CString sFile(bstrFile);
			CString sReason(bstrReason);
			CString sError;
			
			sError.Format("%s\nline=%d\npos=%d\nReason : %s",sFile,lLine,lLinePos,sReason);
			AfxMessageBox(sError);
		}
		else
		{
			AfxMessageBox(" Unknown Error in reading AW define format file");
		}
		
		SysFreeString(bstrFile);
		SysFreeString(bstrReason);
	}
	
	if (pXMLError)
	{
		pXMLError->Release();
		pXMLError = NULL;
	}
	return 0;

}

/************************************************************************
    �� �� ��: getChildByName
    �������ܣ�����pIParentElem�������еĺ���,���Һ�nodeName������ͬ����,Ȼ�����ָ�뷵��.
    ���������pIParentElem : �������ָ��;
	          nodeName     : ��Ҫ���ҵ����� ;
			  bRecursive   : �Ƿ���Ҫ�ݹ����;
    ���������N/A
    �� �� ֵ������   : ���ؽڵ��ָ��
	          ������ : ���ؿ�
    ��    �ߣ�xzt
    ��    �ڣ�2008-03-13 20:16
    �޸ļ�¼��
************************************************************************/
IXMLDOMNode* CXMLDOMParser::getChildByName(IXMLDOMNode* pIParentElem,CString nodeName, bool bRecursive)
{
	if (  NULL == pIParentElem)
	{
		return NULL;
	}

	IXMLDOMNode*		pIChildNode		= NULL;
	IXMLDOMNodeList*	pIChildNodes	= NULL;	
	long				size = 0;     //���ӽڵ�ĸ���

	CComBSTR		tmpNodeName;    //�ڵ������
	CComVariant		tmpNodeValue;   //�ڵ��ֵ
	CString strNodeName;
	
	USES_CONVERSION;
	pIParentElem->get_childNodes(&pIChildNodes); //�õ����еĺ���
	if( NULL == pIChildNodes) 
	{
		return NULL;
	}
	
	//�õ����ӵĸ���
	pIChildNodes->get_length(&size);
	
	for(int i = 0; i < size; ++i)
	{
		pIChildNodes->get_item(i, &pIChildNode); //�õ�һ�����ӽڵ�
		
		if(pIChildNode)
		{
			pIChildNode->get_nodeName(&tmpNodeName);
			strNodeName = (BSTR)(tmpNodeName.m_str);
			if ( 0 == strNodeName.Compare(nodeName) )
			{
				pIChildNodes->Release();
	            pIChildNodes = NULL;
				return pIChildNode;
			}
			
			if (bRecursive)
			{
				IXMLDOMNode* pReturnNode = getChildByName(pIChildNode,nodeName,bRecursive);
				if ( NULL != pReturnNode)
				{
					pIChildNode->Release();
					pIChildNodes->Release();
					pIChildNodes = NULL;
					return pReturnNode;
				}	
			}	
			pIChildNode->Release();
		}
	}

	pIChildNodes->Release();
	pIChildNodes = NULL;
	
	return NULL;
}

/************************************************************************
    �� �� ��: GetValueByNodeAttribute
    �������ܣ�ͨ���ڵ�����Եõ��ڵ��ֵ
    ���������pIParentElem �����׽ڵ��ָ��
			  strAttributeName ��������
			  strAttributeValue ������ֵ
    ���������strNodeValue  ���ڵ��ֵ
    �� �� ֵ������   : true
	          ������ : false
    ��    �ߣ�xzt
    ��    �ڣ�2008-03-24 20:16
    �޸ļ�¼��
************************************************************************/
bool CXMLDOMParser::GetValueByNodeAttribute(IXMLDOMNode* pIParentElem,
											CString strAttributeName, 
											CString strAttributeValue,
											CString& strNodeValue)
{
	if( NULL == pIParentElem)
	{
		return false;
	}


	IXMLDOMNode*		pIChildNode		= NULL;
	IXMLDOMNodeList*	pIChildNodes	= NULL;	
	long	size =0;           //���ӽڵ�ĸ���
	CComVariant tmpNodeValue;  //��Žڵ����ʱֵ
	bool   bFind = false; //�Ƿ��ҵ�
	
	pIParentElem->get_childNodes(&pIChildNodes); //�õ����еĺ���
	
	//�õ����ӵĸ���
	if(NULL == pIChildNodes) 
	{
		return false;
	}
	else
	{
		pIChildNodes->get_length(&size);
	}
	
	for(long i = 0; i < size; ++i)
	{
		pIChildNodes->get_item(i, &pIChildNode); //�õ�һ�����ӽڵ�
		
		if(NULL == pIChildNode)
		{
			break;
		}
		std::string szAttrName = strAttributeName.GetBuffer(strAttributeName.GetLength()); //�ڵ����Ե�����
		std::string szAttrValue;
		GetAttributeNode(pIChildNode,szAttrName,szAttrValue); //��AttrName���Ե�ֵ
		
		if ( EQUAL == strAttributeValue.Compare(szAttrValue.c_str()) )
		{
			pIChildNode->get_nodeTypedValue(&tmpNodeValue);

			pIChildNode->Release();

			USES_CONVERSION;
			strNodeValue = W2A(tmpNodeValue.bstrVal);
			
			bFind = true;
			break;
		}

		pIChildNode->Release();
	}
	
	pIChildNodes->Release();
	pIChildNodes = NULL;

	return bFind;
}

/************************************************************************
    �� �� ��: GetChildByNodeAttribute
    �������ܣ�ͨ���ڵ�����Եõ��ڵ��ֵ
    ���������pIParentElem �����׽ڵ��ָ��
			  strAttributeName ��������
			  strAttributeValue ������ֵ
    ���������N/A
    �� �� ֵ���ɹ����ҵ��Ľڵ�ָ��
			  ʧ�ܣ���
    ��    �ߣ�xzt
    ��    �ڣ�2008-03-24 20:16
    �޸ļ�¼��
************************************************************************/
IXMLDOMNode* CXMLDOMParser::GetChildByNodeAttribute(IXMLDOMNode* pIParentElem, 
													CString strAttributeName, 
													CString strAttributeValue)
{
	if( NULL == pIParentElem)
	{
		return NULL;
	}


	IXMLDOMNode*		pIChildNode		= NULL;
	IXMLDOMNodeList*	pIChildNodes	= NULL;	
	long				size =0;     //���ӽڵ�ĸ���

	pIParentElem->get_childNodes(&pIChildNodes); //�õ����еĺ���
	
	
	if( NULL == pIChildNodes) 
	{
		return NULL;	
	}
	else
	{
		pIChildNodes->get_length(&size);//�õ����ӵĸ���
	}
	
	for(long i = 0; i < size; ++i)
	{
		pIChildNodes->get_item(i, &pIChildNode); //�õ�һ�����ӽڵ�
		
		if(pIChildNode)
		{					
			std::string strAttrName = strAttributeName.GetBuffer(strAttributeName.GetLength()); //�ڵ����Ե�����
			std::string strAttrValue;
			GetAttributeNode(pIChildNode,strAttrName,strAttrValue); //��AttrName���Ե�ֵ
			if ( 0 == strAttributeValue.Compare(strAttrValue.c_str()) )
			{	
				pIChildNodes->Release();
				pIChildNodes = NULL;
				return pIChildNode;
			}

			pIChildNode->Release();
		}
	}

	pIChildNodes->Release();
	pIChildNodes = NULL;

	return NULL;
}

/************************************************************************
    �� �� ��: CheckAW
    �������ܣ����sAW��AW�����ļ��з���ڣ�������ڷ��ؽڵ��ָ��
    ���������pIParentElem�����ڵ�
	          sAW ��AW����
    ���������N/A
    �� �� ֵ������  �� ������ڷ��ؽڵ��ָ��
	          �����ڣ� Ϊ��
    ��    �ߣ�xzt
    ��    �ڣ�2008-01-25 15:02
    �޸ļ�¼��
************************************************************************/
IXMLDOMNode* CXMLDOMParser::CheckAW(IXMLDOMNode* pIParentElem, CString sAW)
{
	ASSERT(pIParentElem);
	
	IXMLDOMNode*		pIChildNode		= NULL;  
	IXMLDOMNode*        pTmpChildNode   = NULL;
	IXMLDOMNodeList*	pIChildNodes	= NULL;  
	long				size = 0;      //XML�ڵ�ĸ���
	CComBSTR			tmpNodeName;   //�ڵ������
	CComVariant			tmpNodeValue;  //�ڵ��ֵ
	CString strNodeName;               //�ڵ������
	CString strNodeValue;              //�ڵ��ֵ
	
	if (NULL == pIParentElem)
	{
		return NULL;
	}
	
	pIParentElem->get_childNodes(&pIChildNodes);//�õ����к��ӵ��б�
	if ( NULL == pIChildNodes)
	{
		return NULL;
	}
	
	pIChildNodes->get_length(&size);//�õ����ӵĸ���
	
	//������еĺ���,д�� m_pPlatformManage �ṹ
	USES_CONVERSION;
	for(long i = 0; i < size; ++i)
	{
		pIChildNodes->get_item(i, &pIChildNode);
		
		if(pIChildNode)
		{
			pIChildNode->get_nodeName(&tmpNodeName);
			
			strNodeName = W2A(tmpNodeName.m_str);
			if (EQUAL == strNodeName.Compare(ACTION_FLAG))
			{
				strNodeValue = GetAWOrLogicValue(pIChildNode);

				if ( EQUAL == strNodeValue.Compare(sAW)) 
				{
					pIChildNodes->Release();
					return pIChildNode;
				}
				else
				{
					pTmpChildNode = CheckAW(pIChildNode, sAW);
					if(NULL != pTmpChildNode)
					{
						pIChildNode->Release();
						pIChildNodes->Release();
						return pTmpChildNode;
					}
				}
				
			}

			pIChildNode->Release();
		}
	}
	
	pIChildNodes->Release();
	pIChildNodes = NULL;
	
	return NULL;	
}

/************************************************************************
    �� �� ����CheckParam
    �������ܣ����ssParam������pIParentElem�з���ڣ�������ڷ��ؽڵ��ָ��
    ���������pIParentElem ����Ҫ���ҵĽڵ�
	          sParam ������������
    ���������N/A
    �� �� ֵ������   : true
	          ������ : false
    ��    �ߣ�xzt
    ��    �ڣ�2008-03-13 19:45
    �޸ļ�¼��
************************************************************************/
bool CXMLDOMParser::CheckParam(IXMLDOMNode* pIParentElem, CString sParam)
{
	ASSERT(pIParentElem );
	
	IXMLDOMNode*		pIChildNode		= NULL;  
	IXMLDOMNode*        pTmpChildNode   = NULL;
	IXMLDOMNodeList*	pIChildNodes	= NULL;  
	long				size = 0;      //XML�ڵ�ĸ���
	CComBSTR			tmpNodeName;   //�ڵ������
	CString strNodeName;               //�ڵ������
	CString strNodeValue;
	
	pTmpChildNode = getChildByName(pIParentElem,PARAM_FLAG);
	if ( NULL == pTmpChildNode)
	{
		strNodeValue = GetParaValue(pIParentElem);
		if ( EQUAL == strNodeValue.Compare(sParam)) 
		{
			return true;
		}
		else
		{
			return false;
		}
	}
				
	pIParentElem->get_childNodes(&pIChildNodes);//�õ����к��ӵ��б�
	if ( NULL == pIChildNodes)
	{
		return false;
	}
	
	pIChildNodes->get_length(&size);//�õ����ӵĸ���
	
	//������еĺ���,д�� sArr �ṹ	
	for(long i = 0; i < size; ++i)
	{
		pIChildNodes->get_item(i, &pIChildNode);
		
		if(NULL != pIChildNode)
		{
			pIChildNode->get_nodeName(&tmpNodeName);
					
			strNodeName = tmpNodeName.m_str;
			if(EQUAL == strNodeName.Compare(PARAM_FLAG))
			{
				if(CheckParam(pIChildNode, sParam))
				{
					pIChildNode->Release();
					pIChildNodes->Release();
					return true;
				}
			}

			pIChildNode->Release();
		}
	}
	
	pIChildNodes->Release();
	pIChildNodes = NULL;
	
	return false;	
}

/************************************************************************
    �������ܣ��õ�AW����logic�ı��������û�еõ�����
    ��������� pXMLParser : xml������
	           pINode : �ڵ�����
    ���������N/A
    �� �� ֵ������
    ��    �ߣ�xzt
    ��    �ڣ�2009-10-26
    �޸ļ�¼��
************************************************************************/
CString CXMLDOMParser::GetAWOrLogicValue(IXMLDOMNode*	pINode)
{
	CString strNodeValue;
	string aAliasName = "alias";
	string sAliasValue;
	CComVariant tmpNodeValue;
	IXMLDOMNode* pTmpChildNode = NULL;


	GetAttributeNode(pINode,aAliasName, sAliasValue);//�õ�������ֵ
	if(sAliasValue.empty())//������������ڣ���õ�AW��
	{
		pTmpChildNode = getChildByName(pINode,ACTION_NAME_FLAG);
		if ( NULL == pTmpChildNode)
		{
			pTmpChildNode = getChildByName(pINode,LOGIC_NAME_FLAG);
			if(NULL == pTmpChildNode)
			{
				return "";
			}
		}

		pTmpChildNode->get_nodeTypedValue(&tmpNodeValue);
		strNodeValue = tmpNodeValue.bstrVal;
	}
	else
	{
		strNodeValue = sAliasValue.c_str();
	}

	return strNodeValue;
}

/************************************************************************
    �������ܣ��õ�para�ı��������û�еõ�����
    ��������� pXMLParser : xml������
	           pINode : �ڵ�����
    ���������N/A
    �� �� ֵ������
    ��    �ߣ�xzt
    ��    �ڣ�2009-10-26
    �޸ļ�¼��
************************************************************************/
CString CXMLDOMParser::GetParaValue(IXMLDOMNode*	pINode)
{
	CString strNodeValue;
	CComVariant tmpNodeValue;
	IXMLDOMNode* pTmpChildNode = NULL;

	pTmpChildNode = getChildByName(pINode,PARA_TCL_NAME_FLAG);
	if(NULL != pTmpChildNode)
	{
		pTmpChildNode->get_nodeTypedValue(&tmpNodeValue);
		strNodeValue = tmpNodeValue.bstrVal;
		pTmpChildNode->Release();
	}

	if(strNodeValue.IsEmpty())
	{
		pTmpChildNode = getChildByName(pINode,PARAM_NAME_FLAG);
		if(NULL != pTmpChildNode)
		{
			pTmpChildNode->get_nodeTypedValue(&tmpNodeValue);
			strNodeValue = tmpNodeValue.bstrVal;
			pTmpChildNode->Release();
		}
	}

	return strNodeValue;
}

//��ȡ�ڵ���ı�ֵ
CString CXMLDOMParser::GetNodeText(IXMLDOMNode* pNode)
{
	BSTR		bstrTmp;
	CString		strValue;

	if (CXMLDOMParser::JudgeTerminateNode(pNode))
	{
		pNode->get_text(&bstrTmp);
		strValue = (const char*)_bstr_t(bstrTmp);
		::SysFreeString(bstrTmp);
	}
	else
	{
		strValue = "";
	}
/*
	if(IsValueEmpty(strValue))
	{
		strValue = "";
	}
*/
	return strValue;
}

// ���Ԫ�����Ե�ֵ
bool CXMLDOMParser::GetAttributeValue(IXMLDOMNode*			pIParentElem,
									  const std::string&	nodeName,
									  CString&				nodeValue)
{
	CComBSTR		bstrName;
	CComVariant		value;
	HRESULT			hr;
	IXMLDOMElement*	pIElem	= NULL;
	bool			bRetVal	= false;
	hr = pIParentElem->QueryInterface(__uuidof(IXMLDOMElement), (void**)&pIElem);
	if(SUCCEEDED(hr))
	{
		bstrName = nodeName.data();
		hr = pIElem->getAttribute(bstrName, &value);
		pIElem->Release();
		pIElem = NULL;
		if(SUCCEEDED(hr))
		{
			if (VT_NULL != value.vt)
			{
				nodeValue = value.bstrVal;
			    bRetVal = true;
			}
			
		}
	}
	return bRetVal;
}

/*************************************************
  Function:       JudgeTerminateNode
  Description:    �жϵ�ǰ�ڵ��ǲ���Ҷ�ӽڵ�
  Input:          
             pXMLNode:   XML�ڵ�
  Output:         
        ��
  Return:         �����,�򷵻�true;
                  ���򷵻�false
  Others:         
*************************************************/
bool CXMLDOMParser::JudgeTerminateNode(IXMLDOMNode* pXMLNode)
{
	if ( NULL == pXMLNode)
	{
		return false;
	}

	bool nResult = true;
	long lLen = 0;
	IXMLDOMNodeList* pNodeList = NULL;
	IXMLDOMNode *pNodeChild = NULL;


	pXMLNode->get_childNodes(&pNodeList);
	if (NULL != pNodeList)
	{
		pNodeList->get_length(&lLen);
		for (int i = 0; i < lLen; i++)
		{
			pNodeList->get_item(i, &pNodeChild);

			if (NULL != pNodeChild) 
			{
				DOMNodeType nType;
				pNodeChild->get_nodeType(&nType);
				if (NODE_ELEMENT == nType)
				{
					nResult= false;
					pNodeChild->Release();
					break;
				}

				pNodeChild->Release();
			}					
		}

		pNodeList->Release();
	}
	return nResult;
}

BOOL CXMLDOMParser::ReadRegWinXml(const std::string& fileName, std::vector<RegWinInfo>& vecRWI)
{
	if (!LoadFromXMLFile(fileName))
	{
		return FALSE;
	}

	IXMLDOMElement*		pIXMLElem = NULL;
	m_pIXMLDoc->get_documentElement(&pIXMLElem);

	IXMLDOMNode* pPIDdNode =getChildByName(pIXMLElem,"PID", true);
	IXMLDOMNode* pVIDdNode =getChildByName(pIXMLElem,"VID", true);
	IXMLDOMNode* pCspNamedNode =getChildByName(pIXMLElem,"CspName", true);
	if (NULL == pPIDdNode || NULL == pVIDdNode || NULL == pCspNamedNode)
	{
		return FALSE;
	}

	IXMLDOMNodeList*	pPIDChildNodes	= NULL;
	IXMLDOMNodeList*	pVIDChildNodes	= NULL;
	IXMLDOMNodeList*	pCspChildNodes	= NULL;
	IXMLDOMNode* pIChildNode = NULL;
	CComBSTR			tmpNodeName;
	CComVariant			tmpNodeValue;
	long size1,size2,size3;
	pPIDdNode->get_childNodes(&pPIDChildNodes);//�õ����к��ӵ��б�
	pVIDdNode->get_childNodes(&pVIDChildNodes);//�õ����к��ӵ��б�
	pCspNamedNode->get_childNodes(&pCspChildNodes);//�õ����к��ӵ��б�
	if ( NULL == pPIDChildNodes || NULL == pVIDChildNodes|| NULL == pCspChildNodes)
	{
		pPIDdNode->Release();
		pVIDdNode->Release();
		pCspNamedNode->Release();
		return false;
	}

	pPIDChildNodes->get_length(&size1);//�õ����ӵĸ���
	pVIDChildNodes->get_length(&size2);//�õ����ӵĸ���
	pCspChildNodes->get_length(&size3);//�õ����ӵĸ���
	if (size1 != size2 || size1 != size3)
	{
		pPIDChildNodes->Release();
		pVIDChildNodes->Release();
		pCspChildNodes->Release();
		pPIDdNode->Release();
		pVIDdNode->Release();
		pCspNamedNode->Release();
		return FALSE;
	}

	//������еĺ���,д�� sArr �ṹ	
	for(long i = 0; i < size1; ++i)
	{
		RegWinInfo tagRWI;
		pPIDChildNodes->get_item(i, &pIChildNode);
		tagRWI.m_szPID = GetNodeText(pIChildNode).GetBuffer();
		pIChildNode->Release();

		pVIDChildNodes->get_item(i, &pIChildNode);
		tagRWI.m_szVID = GetNodeText(pIChildNode).GetBuffer();
		pIChildNode->Release();


		pCspChildNodes->get_item(i, &pIChildNode);
		tagRWI.m_szName = GetNodeText(pIChildNode).GetBuffer();
		CString strVal;
		GetAttributeValue(pIChildNode,"path",strVal);
		tagRWI.m_szPath = strVal;
		pIChildNode->Release();

		vecRWI.push_back(tagRWI);

	}

	pPIDChildNodes->Release();
	pVIDChildNodes->Release();
	pCspChildNodes->Release();
	pPIDdNode->Release();
	pVIDdNode->Release();
	pCspNamedNode->Release();

	return TRUE;
}

BOOL CXMLDOMParser::PutValue(IXMLDOMElement* pIXMLElem,std::string szName,std::string szData)
{

	IXMLDOMNode* pNode = NULL;
	pNode = getChildByName(pIXMLElem,szName.c_str(), true);
	//pNode->put_text(CComBSTR(szData.data()) );
	pNode->put_nodeTypedValue( CComVariant(szData.data()));
	//pNode->put_nodeValue(CComVariant(szData.data()));
	return TRUE;
}

void CXMLDOMParser::RemoveNodeAttr(IXMLDOMElement* pEle, const char* szAttr)
{
	IXMLDOMAttribute *pAttr = NULL;
	IXMLDOMAttribute *pOutAttr = NULL;

	pEle->getAttributeNode(CComBSTR(szAttr),&pAttr);
	
	
	HRESULT hr = pEle->removeAttributeNode(pAttr,&pOutAttr);
	
}

BOOL CXMLDOMParser::MakeSignXML(std::string szFile,
								std::string szInData, 
								std::string szOutSignData,
								std::string szHashData,
								std::string szCert,
								std::string& szxml)
{

	IXMLDOMElement* pDataNode = NULL;
	if (!LoadXml(szInData.c_str(),pDataNode))
	{
		return FALSE;
	}

	CComBSTR	tmpNodeValue2;
	pDataNode->get_xml(&tmpNodeValue2);


	if (!LoadFromXMLFile(szFile))
	{
		return FALSE;
	}

	IXMLDOMElement*		pIXMLElem = NULL;
	m_pIXMLDoc->get_documentElement(&pIXMLElem);

	PutValue(pIXMLElem,"DigestValue",szHashData);
	PutValue(pIXMLElem,"SignatureValue",szOutSignData);
	PutValue(pIXMLElem,"X509Certificate",szCert);

	IXMLDOMNode* pNode = NULL;
	pNode = getChildByName(pIXMLElem,"Object", true);
	IXMLDOMNode *outNewChild =NULL;
	pNode->appendChild(pDataNode,&outNewChild);

	//outNewChild = getChildByName(pIXMLElem,"name", true);

	//RemoveNodeAttr((IXMLDOMElement*)outNewChild,"xmlns");
	//pNode->put_nodeValue(CComVariant(szInData.data()));


	CComBSTR	tmpNodeValue;
	pIXMLElem->get_xml(&tmpNodeValue);

	CString strNodeValue;
	strNodeValue= tmpNodeValue;

	strNodeValue.Replace(" xmlns=\"\"","");

	szxml = strNodeValue.GetBuffer();


//	SaveToXMLFile(szFile);
	

	return TRUE;
}

BOOL CXMLDOMParser::LoadXml(const char* szXml, IXMLDOMElement*&	pIXMLElem)
{

	HRESULT							hr;
	bool							bRetVal	= false;
	VARIANT_BOOL					varBool;
	// �ͷ���ǰ���ĵ�
	SafeReleaseXMLDoc();
	// �������ĵ�
	hr = CoCreateInstance(	__uuidof(DOMDocument),
		NULL,
		CLSCTX_INPROC_SERVER,
		__uuidof(IXMLDOMDocument2),
		(void**)&m_pIXMLDoc);
	if(SUCCEEDED(hr))
	{
		// ����
		hr = m_pIXMLDoc->loadXML(CComBSTR(szXml), &varBool);
		if(SUCCEEDED(hr) && varBool==VARIANT_TRUE)
		{
			m_pIXMLDoc->get_documentElement(&pIXMLElem);
			bRetVal = true;
		}
	}


	// ���ʧ��,��ɾ���ĵ�,��Ϊ�ĵ�����Ϊһ��XML�ĵ�
	if(!bRetVal)
	{
		
	}

	SafeReleaseXMLDoc();
	return bRetVal;
}