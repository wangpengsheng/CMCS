// Win32_Test.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "Win32_Test.h"
#include "../Motion_Win32/MotionFactory.h"
#include "../System_Win32/Config.h"
#include <direct.h>
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// Ψһ��Ӧ�ó������

CWinApp theApp;

using namespace std;

int main()
{
	auto _motion =MOTION_FACTORY;
	auto _config = SYSCCONFIG;


	//_getchar_nolock();
	return 0;
}
