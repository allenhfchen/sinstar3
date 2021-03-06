#include "stdafx.h"
#include "Minidump.h"
#include <windows.h>
#include <DbgHelp.h>
#pragma comment(lib, "DbgHelp.lib")

static TCHAR s_dumpFile[MAX_PATH]=_T("minidump.dmp");
static TCHAR s_crashReporter[MAX_PATH]={0};
static BOOL  s_showCrash = FALSE;
// 创建Dump文件  
//   
void CreateDumpFile(LPCTSTR lpstrDumpFilePathName, EXCEPTION_POINTERS *pException)
{
	// 创建Dump文件  
	//  
	HANDLE hDumpFile = CreateFile(lpstrDumpFilePathName, GENERIC_WRITE, FILE_SHARE_WRITE, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	// Dump信息  
	//  
	MINIDUMP_EXCEPTION_INFORMATION dumpInfo;
	dumpInfo.ExceptionPointers = pException;
	dumpInfo.ThreadId = GetCurrentThreadId();
	dumpInfo.ClientPointers = FALSE;

	// 写入Dump文件内容  
	//  
	MiniDumpWriteDump(GetCurrentProcess(), GetCurrentProcessId(), hDumpFile, MiniDumpNormal, &dumpInfo, NULL, NULL);

	CloseHandle(hDumpFile);
}

// 处理Unhandled Exception的回调函数  
//  
LONG WINAPI ApplicationCrashHandler(EXCEPTION_POINTERS *pException)
{
	CreateDumpFile(s_dumpFile, pException);

	{
		STARTUPINFO         si = { 0 };
		PROCESS_INFORMATION pi;
		si.cb = sizeof(si);
		si.dwFlags = STARTF_USESHOWWINDOW;
		si.wShowWindow = SW_SHOW;
		CreateProcess(s_crashReporter, NULL, NULL, NULL, FALSE, CREATE_NEW_PROCESS_GROUP, NULL, NULL, &si, &pi);
		CloseHandle(pi.hProcess);
		CloseHandle(pi.hThread);
	}
	TerminateProcess(OpenProcess(PROCESS_ALL_ACCESS,0,GetCurrentProcessId()),1);

	return EXCEPTION_EXECUTE_HANDLER;
}

void CMinidump::Enable()
{
	// 设置处理Unhandled Exception的回调函数  
	//   
	SetUnhandledExceptionFilter((LPTOP_LEVEL_EXCEPTION_FILTER)ApplicationCrashHandler);
}

void CMinidump::SetDumpFile(LPCTSTR pszDumpFile)
{
	_tcscpy_s(s_dumpFile,MAX_PATH,pszDumpFile);
}

void CMinidump::SetCrashReporter(LPCTSTR pszCrashReporter)
{
	_tcscpy_s(s_crashReporter,MAX_PATH,pszCrashReporter);
}
