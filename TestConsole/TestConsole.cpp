// TestConsole.cpp :  此文件包含“main”函数，程序将在此处进行并结束。

#include <iostream>
#include <windows.h>
#include <detours.h>

#pragma comment(lib, "detours.lib")

int main()
{
    //std::cout << "Hello World!\n";
    //printf("Test!!!!!!!");
    STARTUPINFO si;
    PROCESS_INFORMATION pi;
    ZeroMemory(&si, sizeof(STARTUPINFO));
    ZeroMemory(&pi, sizeof(PROCESS_INFORMATION));
    si.cb = sizeof(STARTUPINFO);
    WCHAR DirPath[MAX_PATH + 1];
    wcscpy_s(DirPath, MAX_PATH, L"E:\\TestInitialNullForStudent\\InjectDll\\Debug");     //dll的文件夹
    char DLLPath[MAX_PATH + 1] = "E:\\TestInitialNullForStudent\\InjectDll\\Debug\\InnjectDll.dll";   //dll的地址
    WCHAR EXE[MAX_PATH + 1] = { 0 };
    wcscpy_s(EXE, MAX_PATH, L"E:\\TestInitialNullForStudent\\InjectDll\\Debug\\TestApp.exe");
    if (DetourCreateProcessWithDllEx(EXE, NULL, NULL, NULL, TRUE,
        CREATE_DEFAULT_ERROR_MODE | CREATE_SUSPENDED, NULL, DirPath, &si, &pi,
        DLLPath, NULL))
    {//MessageBoxA(NULL,"INJECT",NULL);
        ResumeThread(pi.hThread);
        WaitForSingleObject(pi.hProcess, INFINITE);
    }
    else
    {
        char error[100];
        sprintf_s(error, "%d", GetLastError());//Message(NULL,error,NULL,NULL)
    }
    return 0;
}