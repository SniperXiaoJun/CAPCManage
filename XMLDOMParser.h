/******************************************************************************

                  ��Ȩ���� (C), 2007-2050, ��Ϊ�������޹�˾
******************************************************************************
   �� �� ��   : XMLDOMParser.h
   �� �� ��   : 1.0
   ��    ��   : xzt
   ��������   : 2007-10-10
   ����޸�   :
   ��������   : Ϊ�˸�����Ķ�дXML�ĵ�,��MSXML4.0����з�װ
				��Ҫ���һЩ�ӿڲ���ת������
				ʹ��ǰȷ���Ѿ���װ��MSXML4.0�����úû���
   �����б�   :
   �޸���ʷ   :

******************************************************************************/

#ifndef	_CXMLDOMPARSER_H
#define	_CXMLDOMPARSER_H

#include <atlbase.h>
#include <string>
#include <msxml2.h>
#include "define.h"
using namespace std;

class CXMLDOMParser
{
public:
	CXMLDOMParser()
	{
		CoInitialize(NULL);
		m_pIXMLDoc = NULL;
		m_bSave = false;
	}
	~CXMLDOMParser()
	{
		SafeReleaseXMLDoc();
		CoUninitialize();
	}

	// ����һ��XML�ĵ�,�ɹ�����true,ʧ�ܷ���false
	bool	ConstructXMLFile();

	// ���ļ�����һ��XML�ļ�,���سɹ�����true,����ʧ�ܷ���false
	bool	LoadFromXMLFile(const std::string& fileName);

	// ����XML�ļ���fileName,�ɹ�����true,ʧ�ܷ���false
	bool	SaveToXMLFile(const std::string& fileName);

	// ��ȫ�ͷ�XML�ĵ�
	void	SafeReleaseXMLDoc();

	// ���XML�ļ�����

	// ���ĵ�pIParentElemԪ�������nodeName�ڵ�,ֵΪnodeValue
	bool	AppendMemberNode(	const std::string& nodeName,
								const std::string& nodeValue,
								IXMLDOMElement*    pIParentElem,
								IXMLDOMNode**	   ppOutNewChild=NULL);

	// ���ĵ�pIParentElemԪ�������nodeName�ڵ�,ֵΪnodeValue
    bool   AppendMemberNodeNoValue(const std::string& nodeName,
							  const std::string& nodeValue,
							  IXMLDOMElement*    pIParentElem,
							  IXMLDOMNode**		 ppOutNewChild);

	// ΪԪ��pIParentElem�������
	bool	AppendAttributeNode(const std::string&	nodeName,
								const std::string&	nodeValue,
								IXMLDOMElement*		pIParentElem);



	// ��ȡpIParentElemԪ����nodeName�ڵ��ֵ

	// ��ýڵ�pIParentElem������
	bool	GetAttributeNode(IXMLDOMNode*		pIParentElem,
							 const std::string&	nodeName,
							 std::string&		nodeValue);
     
	//���ýڵ������ֵ
	bool	SetAttributeNode(IXMLDOMNode*		pIParentElem,
							 const std::string&	nodeName,
							 const std::string&		nodeValue);

	// ����ĵ�Ԫ��
	IXMLDOMElement*	GetDocElem();
	
	// ��ýڵ��nodeName����
	IXMLDOMNode*	GetChildNode(IXMLDOMNode*		pIParentElem,
								 const std::string& nodeName,
								 std::string&		nodeValue);


	bool LoadFromXMLFile(CString& fileName,CString& XSDFileName);
	int CheckXmlLoad(IXMLDOMDocument2 *pDoc);
	//���XML�ļ������ƣ�
	CString GetFileName()  
	{
		return m_fileName;
	}
	void SetFileName(CString FileName)
	{
		m_fileName = FileName;
	}

	void SetFileSave(bool bSave)
	{ 
		m_bSave =  bSave;
	}
	bool GetFileSave()
	{
		return m_bSave;
	}
	
	/////////////////////////////�����--xzt
	IXMLDOMNode* getChildByName(IXMLDOMNode* pIParentElem,CString nodeName, bool bRecursive = false);
	
	//ͨ���ڵ�����Եõ��ڵ��ֵ
	bool CXMLDOMParser::GetValueByNodeAttribute(IXMLDOMNode* pIParentElem,
											CString strAttributeName, 
											CString strAttributeValue,
											CString& strNodeValue);

	//ͨ���ڵ�����Եõ��ڵ��ֵ
	IXMLDOMNode* CXMLDOMParser::GetChildByNodeAttribute(IXMLDOMNode* pIParentElem, 
													CString strAttributeName, 
													CString strAttributeValue);

	//���sAW��AW�����ļ��з���ڣ�������ڷ��ؽڵ��ָ��
	IXMLDOMNode* CheckAW(IXMLDOMNode* pIParentElem, CString sAW);

	//���ssParam������pIParentElem�з���ڣ�������ڷ��ؽڵ��ָ��
	bool CheckParam(IXMLDOMNode* pIParentElem, CString sParam);

	CString GetAWOrLogicValue(IXMLDOMNode*	pINode);

	CString GetParaValue(IXMLDOMNode*	pINode);

	//��ȡ�ڵ���ı�ֵ
	static CString GetNodeText(IXMLDOMNode* pNode);

	// ���Ԫ�����Ե�ֵ
	static bool GetAttributeValue(IXMLDOMNode*			pIParentElem,
							      const std::string&	nodeName,
							      CString&				nodeValue);

	//�ж�xml�ڵ��Ƿ��Ǻ���
	static bool JudgeTerminateNode(IXMLDOMNode* pXMLNode);

	BOOL ReadRegWinXml(const std::string& fileName,std::vector<RegWinInfo>& vecRWI);

	//xml��ʽ��ǩ��
	BOOL MakeSignXML(std::string szFile,
		             std::string szInData, 
					 std::string szOutSignData,
					 std::string szHashData,
					 std::string szCert,
					 std::string& szxml);

	BOOL CXMLDOMParser::PutValue(IXMLDOMElement* pIXMLElem,std::string szName,std::string szData);

	
	BOOL LoadXml(const char* szXml, IXMLDOMElement*&	pIXMLElem);
	void RemoveNodeAttr(IXMLDOMElement* pEle, const char* szAttr);

protected:
private:
	IXMLDOMDocument2*				m_pIXMLDoc;		// XML�ĵ�
	CString  m_fileName;   //�ļ������ƣ�
	bool m_bSave ; //�Ƿ���Ҫ����
	

};

#endif