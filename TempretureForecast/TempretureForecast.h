
// TempretureForecast.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CTempretureForecastApp: 
// �йش����ʵ�֣������ TempretureForecast.cpp
//

class CTempretureForecastApp : public CWinApp
{
public:
	CTempretureForecastApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CTempretureForecastApp theApp;