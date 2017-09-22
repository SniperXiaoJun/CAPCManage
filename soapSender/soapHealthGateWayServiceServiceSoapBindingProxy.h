/* soapHealthGateWayServiceServiceSoapBindingProxy.h
   Generated by gSOAP 2.7.7 from SOF_interface.h
   Copyright (C) 2000-2005, Robert van Engelen, Genivia Inc. All Rights Reserved.
   This part of the software is released under one of the following licenses:
   GPL, the gSOAP public license, or Genivia's license for commercial use.
*/

#ifndef soapHealthGateWayServiceServiceSoapBinding_H
#define soapHealthGateWayServiceServiceSoapBinding_H
#include "soapH.h"
class HealthGateWayServiceServiceSoapBinding
{   public:
	struct soap *soap;
	const char *endpoint;
	HealthGateWayServiceServiceSoapBinding()
	{ soap = soap_new(); endpoint = "http://localhost:8080/camanager/webservice/sOF_GenRandom"; if (soap && !soap->namespaces) { static const struct Namespace namespaces[] = 
{
	{"SOAP-ENV", "http://schemas.xmlsoap.org/soap/envelope/", "http://www.w3.org/*/soap-envelope", NULL},
	{"SOAP-ENC", "http://schemas.xmlsoap.org/soap/encoding/", "http://www.w3.org/*/soap-encoding", NULL},
	{"xsi", "http://www.w3.org/2001/XMLSchema-instance", "http://www.w3.org/*/XMLSchema-instance", NULL},
	{"xsd", "http://www.w3.org/2001/XMLSchema", "http://www.w3.org/*/XMLSchema", NULL},
	{"WS1", "http://impl.service.ws.jsca.com/", NULL, NULL},
	{NULL, NULL, NULL, NULL}
};
	soap->namespaces = namespaces; } };
	virtual ~HealthGateWayServiceServiceSoapBinding() { if (soap) { soap_destroy(soap); soap_end(soap); soap_done(soap); soap_del(soap); } };
	virtual int __WS1__SOF_USCOREVerifySignedData(WS1__SOF_USCOREVerifySignedData *WS1__SOF_USCOREVerifySignedData_, WS1__SOF_USCOREVerifySignedDataResponse *WS1__SOF_USCOREVerifySignedDataResponse_) { return soap ? soap_call___WS1__SOF_USCOREVerifySignedData(soap, endpoint, NULL, WS1__SOF_USCOREVerifySignedData_, WS1__SOF_USCOREVerifySignedDataResponse_) : SOAP_EOM; };
	virtual int __WS1__SOF_USCOREQueryCertTrustList(WS1__SOF_USCOREQueryCertTrustList *WS1__SOF_USCOREQueryCertTrustList_, WS1__SOF_USCOREQueryCertTrustListResponse *WS1__SOF_USCOREQueryCertTrustListResponse_) { return soap ? soap_call___WS1__SOF_USCOREQueryCertTrustList(soap, endpoint, NULL, WS1__SOF_USCOREQueryCertTrustList_, WS1__SOF_USCOREQueryCertTrustListResponse_) : SOAP_EOM; };
	virtual int __WS1__SOF_USCOREGetP7SignDataInfo(WS1__SOF_USCOREGetP7SignDataInfo *WS1__SOF_USCOREGetP7SignDataInfo_, WS1__SOF_USCOREGetP7SignDataInfoResponse *WS1__SOF_USCOREGetP7SignDataInfoResponse_) { return soap ? soap_call___WS1__SOF_USCOREGetP7SignDataInfo(soap, endpoint, NULL, WS1__SOF_USCOREGetP7SignDataInfo_, WS1__SOF_USCOREGetP7SignDataInfoResponse_) : SOAP_EOM; };
	virtual int __WS1__SOF_USCORESetCertTrustList(WS1__SOF_USCORESetCertTrustList *WS1__SOF_USCORESetCertTrustList_, WS1__SOF_USCORESetCertTrustListResponse *WS1__SOF_USCORESetCertTrustListResponse_) { return soap ? soap_call___WS1__SOF_USCORESetCertTrustList(soap, endpoint, NULL, WS1__SOF_USCORESetCertTrustList_, WS1__SOF_USCORESetCertTrustListResponse_) : SOAP_EOM; };
	virtual int __WS1__SOF_USCOREVerifySignedDataByP7(WS1__SOF_USCOREVerifySignedDataByP7 *WS1__SOF_USCOREVerifySignedDataByP7_, WS1__SOF_USCOREVerifySignedDataByP7Response *WS1__SOF_USCOREVerifySignedDataByP7Response_) { return soap ? soap_call___WS1__SOF_USCOREVerifySignedDataByP7(soap, endpoint, NULL, WS1__SOF_USCOREVerifySignedDataByP7_, WS1__SOF_USCOREVerifySignedDataByP7Response_) : SOAP_EOM; };
	virtual int __WS1__SOF_USCOREPubKeyEncrypt(WS1__SOF_USCOREPubKeyEncrypt *WS1__SOF_USCOREPubKeyEncrypt_, WS1__SOF_USCOREPubKeyEncryptResponse *WS1__SOF_USCOREPubKeyEncryptResponse_) { return soap ? soap_call___WS1__SOF_USCOREPubKeyEncrypt(soap, endpoint, NULL, WS1__SOF_USCOREPubKeyEncrypt_, WS1__SOF_USCOREPubKeyEncryptResponse_) : SOAP_EOM; };
	virtual int __WS1__SOF_USCOREVerifyTimeStamp(WS1__SOF_USCOREVerifyTimeStamp *WS1__SOF_USCOREVerifyTimeStamp_, WS1__SOF_USCOREVerifyTimeStampResponse *WS1__SOF_USCOREVerifyTimeStampResponse_) { return soap ? soap_call___WS1__SOF_USCOREVerifyTimeStamp(soap, endpoint, NULL, WS1__SOF_USCOREVerifyTimeStamp_, WS1__SOF_USCOREVerifyTimeStampResponse_) : SOAP_EOM; };
	virtual int __WS1__SOF_USCOREVerifySignedFile(WS1__SOF_USCOREVerifySignedFile *WS1__SOF_USCOREVerifySignedFile_, WS1__SOF_USCOREVerifySignedFileResponse *WS1__SOF_USCOREVerifySignedFileResponse_) { return soap ? soap_call___WS1__SOF_USCOREVerifySignedFile(soap, endpoint, NULL, WS1__SOF_USCOREVerifySignedFile_, WS1__SOF_USCOREVerifySignedFileResponse_) : SOAP_EOM; };
	virtual int __WS1__SOF_USCOREGetCertInfoByOid(WS1__SOF_USCOREGetCertInfoByOid *WS1__SOF_USCOREGetCertInfoByOid_, WS1__SOF_USCOREGetCertInfoByOidResponse *WS1__SOF_USCOREGetCertInfoByOidResponse_) { return soap ? soap_call___WS1__SOF_USCOREGetCertInfoByOid(soap, endpoint, NULL, WS1__SOF_USCOREGetCertInfoByOid_, WS1__SOF_USCOREGetCertInfoByOidResponse_) : SOAP_EOM; };
	virtual int __WS1__SOF_USCOREGetServerCertificate(WS1__SOF_USCOREGetServerCertificate *WS1__SOF_USCOREGetServerCertificate_, WS1__SOF_USCOREGetServerCertificateResponse *WS1__SOF_USCOREGetServerCertificateResponse_) { return soap ? soap_call___WS1__SOF_USCOREGetServerCertificate(soap, endpoint, NULL, WS1__SOF_USCOREGetServerCertificate_, WS1__SOF_USCOREGetServerCertificateResponse_) : SOAP_EOM; };
	virtual int __WS1__SOF_USCOREDelCertTrustList(WS1__SOF_USCOREDelCertTrustList *WS1__SOF_USCOREDelCertTrustList_, WS1__SOF_USCOREDelCertTrustListResponse *WS1__SOF_USCOREDelCertTrustListResponse_) { return soap ? soap_call___WS1__SOF_USCOREDelCertTrustList(soap, endpoint, NULL, WS1__SOF_USCOREDelCertTrustList_, WS1__SOF_USCOREDelCertTrustListResponse_) : SOAP_EOM; };
	virtual int __WS1__SOF_USCOREGetXMLSignatureInfo(WS1__SOF_USCOREGetXMLSignatureInfo *WS1__SOF_USCOREGetXMLSignatureInfo_, WS1__SOF_USCOREGetXMLSignatureInfoResponse *WS1__SOF_USCOREGetXMLSignatureInfoResponse_) { return soap ? soap_call___WS1__SOF_USCOREGetXMLSignatureInfo(soap, endpoint, NULL, WS1__SOF_USCOREGetXMLSignatureInfo_, WS1__SOF_USCOREGetXMLSignatureInfoResponse_) : SOAP_EOM; };
	virtual int __WS1__SOF_USCORESignData(WS1__SOF_USCORESignData *WS1__SOF_USCORESignData_, WS1__SOF_USCORESignDataResponse *WS1__SOF_USCORESignDataResponse_) { return soap ? soap_call___WS1__SOF_USCORESignData(soap, endpoint, NULL, WS1__SOF_USCORESignData_, WS1__SOF_USCORESignDataResponse_) : SOAP_EOM; };
	virtual int __WS1__SOF_USCOREVerifySignedDataXML(WS1__SOF_USCOREVerifySignedDataXML *WS1__SOF_USCOREVerifySignedDataXML_, WS1__SOF_USCOREVerifySignedDataXMLResponse *WS1__SOF_USCOREVerifySignedDataXMLResponse_) { return soap ? soap_call___WS1__SOF_USCOREVerifySignedDataXML(soap, endpoint, NULL, WS1__SOF_USCOREVerifySignedDataXML_, WS1__SOF_USCOREVerifySignedDataXMLResponse_) : SOAP_EOM; };
	virtual int __WS1__SOF_USCORESignFile(WS1__SOF_USCORESignFile *WS1__SOF_USCORESignFile_, WS1__SOF_USCORESignFileResponse *WS1__SOF_USCORESignFileResponse_) { return soap ? soap_call___WS1__SOF_USCORESignFile(soap, endpoint, NULL, WS1__SOF_USCORESignFile_, WS1__SOF_USCORESignFileResponse_) : SOAP_EOM; };
	virtual int __WS1__SOF_USCOREGetInstance(WS1__SOF_USCOREGetInstance *WS1__SOF_USCOREGetInstance_, WS1__SOF_USCOREGetInstanceResponse *WS1__SOF_USCOREGetInstanceResponse_) { return soap ? soap_call___WS1__SOF_USCOREGetInstance(soap, endpoint, NULL, WS1__SOF_USCOREGetInstance_, WS1__SOF_USCOREGetInstanceResponse_) : SOAP_EOM; };
	virtual int __WS1__SOF_USCOREPriKeyDecrypt(WS1__SOF_USCOREPriKeyDecrypt *WS1__SOF_USCOREPriKeyDecrypt_, WS1__SOF_USCOREPriKeyDecryptResponse *WS1__SOF_USCOREPriKeyDecryptResponse_) { return soap ? soap_call___WS1__SOF_USCOREPriKeyDecrypt(soap, endpoint, NULL, WS1__SOF_USCOREPriKeyDecrypt_, WS1__SOF_USCOREPriKeyDecryptResponse_) : SOAP_EOM; };
	virtual int __WS1__SOF_USCOREGenRandom(WS1__SOF_USCOREGenRandom *WS1__SOF_USCOREGenRandom_, WS1__SOF_USCOREGenRandomResponse *WS1__SOF_USCOREGenRandomResponse_) { return soap ? soap_call___WS1__SOF_USCOREGenRandom(soap, endpoint, NULL, WS1__SOF_USCOREGenRandom_, WS1__SOF_USCOREGenRandomResponse_) : SOAP_EOM; };
	virtual int __WS1__SOF_USCOREGetSignMethod(WS1__SOF_USCOREGetSignMethod *WS1__SOF_USCOREGetSignMethod_, WS1__SOF_USCOREGetSignMethodResponse *WS1__SOF_USCOREGetSignMethodResponse_) { return soap ? soap_call___WS1__SOF_USCOREGetSignMethod(soap, endpoint, NULL, WS1__SOF_USCOREGetSignMethod_, WS1__SOF_USCOREGetSignMethodResponse_) : SOAP_EOM; };
	virtual int __WS1__SOF_USCORESetWebAppName(WS1__SOF_USCORESetWebAppName *WS1__SOF_USCORESetWebAppName_, WS1__SOF_USCORESetWebAppNameResponse *WS1__SOF_USCORESetWebAppNameResponse_) { return soap ? soap_call___WS1__SOF_USCORESetWebAppName(soap, endpoint, NULL, WS1__SOF_USCORESetWebAppName_, WS1__SOF_USCORESetWebAppNameResponse_) : SOAP_EOM; };
	virtual int __WS1__SOF_USCORESetEncryptMethod(WS1__SOF_USCORESetEncryptMethod *WS1__SOF_USCORESetEncryptMethod_, WS1__SOF_USCORESetEncryptMethodResponse *WS1__SOF_USCORESetEncryptMethodResponse_) { return soap ? soap_call___WS1__SOF_USCORESetEncryptMethod(soap, endpoint, NULL, WS1__SOF_USCORESetEncryptMethod_, WS1__SOF_USCORESetEncryptMethodResponse_) : SOAP_EOM; };
	virtual int __WS1__SOF_USCORECreateTimeStampRequest(WS1__SOF_USCORECreateTimeStampRequest *WS1__SOF_USCORECreateTimeStampRequest_, WS1__SOF_USCORECreateTimeStampRequestResponse *WS1__SOF_USCORECreateTimeStampRequestResponse_) { return soap ? soap_call___WS1__SOF_USCORECreateTimeStampRequest(soap, endpoint, NULL, WS1__SOF_USCORECreateTimeStampRequest_, WS1__SOF_USCORECreateTimeStampRequestResponse_) : SOAP_EOM; };
	virtual int __WS1__SOF_USCOREGetEncryptMethod(WS1__SOF_USCOREGetEncryptMethod *WS1__SOF_USCOREGetEncryptMethod_, WS1__SOF_USCOREGetEncryptMethodResponse *WS1__SOF_USCOREGetEncryptMethodResponse_) { return soap ? soap_call___WS1__SOF_USCOREGetEncryptMethod(soap, endpoint, NULL, WS1__SOF_USCOREGetEncryptMethod_, WS1__SOF_USCOREGetEncryptMethodResponse_) : SOAP_EOM; };
	virtual int __WS1__SOF_USCORECreateTimeStampResponse(WS1__SOF_USCORECreateTimeStampResponse *WS1__SOF_USCORECreateTimeStampResponse_, WS1__SOF_USCORECreateTimeStampResponseResponse *WS1__SOF_USCORECreateTimeStampResponseResponse_) { return soap ? soap_call___WS1__SOF_USCORECreateTimeStampResponse(soap, endpoint, NULL, WS1__SOF_USCORECreateTimeStampResponse_, WS1__SOF_USCORECreateTimeStampResponseResponse_) : SOAP_EOM; };
	virtual int __WS1__SOF_USCOREValidateCert(WS1__SOF_USCOREValidateCert *WS1__SOF_USCOREValidateCert_, WS1__SOF_USCOREValidateCertResponse *WS1__SOF_USCOREValidateCertResponse_) { return soap ? soap_call___WS1__SOF_USCOREValidateCert(soap, endpoint, NULL, WS1__SOF_USCOREValidateCert_, WS1__SOF_USCOREValidateCertResponse_) : SOAP_EOM; };
	virtual int __WS1__DeleteFile(WS1__DeleteFile *WS1__DeleteFile_, WS1__DeleteFileResponse *WS1__DeleteFileResponse_) { return soap ? soap_call___WS1__DeleteFile(soap, endpoint, NULL, WS1__DeleteFile_, WS1__DeleteFileResponse_) : SOAP_EOM; };
	virtual int __WS1__GetFile(WS1__GetFile *WS1__GetFile_, WS1__GetFileResponse *WS1__GetFileResponse_) { return soap ? soap_call___WS1__GetFile(soap, endpoint, NULL, WS1__GetFile_, WS1__GetFileResponse_) : SOAP_EOM; };
	virtual int __WS1__SOF_USCOREDecryptFile(WS1__SOF_USCOREDecryptFile *WS1__SOF_USCOREDecryptFile_, WS1__SOF_USCOREDecryptFileResponse *WS1__SOF_USCOREDecryptFileResponse_) { return soap ? soap_call___WS1__SOF_USCOREDecryptFile(soap, endpoint, NULL, WS1__SOF_USCOREDecryptFile_, WS1__SOF_USCOREDecryptFileResponse_) : SOAP_EOM; };
	virtual int __WS1__SOF_USCORESetSignMethod(WS1__SOF_USCORESetSignMethod *WS1__SOF_USCORESetSignMethod_, WS1__SOF_USCORESetSignMethodResponse *WS1__SOF_USCORESetSignMethodResponse_) { return soap ? soap_call___WS1__SOF_USCORESetSignMethod(soap, endpoint, NULL, WS1__SOF_USCORESetSignMethod_, WS1__SOF_USCORESetSignMethodResponse_) : SOAP_EOM; };
	virtual int __WS1__SOF_USCOREGetTimeStampInfo(WS1__SOF_USCOREGetTimeStampInfo *WS1__SOF_USCOREGetTimeStampInfo_, WS1__SOF_USCOREGetTimeStampInfoResponse *WS1__SOF_USCOREGetTimeStampInfoResponse_) { return soap ? soap_call___WS1__SOF_USCOREGetTimeStampInfo(soap, endpoint, NULL, WS1__SOF_USCOREGetTimeStampInfo_, WS1__SOF_USCOREGetTimeStampInfoResponse_) : SOAP_EOM; };
	virtual int __WS1__SOF_USCOREEncryptFile(WS1__SOF_USCOREEncryptFile *WS1__SOF_USCOREEncryptFile_, WS1__SOF_USCOREEncryptFileResponse *WS1__SOF_USCOREEncryptFileResponse_) { return soap ? soap_call___WS1__SOF_USCOREEncryptFile(soap, endpoint, NULL, WS1__SOF_USCOREEncryptFile_, WS1__SOF_USCOREEncryptFileResponse_) : SOAP_EOM; };
	virtual int __WS1__SOF_USCORESignDataByP7(WS1__SOF_USCORESignDataByP7 *WS1__SOF_USCORESignDataByP7_, WS1__SOF_USCORESignDataByP7Response *WS1__SOF_USCORESignDataByP7Response_) { return soap ? soap_call___WS1__SOF_USCORESignDataByP7(soap, endpoint, NULL, WS1__SOF_USCORESignDataByP7_, WS1__SOF_USCORESignDataByP7Response_) : SOAP_EOM; };
	virtual int __WS1__SOF_USCOREDecryptData(WS1__SOF_USCOREDecryptData *WS1__SOF_USCOREDecryptData_, WS1__SOF_USCOREDecryptDataResponse *WS1__SOF_USCOREDecryptDataResponse_) { return soap ? soap_call___WS1__SOF_USCOREDecryptData(soap, endpoint, NULL, WS1__SOF_USCOREDecryptData_, WS1__SOF_USCOREDecryptDataResponse_) : SOAP_EOM; };
	virtual int __WS1__SOF_USCORESignDataXML(WS1__SOF_USCORESignDataXML *WS1__SOF_USCORESignDataXML_, WS1__SOF_USCORESignDataXMLResponse *WS1__SOF_USCORESignDataXMLResponse_) { return soap ? soap_call___WS1__SOF_USCORESignDataXML(soap, endpoint, NULL, WS1__SOF_USCORESignDataXML_, WS1__SOF_USCORESignDataXMLResponse_) : SOAP_EOM; };
	virtual int __WS1__SOF_USCOREGetCertInfo(WS1__SOF_USCOREGetCertInfo *WS1__SOF_USCOREGetCertInfo_, WS1__SOF_USCOREGetCertInfoResponse *WS1__SOF_USCOREGetCertInfoResponse_) { return soap ? soap_call___WS1__SOF_USCOREGetCertInfo(soap, endpoint, NULL, WS1__SOF_USCOREGetCertInfo_, WS1__SOF_USCOREGetCertInfoResponse_) : SOAP_EOM; };
	virtual int __WS1__SOF_USCOREQueryCertTrustListAltNames(WS1__SOF_USCOREQueryCertTrustListAltNames *WS1__SOF_USCOREQueryCertTrustListAltNames_, WS1__SOF_USCOREQueryCertTrustListAltNamesResponse *WS1__SOF_USCOREQueryCertTrustListAltNamesResponse_) { return soap ? soap_call___WS1__SOF_USCOREQueryCertTrustListAltNames(soap, endpoint, NULL, WS1__SOF_USCOREQueryCertTrustListAltNames_, WS1__SOF_USCOREQueryCertTrustListAltNamesResponse_) : SOAP_EOM; };
	virtual int __WS1__SOF_USCOREEncryptData(WS1__SOF_USCOREEncryptData *WS1__SOF_USCOREEncryptData_, WS1__SOF_USCOREEncryptDataResponse *WS1__SOF_USCOREEncryptDataResponse_) { return soap ? soap_call___WS1__SOF_USCOREEncryptData(soap, endpoint, NULL, WS1__SOF_USCOREEncryptData_, WS1__SOF_USCOREEncryptDataResponse_) : SOAP_EOM; };
};
#endif