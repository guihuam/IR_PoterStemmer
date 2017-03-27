
// IRPoterStemmerDlg.cpp : ʵ���ļ�
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


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
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

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CIRPoterStemmerDlg �Ի���



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


// CIRPoterStemmerDlg ��Ϣ�������

BOOL CIRPoterStemmerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

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

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	//ShowWindow(SW_MAXIMIZE);

	// TODO:  �ڴ���Ӷ���ĳ�ʼ������
	m_Num1.AddString(_T("1"));
	m_Num1.AddString(_T("2"));
	m_Num1.AddString(_T("3"));

	m_Num2.AddString(_T("1"));
	m_Num2.AddString(_T("2"));
	m_Num2.AddString(_T("3"));
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CIRPoterStemmerDlg::OnPaint()
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
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CIRPoterStemmerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}








void CIRPoterStemmerDlg::OnBnClickedButtonsearch()
{
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	m_input2.SetSel(0, -1); m_input2.Clear(); m_input2.GetFocus();
	m_Num2.ResetContent(); m_Num2.GetFocus();
	m_output.SetSel(0,-1);m_output.Clear();m_output.GetFocus();//�ٴλ�ý���
	m_Resp.SetSel(0, -1);m_Resp.Clear();m_Resp.GetFocus();//�ٴλ�ý���

	
	

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
		MessageBox(_T("����δ�����ۣ�����ȷ����ѽ~"));
		return;
	}
	for (int t = 0; t < a.length(); t++)
	{
		if (!is_alpha(a[t]))
		{
			MessageBox(_T("������������ۣ�����ȷ����ѽ~"));
			return;
		}

	}
	if (num_1 <= 0)
	{
		MessageBox(_T("��ѯ����������������ȷ������~"));
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
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	m_input.SetSel(0, -1);m_input.Clear();m_input.GetFocus();//�ٴλ�ý���
	m_Num1.ResetContent();m_Num1.GetFocus();
	m_output.SetSel(0, -1); m_output.Clear(); m_output.GetFocus();//�ٴλ�ý���
	m_Resp.SetSel(0, -1); m_Resp.Clear(); m_Resp.GetFocus();//�ٴλ�ý���

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
		MessageBox(_T("������������������Կո����~"));
		return;
	}
	for (int t = 0; t < a0.length(); t++)
	{
		if (!is_alpha(a0[t]))
		{
			MessageBox(_T("�����е�һ��������������ۣ�����ȷ����ѽ~"));
			return;
		}
	}
	for (int t = 0; t < a1.length(); t++)
	{
		if (!is_alpha(a1[t]))
		{
			MessageBox(_T("�����еڶ���������������ۣ�����ȷ����ѽ~"));
			return;
		}
	}
	if (num_2 <= 0)
	{
		MessageBox(_T("��ѯ����������������ȷ������~"));
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
	// TODO:  �ڴ���ӿؼ�֪ͨ����������
	
	INT_PTR nRes;

	// ��ʾ��Ϣ�Ի���   
	nRes = MessageBox(_T("�������ݼ������仯��ˢ�²�ѯ�⣬�Ҵ˲�����Ҫ�ܳ�ʱ�䣬��ȷ��Ҫ�������ݼ���"), _T("���ݴ���"), MB_OKCANCEL | MB_ICONQUESTION);
	// �ж���Ϣ�Ի��򷵻�ֵ�����ΪIDCANCEL��return�������������ִ��   
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

	MessageBox(_T("�Ѿ�������ϣ�"));
}
