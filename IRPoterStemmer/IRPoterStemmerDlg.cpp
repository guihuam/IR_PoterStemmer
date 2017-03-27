
// IRPoterStemmerDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "IRPoterStemmer.h"
#include "IRPoterStemmerDlg.h"
#include "afxdialogex.h"
#include <fstream>
#include<vector>
#include<io.h>
#include<ctime>
#include <windows.h>
#include <string>
#include "Stemmer.h"
#include<iostream>
using namespace std;


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CIRPoterStemmerDlg 对话框



CIRPoterStemmerDlg::CIRPoterStemmerDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CIRPoterStemmerDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CIRPoterStemmerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDITInput, m_input);
	DDX_Control(pDX, IDC_EDITOutput, m_output);
	DDX_Control(pDX, IDC_COMBONum, m_Num1);
	DDX_Control(pDX, IDC_COMBONum2, m_Num2);
	DDX_Control(pDX, IDC_EDITRespond_time, m_Resp);
	DDX_Control(pDX, IDC_EDITInput2, m_input2);
}

BEGIN_MESSAGE_MAP(CIRPoterStemmerDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTONSearch, &CIRPoterStemmerDlg::OnBnClickedButtonsearch)
	ON_BN_CLICKED(IDC_BUTTONSearch2, &CIRPoterStemmerDlg::OnBnClickedButtonsearch2)
	ON_BN_CLICKED(IDC_BUTTON1, &CIRPoterStemmerDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CIRPoterStemmerDlg 消息处理程序

BOOL CIRPoterStemmerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	//ShowWindow(SW_MAXIMIZE);

	// TODO:  在此添加额外的初始化代码
	m_Num1.AddString(_T("1"));
	m_Num1.AddString(_T("2"));
	m_Num1.AddString(_T("3"));

	m_Num2.AddString(_T("1"));
	m_Num2.AddString(_T("2"));
	m_Num2.AddString(_T("3"));
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CIRPoterStemmerDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CIRPoterStemmerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CIRPoterStemmerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}








void CIRPoterStemmerDlg::OnBnClickedButtonsearch()
{
	// TODO:  在此添加控件通知处理程序代码
	m_input2.SetSel(0, -1); m_input2.Clear(); m_input2.GetFocus();
	m_Num2.ResetContent(); m_Num2.GetFocus();
	m_output.SetSel(0,-1);m_output.Clear();m_output.GetFocus();//再次获得焦点
	m_Resp.SetSel(0, -1);m_Resp.Clear();m_Resp.GetFocus();//再次获得焦点

	
	

	CString strTemp;
	m_input.GetWindowTextW(strTemp);


	CString num_c;
	m_Num1.GetWindowTextW(num_c);
	double dTemp = _wtof(num_c.GetString());
	int num_1 = (dTemp);

	USES_CONVERSION;
	string a(W2A(strTemp));
	Stemmer A;
	string filePath3 = "C:\\data\\A_Zdata\\a.txt";

	if (a.empty())
	{
		MessageBox(_T("单词未输入哇，请正确输入呀~"));
		return;
	}
	for (int t = 0; t < a.length(); t++)
	{
		if (!is_alpha(a[t]))
		{
			MessageBox(_T("单词输入错误哇，请正确输入呀~"));
			return;
		}

	}
	if (num_1 <= 0)
	{
		MessageBox(_T("查询次数出错啦，请正确输入哇~"));
		return;
	}

	Stemmer B;

	time_t  in_time, out_time;
	time(&in_time);

	string res_word = B.result_word(a);
	int len = filePath3.length();
	filePath3[len - 5] = res_word[0];

	vector<words_list> list = B.find_in_file(filePath3, res_word, num_1);
	time(&out_time);
	string out_str;
	for (int cur_i = 0; cur_i < num_1; cur_i++)
	{
		string word_i = B.cout_find(list, cur_i);
		out_str += list[cur_i].file_name;
		out_str += ":\r\n";
		out_str += word_i;
		out_str += "\r\n";
	}


	int resp_time = out_time - in_time;
	CString resp_t;
	resp_t.Format(_T("%d"), resp_time);

	//hli AT xidian.edu.cn OR herolee AT pmail.ntu.edu.sg

	CString cs;
	cs.Format(_T("%s"), CStringW(out_str.c_str()));

	m_output.SetWindowTextW(cs);
	m_Resp.SetWindowTextW(resp_t);
}




void CIRPoterStemmerDlg::OnBnClickedButtonsearch2()
{
	// TODO:  在此添加控件通知处理程序代码
	m_input.SetSel(0, -1);m_input.Clear();m_input.GetFocus();//再次获得焦点
	m_Num1.ResetContent();m_Num1.GetFocus();
	m_output.SetSel(0, -1); m_output.Clear(); m_output.GetFocus();//再次获得焦点
	m_Resp.SetSel(0, -1); m_Resp.Clear(); m_Resp.GetFocus();//再次获得焦点

	CString Phrase;
	m_input2.GetWindowTextW(Phrase);
	CString num_c;
	m_Num2.GetWindowTextW(num_c);
	double dTemp = _wtof(num_c.GetString());
	int num_2 = dTemp;

	string filePath3 = "C:\\data\\A_Zdata\\a.txt";
	string filePath4 = "C:\\data\\A_Zdata\\a.txt";

	CString b[2];

	CString strTmp;
	int i = 0;
	while (AfxExtractSubString(strTmp, Phrase, i, _T(' ')) && i<2)
		b[i++] = strTmp;
	USES_CONVERSION;
	string a0(W2A(b[0]));string a1(W2A(b[1]));
	if (a0.empty() || a1.empty())
	{
		MessageBox(_T("短语输入错误啦，请以空格隔开~"));
		return;
	}
	for (int t = 0; t < a0.length(); t++)
	{
		if (!is_alpha(a0[t]))
		{
			MessageBox(_T("短语中第一个单词输入错误哇，请正确输入呀~"));
			return;
		}
	}
	for (int t = 0; t < a1.length(); t++)
	{
		if (!is_alpha(a1[t]))
		{
			MessageBox(_T("短语中第二个单词输入错误哇，请正确输入呀~"));
			return;
		}
	}
	if (num_2 <= 0)
	{
		MessageBox(_T("查询次数出错啦，请正确输入哇~"));
		return;
	}

	Stemmer B;

	time_t  in_time, out_time;
	string res_worda = B.result_word(a0);
	string res_wordb = B.result_word(a1);
	int len = filePath3.length();
	filePath3[len - 5] = res_worda[0];
	filePath4[len - 5] = res_wordb[0];
	time(&in_time);
	vector<words_list> list = B.find_in_two(filePath3, filePath4, res_worda, res_wordb, num_2);
	time(&out_time);
	string out_str;
	for (int cur_i = 0; cur_i < num_2; cur_i++)
	{
		string word_i = B.cout_find(list, cur_i);
		out_str += list[cur_i].file_name;
		out_str += ":\r\n";
		out_str += word_i;
		out_str += "\r\n";
	}
	

	int resp_time = out_time - in_time;
	CString resp_t;
	resp_t.Format(_T("%d"), resp_time);	
	m_Resp.SetWindowTextW(resp_t);

	CString cs;
	cs.Format(_T("%s"), CStringW(out_str.c_str()));
	m_output.SetWindowTextW(cs);
	//hli AT xidian.edu.cn OR herolee AT pmail.ntu.edu.sg
}


void CIRPoterStemmerDlg::OnBnClickedButton1()
{
	// TODO:  在此添加控件通知处理程序代码
	
	INT_PTR nRes;

	// 显示消息对话框   
	nRes = MessageBox(_T("仅当数据集发生变化才刷新查询库，且此操作需要很长时间，您确定要处理数据集吗？"), _T("数据处理"), MB_OKCANCEL | MB_ICONQUESTION);
	// 判断消息对话框返回值。如果为IDCANCEL就return，否则继续向下执行   
	if (IDCANCEL == nRes)
		return;



	Stemmer A;

	char *filePath = "C:\\data\\IRdata";
	vector<string> files_IRdata;
	A.getFiles(filePath, files_IRdata);

	A.files_main(files_IRdata);


	char *filePath2 = "C:\\data\\A_Zdata";
	vector<string> files_AZdata;
	A.getFiles(filePath2, files_AZdata);
	A.sort_in_az(files_AZdata);

	MessageBox(_T("已经处理完毕！"));
}
