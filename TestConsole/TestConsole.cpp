// TestConsole.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include<iostream>
#include<cstdio>
#include<windows.h>
#include<detours.h>
#include<thread>
#include <atlconv.h>

#pragma comment(lib, "detours.lib")
#pragma warning(disable: 4996)

using namespace std;

int main(int argc, char* argv[]) {
	 
	// 如果所选文件为TestConsole注射器，立即返回
	if (strstr(argv[0], "TestConsole")) {
		return 0;
	}
	// fileName转化
	wchar_t fileName[256] = L"";
	MultiByteToWideChar(CP_ACP, 0, argv[0], strlen(argv[0]), fileName, sizeof(fileName));
	wprintf(L"%s\n", fileName);

	STARTUPINFO si;
	PROCESS_INFORMATION pi;
	ZeroMemory(&si, sizeof(STARTUPINFO));
	ZeroMemory(&pi, sizeof(PROCESS_INFORMATION));
	si.cb = sizeof(STARTUPINFO);
	// 文件夹路径
	WCHAR DirPath[MAX_PATH + 1];
	wcscpy_s(DirPath, MAX_PATH, L"E:\\TestInitialNullForStudent\\InjectDll\\Debug");	// dll文件夹
	// dll路径
	char DLLPath[MAX_PATH + 1] = "E:\\TestInitialNullForStudent\\InjectDll\\Debug\\InnjectDll.dll"; // dll的地址
	// 测试文件路径
	WCHAR EXE[MAX_PATH + 1] = { 0 };
	// wcscpy_s(EXE, MAX_PATH, L"E:\\TestInitialNullForStudent\\InjectDll\\Debug\\TestApp.exe"); // MessageBoxA
	// wcscpy_s(EXE, MAX_PATH, L"E:\\TestInitialNullForStudent\\InjectDll\\Debug\\TestExe.exe"); // TestExe
	wcscpy_s(EXE, MAX_PATH, fileName); // 自选文件

	USES_CONVERSION;
	LPWSTR commandLine = NULL;
	commandLine = A2W(argv[1]);


	if (DetourCreateProcessWithDllEx(EXE, commandLine, NULL, NULL, TRUE,
		CREATE_DEFAULT_ERROR_MODE | CREATE_SUSPENDED, NULL, DirPath,
		&si, &pi, DLLPath, NULL)) {
		// 恢复线程
		ResumeThread(pi.hThread);
		WaitForSingleObject(pi.hProcess, INFINITE);
	}
	else {
		char error[100];
		sprintf(error, "%d", GetLastError());
	}
	return 0;
}