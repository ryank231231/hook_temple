#define _CRT_SECURE_NO_WARNINGS
#define WIN32_LEAN_AND_MEAN
#define _X86_

//include headers
#include <Windows.h>
#include "includes/detours/detours.h"
#include "function_forward.h"

//include MS Detours static lib
#ifdef _X86_
#pragma comment(lib,"includes/detours/x86/detours.lib")
#endif // _X86_

//declear some functions
long StartHook();
long EndHook();

static HANDLE (WINAPI *SysCreateFileA)(
	LPCSTR lpFileName,
	DWORD dwDesiredAccess,
	DWORD dwShareMode,
	LPSECURITY_ATTRIBUTES lpSecurityAttributes,
	DWORD dwCreationDisposition,
	DWORD dwFlagsAndAttributes,
	HANDLE hTemplateFile
	) = CreateFileA;

static HANDLE (WINAPI *SysCreateFileW)(
	LPCWSTR lpFileName,
	DWORD dwDesiredAccess,
	DWORD dwShareMode,
	LPSECURITY_ATTRIBUTES lpSecurityAttributes,
	DWORD dwCreationDisposition,
	DWORD dwFlagsAndAttributes,
	HANDLE hTemplateFile
	) = CreateFileW;

HANDLE WINAPI HookCreateFileA(
	LPCSTR lpFileName,
	DWORD dwDesiredAccess,
	DWORD dwShareMode,
	LPSECURITY_ATTRIBUTES lpSecurityAttributes,
	DWORD dwCreationDisposition,
	DWORD dwFlagsAndAttributes,
	HANDLE hTemplateFile
	);

HANDLE WINAPI HookCreateFileW(
	LPCWSTR lpFileName,
	DWORD dwDesiredAccess,
	DWORD dwShareMode,
	LPSECURITY_ATTRIBUTES lpSecurityAttributes,
	DWORD dwCreationDisposition,
	DWORD dwFlagsAndAttributes,
	HANDLE hTemplateFile
	);

void init_redirector(){		//init
	#ifdef _DEBUG
		MessageBoxW(0, L"DLL_PROCESS_ATTACH", L"", 0);
	#endif // _DEBUG
}

BOOL WINAPI DllMain(HMODULE hModule, DWORD dwReason, PVOID pvReserved)
{

	if (dwReason == DLL_PROCESS_ATTACH)
	{
		DisableThreadLibraryCalls(hModule);

		//ryan stuff.
		init_redirector();
		if (StartHook() != NO_ERROR)
		{
			MessageBoxW(0, L"HOOK_FAILED", L"", 0);
		}
	}

	else if (dwReason == DLL_PROCESS_DETACH)
	{
		if (EndHook() != NO_ERROR)
		{
			MessageBoxW(0, L"UNHOOK_FAILED", L"", 0);
		}
		Free();
	}

	return TRUE;
}

long StartHook()
{
	//开始事务
	DetourTransactionBegin();
	//更新线程信息  
	DetourUpdateThread(GetCurrentThread());
	//将拦截的函数附加到原函数的地址上,这里可以拦截多个函数。
	DetourAttach(&(PVOID&)SysCreateFileA, HookCreateFileA);
	DetourAttach(&(PVOID&)SysCreateFileW, HookCreateFileW);
	//结束事务
	return DetourTransactionCommit();

}

long EndHook()
{
	//开始事务
	DetourTransactionBegin();
	//更新线程信息 
	DetourUpdateThread(GetCurrentThread());
	//将拦截的函数从原函数的地址上解除，这里可以解除多个函数。
	DetourDetach(&(PVOID&)SysCreateFileA, HookCreateFileA);
	DetourDetach(&(PVOID&)SysCreateFileW, HookCreateFileW);
	//结束事务
	return DetourTransactionCommit();
}

HANDLE WINAPI HookCreateFileA( LPCSTR lpFileName, DWORD dwDesiredAccess, DWORD dwShareMode, LPSECURITY_ATTRIBUTES lpSecurityAttributes, DWORD dwCreationDisposition, DWORD dwFlagsAndAttributes, HANDLE hTemplateFile ){
	return SysCreateFileA(lpFileName,dwDesiredAccess,dwShareMode,lpSecurityAttributes,dwCreationDisposition,dwFlagsAndAttributes,hTemplateFile);
}

HANDLE WINAPI HookCreateFileW( LPCWSTR lpFileName, DWORD dwDesiredAccess, DWORD dwShareMode, LPSECURITY_ATTRIBUTES lpSecurityAttributes, DWORD dwCreationDisposition, DWORD dwFlagsAndAttributes, HANDLE hTemplateFile ){
	return SysCreateFileW(lpFileName,dwDesiredAccess,dwShareMode,lpSecurityAttributes,dwCreationDisposition,dwFlagsAndAttributes,hTemplateFile);
}