
// IRPoterStemmer.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CIRPoterStemmerApp: 
// �йش����ʵ�֣������ IRPoterStemmer.cpp
//

class CIRPoterStemmerApp : public CWinApp
{
public:
	CIRPoterStemmerApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CIRPoterStemmerApp theApp;