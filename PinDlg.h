#pragma once


// CPinDlg �Ի���

class CPinDlg : public CDialog
{
	DECLARE_DYNAMIC(CPinDlg)

public:
	CPinDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CPinDlg();

// �Ի�������
	enum { IDD = IDD_PIN_DIALOG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
};
