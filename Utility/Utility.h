// Utility.h : Utility DLL ����ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CUtilityApp
// �йش���ʵ�ֵ���Ϣ������� Utility.cpp
//

class CUtilityApp : public CWinApp
{
public:
	CUtilityApp();

// ��д
public:
	virtual BOOL InitInstance();

	DECLARE_MESSAGE_MAP()
};
