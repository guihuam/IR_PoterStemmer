
// IRPoterStemmerDlg.h : ͷ�ļ�
//

#pragma once
#include "afxwin.h"


// CIRPoterStemmerDlg �Ի���
class CIRPoterStemmerDlg : public CDialogEx
{
// ����
public:
	CIRPoterStemmerDlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
	enum { IDD = IDD_IRPOTERSTEMMER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonsearch();
	CEdit m_input;
	CEdit m_output;
	CComboBox m_Num1;
	CComboBox m_Num2;
	CEdit m_Resp;
	afx_msg void OnBnClickedButtonsearch2();
	CEdit m_input2;
	afx_msg void OnBnClickedButton1();
};
