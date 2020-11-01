//for function forward

#define ALCDECL EXTERNC NAKED void __cdecl
#define EXTERNC extern "C"
#define NAKED __declspec(naked)
#define EXPORT __declspec(dllexport)

#define ALCPP EXPORT NAKED
#define ALSTD EXTERNC EXPORT NAKED void __stdcall
#define ALCFAST EXTERNC EXPORT NAKED void __fastcall

HMODULE m_hModule = NULL;	// 原始模块句柄
DWORD m_dwReturn[15] = {0};	// 原始函数返回地址

//from version.dll

#pragma comment(linker, "/EXPORT:GetFileVersionInfoA=_redirector_GetFileVersionInfoA,@1")
#pragma comment(linker, "/EXPORT:GetFileVersionInfoByHandle=_redirector_GetFileVersionInfoByHandle,@2")
#pragma comment(linker, "/EXPORT:GetFileVersionInfoExW=_redirector_GetFileVersionInfoExW,@3")
#pragma comment(linker, "/EXPORT:GetFileVersionInfoSizeA=_redirector_GetFileVersionInfoSizeA,@4")
#pragma comment(linker, "/EXPORT:GetFileVersionInfoSizeExW=_redirector_GetFileVersionInfoSizeExW,@5")
#pragma comment(linker, "/EXPORT:GetFileVersionInfoSizeW=_redirector_GetFileVersionInfoSizeW,@6")
#pragma comment(linker, "/EXPORT:GetFileVersionInfoW=_redirector_GetFileVersionInfoW,@7")
#pragma comment(linker, "/EXPORT:VerFindFileA=_redirector_VerFindFileA,@8")
#pragma comment(linker, "/EXPORT:VerFindFileW=_redirector_VerFindFileW,@9")
#pragma comment(linker, "/EXPORT:VerInstallFileA=_redirector_VerInstallFileA,@10")
#pragma comment(linker, "/EXPORT:VerInstallFileW=_redirector_VerInstallFileW,@11")
#pragma comment(linker, "/EXPORT:VerLanguageNameA=_redirector_VerLanguageNameA,@12")
#pragma comment(linker, "/EXPORT:VerLanguageNameW=_redirector_VerLanguageNameW,@13")
#pragma comment(linker, "/EXPORT:VerQueryValueA=_redirector_VerQueryValueA,@14")
#pragma comment(linker, "/EXPORT:VerQueryValueW=_redirector_VerQueryValueW,@15")

// 加载原始模块
inline BOOL WINAPI Load()
{
	TCHAR tzPath[MAX_PATH];
	TCHAR tzTemp[MAX_PATH * 2];

	GetSystemDirectory(tzPath, MAX_PATH);
	lstrcat(tzPath, TEXT("\\version"));
	m_hModule = LoadLibrary(tzPath);
	if (m_hModule == NULL)
	{
		wsprintf(tzTemp, TEXT("无法加载 %s，程序无法正常运行。"), tzPath);
		MessageBox(NULL, tzTemp, TEXT("redirector"), MB_ICONSTOP);
	}

	return (m_hModule != NULL);	
}

// 释放原始模块
inline VOID WINAPI Free()
{
	if (m_hModule)
	{
		FreeLibrary(m_hModule);
	}
}

FARPROC WINAPI GetAddress(PCSTR pszProcName)
{
	FARPROC fpAddress;
	CHAR szProcName[16];
	TCHAR tzTemp[MAX_PATH];

	if (m_hModule == NULL)
	{
		if (Load() == FALSE)
		{
			ExitProcess(-1);
		}
	}

	fpAddress = GetProcAddress(m_hModule, pszProcName);
	if (fpAddress == NULL)
	{
		if (HIWORD(pszProcName) == 0)
		{
			wsprintf(szProcName, "%d", pszProcName);
			pszProcName = szProcName;
		}

		wsprintf(tzTemp, TEXT("无法找到函数 %hs，程序无法正常运行。"), pszProcName);
		MessageBox(NULL, tzTemp, TEXT("redirector"), MB_ICONSTOP);
		ExitProcess(-2);
	}

	return fpAddress;
}

// 导出函数
ALCDECL redirector_GetFileVersionInfoA(void)
{
	// 保存返回地址
	__asm POP m_dwReturn[0 * TYPE long];

	// 调用原始函数
	GetAddress("GetFileVersionInfoA")();

	// 转跳到返回地址
	__asm JMP m_dwReturn[0 * TYPE long];
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 导出函数
ALCDECL redirector_GetFileVersionInfoByHandle(void)
{
	// 保存返回地址
	__asm POP m_dwReturn[1 * TYPE long];

	// 调用原始函数
	GetAddress("GetFileVersionInfoByHandle")();

	// 转跳到返回地址
	__asm JMP m_dwReturn[1 * TYPE long];
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 导出函数
ALCDECL redirector_GetFileVersionInfoExW(void)
{
	// 保存返回地址
	__asm POP m_dwReturn[2 * TYPE long];

	// 调用原始函数
	GetAddress("GetFileVersionInfoExW")();

	// 转跳到返回地址
	__asm JMP m_dwReturn[2 * TYPE long];
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 导出函数
ALCDECL redirector_GetFileVersionInfoSizeA(void)
{
	// 保存返回地址
	__asm POP m_dwReturn[3 * TYPE long];

	// 调用原始函数
	GetAddress("GetFileVersionInfoSizeA")();

	// 转跳到返回地址
	__asm JMP m_dwReturn[3 * TYPE long];
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 导出函数
ALCDECL redirector_GetFileVersionInfoSizeExW(void)
{
	// 保存返回地址
	__asm POP m_dwReturn[4 * TYPE long];

	// 调用原始函数
	GetAddress("GetFileVersionInfoSizeExW")();

	// 转跳到返回地址
	__asm JMP m_dwReturn[4 * TYPE long];
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 导出函数
ALCDECL redirector_GetFileVersionInfoSizeW(void)
{
	// 保存返回地址
	__asm POP m_dwReturn[5 * TYPE long];

	// 调用原始函数
	GetAddress("GetFileVersionInfoSizeW")();

	// 转跳到返回地址
	__asm JMP m_dwReturn[5 * TYPE long];
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 导出函数
ALCDECL redirector_GetFileVersionInfoW(void)
{
	// 保存返回地址
	__asm POP m_dwReturn[6 * TYPE long];

	// 调用原始函数
	GetAddress("GetFileVersionInfoW")();

	// 转跳到返回地址
	__asm JMP m_dwReturn[6 * TYPE long];
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 导出函数
ALCDECL redirector_VerFindFileA(void)
{
	// 保存返回地址
	__asm POP m_dwReturn[7 * TYPE long];

	// 调用原始函数
	GetAddress("VerFindFileA")();

	// 转跳到返回地址
	__asm JMP m_dwReturn[7 * TYPE long];
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 导出函数
ALCDECL redirector_VerFindFileW(void)
{
	// 保存返回地址
	__asm POP m_dwReturn[8 * TYPE long];

	// 调用原始函数
	GetAddress("VerFindFileW")();

	// 转跳到返回地址
	__asm JMP m_dwReturn[8 * TYPE long];
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 导出函数
ALCDECL redirector_VerInstallFileA(void)
{
	// 保存返回地址
	__asm POP m_dwReturn[9 * TYPE long];

	// 调用原始函数
	GetAddress("VerInstallFileA")();

	// 转跳到返回地址
	__asm JMP m_dwReturn[9 * TYPE long];
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 导出函数
ALCDECL redirector_VerInstallFileW(void)
{
	// 保存返回地址
	__asm POP m_dwReturn[10 * TYPE long];

	// 调用原始函数
	GetAddress("VerInstallFileW")();

	// 转跳到返回地址
	__asm JMP m_dwReturn[10 * TYPE long];
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 导出函数
ALCDECL redirector_VerLanguageNameA(void)
{
	// 保存返回地址
	__asm POP m_dwReturn[11 * TYPE long];

	// 调用原始函数
	GetAddress("VerLanguageNameA")();

	// 转跳到返回地址
	__asm JMP m_dwReturn[11 * TYPE long];
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 导出函数
ALCDECL redirector_VerLanguageNameW(void)
{
	// 保存返回地址
	__asm POP m_dwReturn[12 * TYPE long];

	// 调用原始函数
	GetAddress("VerLanguageNameW")();

	// 转跳到返回地址
	__asm JMP m_dwReturn[12 * TYPE long];
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 导出函数
ALCDECL redirector_VerQueryValueA(void)
{
	// 保存返回地址
	__asm POP m_dwReturn[13 * TYPE long];

	// 调用原始函数
	GetAddress("VerQueryValueA")();

	// 转跳到返回地址
	__asm JMP m_dwReturn[13 * TYPE long];
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 导出函数
ALCDECL redirector_VerQueryValueW(void)
{
	// 保存返回地址
	__asm POP m_dwReturn[14 * TYPE long];

	// 调用原始函数
	GetAddress("VerQueryValueW")();

	// 转跳到返回地址
	__asm JMP m_dwReturn[14 * TYPE long];
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
