#pragma once

#include "ReadUKey.h"
// CTestUKeyDlg �Ի���

class CTestUKeyDlg : public CDialog
{
	DECLARE_DYNAMIC(CTestUKeyDlg)

public:
	CTestUKeyDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CTestUKeyDlg();

// �Ի�������
	enum { IDD = IDD_TESTUKEY_DIALOG };

public:

	int Test2();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedBtnGetdevinfo();
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedBtnAppManage();
};
