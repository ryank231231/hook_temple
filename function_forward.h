//for function forward

#define ALCDECL EXTERNC NAKED void __cdecl
#define EXTERNC extern "C"
#define NAKED __declspec(naked)
#define EXPORT __declspec(dllexport)

#define ALCPP EXPORT NAKED
#define ALSTD EXTERNC EXPORT NAKED void __stdcall
#define ALCFAST EXTERNC EXPORT NAKED void __fastcall

HMODULE m_hModule = NULL;	// ԭʼģ����
DWORD m_dwReturn[15] = {0};	// ԭʼ�������ص�ַ

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

// ����ԭʼģ��
inline BOOL WINAPI Load()
{
	TCHAR tzPath[MAX_PATH];
	TCHAR tzTemp[MAX_PATH * 2];

	GetSystemDirectory(tzPath, MAX_PATH);
	lstrcat(tzPath, TEXT("\\version"));
	m_hModule = LoadLibrary(tzPath);
	if (m_hModule == NULL)
	{
		wsprintf(tzTemp, TEXT("�޷����� %s�������޷��������С�"), tzPath);
		MessageBox(NULL, tzTemp, TEXT("redirector"), MB_ICONSTOP);
	}

	return (m_hModule != NULL);	
}

// �ͷ�ԭʼģ��
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

		wsprintf(tzTemp, TEXT("�޷��ҵ����� %hs�������޷��������С�"), pszProcName);
		MessageBox(NULL, tzTemp, TEXT("redirector"), MB_ICONSTOP);
		ExitProcess(-2);
	}

	return fpAddress;
}

// ��������
ALCDECL redirector_GetFileVersionInfoA(void)
{
	// ���淵�ص�ַ
	__asm POP m_dwReturn[0 * TYPE long];

	// ����ԭʼ����
	GetAddress("GetFileVersionInfoA")();

	// ת�������ص�ַ
	__asm JMP m_dwReturn[0 * TYPE long];
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ��������
ALCDECL redirector_GetFileVersionInfoByHandle(void)
{
	// ���淵�ص�ַ
	__asm POP m_dwReturn[1 * TYPE long];

	// ����ԭʼ����
	GetAddress("GetFileVersionInfoByHandle")();

	// ת�������ص�ַ
	__asm JMP m_dwReturn[1 * TYPE long];
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ��������
ALCDECL redirector_GetFileVersionInfoExW(void)
{
	// ���淵�ص�ַ
	__asm POP m_dwReturn[2 * TYPE long];

	// ����ԭʼ����
	GetAddress("GetFileVersionInfoExW")();

	// ת�������ص�ַ
	__asm JMP m_dwReturn[2 * TYPE long];
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ��������
ALCDECL redirector_GetFileVersionInfoSizeA(void)
{
	// ���淵�ص�ַ
	__asm POP m_dwReturn[3 * TYPE long];

	// ����ԭʼ����
	GetAddress("GetFileVersionInfoSizeA")();

	// ת�������ص�ַ
	__asm JMP m_dwReturn[3 * TYPE long];
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ��������
ALCDECL redirector_GetFileVersionInfoSizeExW(void)
{
	// ���淵�ص�ַ
	__asm POP m_dwReturn[4 * TYPE long];

	// ����ԭʼ����
	GetAddress("GetFileVersionInfoSizeExW")();

	// ת�������ص�ַ
	__asm JMP m_dwReturn[4 * TYPE long];
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ��������
ALCDECL redirector_GetFileVersionInfoSizeW(void)
{
	// ���淵�ص�ַ
	__asm POP m_dwReturn[5 * TYPE long];

	// ����ԭʼ����
	GetAddress("GetFileVersionInfoSizeW")();

	// ת�������ص�ַ
	__asm JMP m_dwReturn[5 * TYPE long];
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ��������
ALCDECL redirector_GetFileVersionInfoW(void)
{
	// ���淵�ص�ַ
	__asm POP m_dwReturn[6 * TYPE long];

	// ����ԭʼ����
	GetAddress("GetFileVersionInfoW")();

	// ת�������ص�ַ
	__asm JMP m_dwReturn[6 * TYPE long];
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ��������
ALCDECL redirector_VerFindFileA(void)
{
	// ���淵�ص�ַ
	__asm POP m_dwReturn[7 * TYPE long];

	// ����ԭʼ����
	GetAddress("VerFindFileA")();

	// ת�������ص�ַ
	__asm JMP m_dwReturn[7 * TYPE long];
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ��������
ALCDECL redirector_VerFindFileW(void)
{
	// ���淵�ص�ַ
	__asm POP m_dwReturn[8 * TYPE long];

	// ����ԭʼ����
	GetAddress("VerFindFileW")();

	// ת�������ص�ַ
	__asm JMP m_dwReturn[8 * TYPE long];
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ��������
ALCDECL redirector_VerInstallFileA(void)
{
	// ���淵�ص�ַ
	__asm POP m_dwReturn[9 * TYPE long];

	// ����ԭʼ����
	GetAddress("VerInstallFileA")();

	// ת�������ص�ַ
	__asm JMP m_dwReturn[9 * TYPE long];
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ��������
ALCDECL redirector_VerInstallFileW(void)
{
	// ���淵�ص�ַ
	__asm POP m_dwReturn[10 * TYPE long];

	// ����ԭʼ����
	GetAddress("VerInstallFileW")();

	// ת�������ص�ַ
	__asm JMP m_dwReturn[10 * TYPE long];
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ��������
ALCDECL redirector_VerLanguageNameA(void)
{
	// ���淵�ص�ַ
	__asm POP m_dwReturn[11 * TYPE long];

	// ����ԭʼ����
	GetAddress("VerLanguageNameA")();

	// ת�������ص�ַ
	__asm JMP m_dwReturn[11 * TYPE long];
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ��������
ALCDECL redirector_VerLanguageNameW(void)
{
	// ���淵�ص�ַ
	__asm POP m_dwReturn[12 * TYPE long];

	// ����ԭʼ����
	GetAddress("VerLanguageNameW")();

	// ת�������ص�ַ
	__asm JMP m_dwReturn[12 * TYPE long];
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ��������
ALCDECL redirector_VerQueryValueA(void)
{
	// ���淵�ص�ַ
	__asm POP m_dwReturn[13 * TYPE long];

	// ����ԭʼ����
	GetAddress("VerQueryValueA")();

	// ת�������ص�ַ
	__asm JMP m_dwReturn[13 * TYPE long];
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ��������
ALCDECL redirector_VerQueryValueW(void)
{
	// ���淵�ص�ַ
	__asm POP m_dwReturn[14 * TYPE long];

	// ����ԭʼ����
	GetAddress("VerQueryValueW")();

	// ת�������ص�ַ
	__asm JMP m_dwReturn[14 * TYPE long];
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
