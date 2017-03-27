
// IRPoterStemmerDlg.h : 头文件
//

#pragma once
#include "afxwin.h"


// CIRPoterStemmerDlg 对话框
class CIRPoterStemmerDlg : public CDialogEx
{
// 构造
public:
	CIRPoterStemmerDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_IRPOTERSTEMMER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
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
