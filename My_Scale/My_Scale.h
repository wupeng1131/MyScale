
// My_Scale.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CMy_ScaleApp:
// �йش����ʵ�֣������ My_Scale.cpp
//

class CMy_ScaleApp : public CWinApp
{
public:
	CMy_ScaleApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CMy_ScaleApp theApp;