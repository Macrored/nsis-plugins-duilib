#ifndef UNICODE
#define UNICODE
#endif // !UNICODE

#ifndef _UNICODE
#define _UNICODE
#endif // !__UNICODE

#include <iostream>
#include <sstream>
#include <string>
// #include <vld.h>
#include <windows.h>
#include <nsis/pluginapi.h> // nsis plugin
#include "360Safe.h"

typedef struct
{
	extra_parameters *extra;
	int addr;
} EXECDATA;

HINSTANCE g_hInstance;
HWND g_hwndParent;

// To work with Unicode version of NSIS, please use TCHAR-type
// functions for accessing the variables and the stack.

// 线程调度函数
DWORD WINAPI ExecThreadProc(LPVOID lpParam)
{
	EXECDATA *param = (EXECDATA*)lpParam;

	std::wostringstream debug_str;
	debug_str << TEXT("[MYDLL@exec:") << __LINE__ << TEXT("] ") << TEXT("Enter ExecThreadProc functon of dll success，thread start! NSIS function address:") << param->addr << std::endl;
	OutputDebugString(debug_str.str().c_str());

	return param->extra->ExecuteCodeSegment(param->addr, NULL);
}

// 从寄存器中获取nsis的函数地址
bool GetNsisFuncAddr(int varNum, int *funAddr) {
	// 从$Rx获取函数地址，转为int型
	LPCTSTR rxStr = getuservariable(varNum);
	if (rxStr == NULL) {
		return false;
	}

	int rxInt = _tstoi(rxStr);
	if (rxInt <= 0) {
		return false;
	}

	*funAddr = rxInt;
	return true;
}

// 创建线程调用nsis函数
bool BgCreateThreadCallNsisFunc(EXECDATA *execParam, HANDLE *hThread) {
	DWORD tid;
	HANDLE resThread = CreateThread(NULL, 0, ExecThreadProc, execParam, 0, &tid);
	if (resThread) {
		SetThreadPriority(resThread, THREAD_PRIORITY_NORMAL);
		
		std::wostringstream debug_str;
		debug_str << TEXT("[MYDLL@exec:") << __LINE__ << TEXT("] ") << TEXT("Create thread ID:") << resThread << TEXT("(")
			<< (int)resThread << TEXT(")") << std::endl;
		OutputDebugString(debug_str.str().c_str());

		// WaitForSingleObject(resThread, INFINITE);
		*hThread = resThread;
		// *hThread = NULL;
		return true;
	}
	else {
		// extra->ExecuteCodeSegment(execParam.addr, NULL);
		*hThread = NULL;
	}
	return false;
}

extern "C" void __declspec(dllexport) Exec(HWND hwndParent, int string_size,
	LPTSTR variables, stack_t **stacktop,
	extra_parameters *extra, ...)
{
	EXDLL_INIT();
	g_hwndParent = hwndParent;

	{
		std::wostringstream debug_str;
		debug_str << TEXT("[MYDLL@exec:") << __LINE__ << TEXT("] ") << TEXT("Enter Exec function of dll success! NSIS handle:") 
			<< hwndParent << TEXT(" string size:") << string_size << std::endl;
		OutputDebugString(debug_str.str().c_str());

		// 分别从$R0 $R1 $R2三个寄存器中取nsis函数地址，用后台线程启动
		HANDLE hThread1 = NULL, hThread2 = NULL, hThread3 = NULL;
		EXECDATA execData1, execData2, execData3;
		int funAddr;
		if (GetNsisFuncAddr(INST_R0, &funAddr)) {
			std::wostringstream debug_str;
			debug_str << TEXT("[MYDLL@exec:") << __LINE__ << TEXT("] ") << TEXT("Exec function get $R0 success! $R0:") << funAddr - 1 << std::endl;
			OutputDebugString(debug_str.str().c_str());
			execData1.extra = extra;
			execData1.addr = funAddr - 1;
			BgCreateThreadCallNsisFunc(&execData1, &hThread1);
		}

		if (GetNsisFuncAddr(INST_R1, &funAddr)) {
			std::wostringstream debug_str;
			debug_str << TEXT("[MYDLL@exec:") << __LINE__ << TEXT("] ") << TEXT("Exec function get $R1 success! $R1:") << funAddr - 1 << std::endl;
			OutputDebugString(debug_str.str().c_str());
			execData2.extra = extra;
			execData2.addr = funAddr - 1;
			BgCreateThreadCallNsisFunc(&execData2, &hThread2);
		}

		if (GetNsisFuncAddr(INST_R2, &funAddr)) {
			std::wostringstream debug_str;
			debug_str << TEXT("[MYDLL@exec:") << __LINE__ << TEXT("] ") << TEXT("Exec function get $R2 success! $R2:") << funAddr - 1 << std::endl;
			OutputDebugString(debug_str.str().c_str());
			execData3.extra = extra;
			execData3.addr = funAddr - 1;
			BgCreateThreadCallNsisFunc(&execData3, &hThread3);
		}

		// 等待线程执行结束
		DWORD exitCode;
		BOOL res = GetExitCodeThread(hThread1, &exitCode);
		if (exitCode == STILL_ACTIVE) {
			std::wostringstream debug_str;
			debug_str << TEXT("[MYDLL@exec:") << __LINE__ << TEXT("] ") << TEXT("Exec function wait thread1 to exit. thread1:") << hThread1 << std::endl;
			OutputDebugString(debug_str.str().c_str());
			WaitForSingleObject(hThread1, INFINITE);
		}
		GetExitCodeThread(hThread2, &exitCode);
		if (exitCode == STILL_ACTIVE) {
			std::wostringstream debug_str;
			debug_str << TEXT("[MYDLL@exec:") << __LINE__ << TEXT("] ") << TEXT("Exec function wait thread2 to exit. thread2:") << hThread2 << std::endl;
			OutputDebugString(debug_str.str().c_str());
			WaitForSingleObject(hThread2, INFINITE);
		}
		GetExitCodeThread(hThread3, &exitCode);
		if (exitCode == STILL_ACTIVE) {
			std::wostringstream debug_str;
			debug_str << TEXT("[MYDLL@exec:") << __LINE__ << TEXT("] ") << TEXT("Exec function wait thread3 to exit. thread3:") << hThread3 << std::endl;
			OutputDebugString(debug_str.str().c_str());
			WaitForSingleObject(hThread3, INFINITE);
		}

		CloseHandle(hThread1);
		CloseHandle(hThread2);
		CloseHandle(hThread3);
	}
}

extern "C" void __declspec(dllexport) Frame360(HWND hwndParent, int string_size,
	LPTSTR variables, stack_t **stacktop,
	extra_parameters *extra, ...)
{
	EXDLL_INIT();
	g_hwndParent = hwndParent;
	{
		MainFrame360(g_hInstance);
	}
}


BOOL WINAPI DllMain(HINSTANCE hInst, ULONG ul_reason_for_call, LPVOID lpReserved)
{
	g_hInstance = hInst;
	return TRUE;
}
