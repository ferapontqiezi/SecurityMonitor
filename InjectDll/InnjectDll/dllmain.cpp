// dllmain.cpp : 定义 DLL 应用程序的入口点。
#include "pch.h"
#include "framework.h"
#include "detours.h"
#include "stdio.h"
#include "stdarg.h"
#include "windows.h"
#include <iostream>
#include <cstring>
#include <string>
#include <stdlib.h>
#include <unordered_map>
#include <WinSock2.h>
#include <ws2tcpip.h>

// 忽略warning信息
#define _CRT_SECURE_NO_WARNINGS
#pragma warning(disable: 4996)

#pragma comment(lib,"detours.lib")
 // 加载 ws2_32.dll
#pragma comment (lib, "ws2_32.lib")

#define NONE 0
 //  MessageBox调用截获（1）
#define MESSAGEBOXA 1  
#define MESSAGEBOXW 2   
 //  文件操作API调用截获（4，8）
#define CREATEFILE 3   
#define WRITEFILE 4
#define READFILE 5
 //  堆操作API调用截获（2，6）
#define HEAPCREATE 6
#define HEAPDESTROY 7
#define HEAPFREE 8
 //  注册表API调用截获（5，9）
#define REGCREATEKEYEX 9
#define REGSETVALUEEX 10
#define REGGETVALUE 11
#define REGCLOSEKEY 12
#define REGOPENKEYEX 13
#define REGDELETEVALUE 14
 //  网络通信API调用截获（3，7）
#define ASOCKET 15
#define BIND 16
#define SEND 17
#define RECV 18

using namespace std;

SYSTEMTIME st;
FILE* f;

struct info {
    int type, argNum;
    SYSTEMTIME st;
    char argName[10][50] = { 0 };
    char argValue[10][50] = { 0 };
};

info contactInfo;
// 用 内存映射方式实现了 共享数据访问。
HANDLE hSemaphore = OpenSemaphore(EVENT_ALL_ACCESS, FALSE, L"mySemaphore");
HANDLE hMappingFile = OpenFileMapping(FILE_MAP_ALL_ACCESS, NULL, L"ShareMemory");
LPVOID MapFileBase = MapViewOfFile(hMappingFile, FILE_MAP_ALL_ACCESS, 0, 0, sizeof(info));


// 消息弹窗操作API截获
// MessageBox A and W (Old -> New)

static int (WINAPI* OldMessageBoxW)(_In_opt_ HWND hWnd, _In_opt_ LPCWSTR lpText, _In_opt_ LPCWSTR lpCaption, _In_ UINT uType) = MessageBoxW;
static int (WINAPI* OldMessageBoxA)(_In_opt_ HWND hWnd, _In_opt_ LPCSTR lpText, _In_opt_ LPCSTR lpCaption, _In_ UINT uType) = MessageBoxA;

extern "C"  __declspec(dllexport)int WINAPI NewMessageBoxA(_In_opt_ HWND hWnd, _In_opt_ LPCSTR lpText, _In_opt_ LPCSTR lpCaption, _In_ UINT uType)
{
    Sleep(100);
    // 向contactInfo中写入数据
    contactInfo.type = MESSAGEBOXA;
    GetLocalTime(&(contactInfo.st));
    contactInfo.argNum = 4;
    // 参数名
    sprintf_s(contactInfo.argName[0], sizeof(contactInfo.argName[0]), "hWnd");
    sprintf_s(contactInfo.argName[1], sizeof(contactInfo.argName[1]), "lpText");
    sprintf_s(contactInfo.argName[2], sizeof(contactInfo.argName[2]), "lpCaption");
    sprintf_s(contactInfo.argName[3], sizeof(contactInfo.argName[3]), "uType");
    // 参数值
    sprintf_s(contactInfo.argValue[0], sizeof(contactInfo.argValue[0]), "%08X", hWnd);
    sprintf_s(contactInfo.argValue[1], sizeof(contactInfo.argValue[1]), "%s", lpText);
    sprintf_s(contactInfo.argValue[2], sizeof(contactInfo.argValue[2]), "%s", lpCaption);
    sprintf_s(contactInfo.argValue[3], sizeof(contactInfo.argValue[3]), "%08X", uType);
    // 将contactInfo赋值到共享内存
    memcpy(MapFileBase, &contactInfo, sizeof(info));
    printf("I am MessageBoxA\n");
    // 使得信号量+1
    ReleaseSemaphore(hSemaphore, 1, NULL);

    fprintf(f, "\n\n****************************************\n");
    fprintf(f, "MessageBoxA Hooked\n");
    GetLocalTime(&st);
    fprintf(f, "DLL日志输出：%d-%d-%d %02d: %02d: %02d: %03d\n", st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond, st.wMilliseconds);
    fprintf(f, "hWnd: %08x\n", hWnd);
    fprintf(f, "lpText: %s\n", lpText);
    fprintf(f, "lpCaption: %s\n", lpCaption);
    fprintf(f, "uType: %08x\n", uType);
    fprintf(f, "****************************************\n");
    printf("***********\n");
    
    Sleep(10); // 防止重复Hook
    return OldMessageBoxA(hWnd, lpText, lpCaption, uType);
}

extern "C"  __declspec(dllexport)int WINAPI NewMessageBoxW(_In_opt_ HWND hWnd, _In_opt_ LPCWSTR lpText, _In_opt_ LPCWSTR lpCaption, _In_ UINT uType)
{
    char temp1[70], temp2[70];
    contactInfo.type = MESSAGEBOXW;
    GetLocalTime(&(contactInfo.st));

    contactInfo.argNum = 4;
    // 参数名
    sprintf_s(contactInfo.argName[0], sizeof(contactInfo.argName[0]), "hWnd");
    sprintf_s(contactInfo.argName[1], sizeof(contactInfo.argName[1]), "lpText");
    sprintf_s(contactInfo.argName[2], sizeof(contactInfo.argName[2]), "lpCaption");
    sprintf_s(contactInfo.argName[3], sizeof(contactInfo.argName[3]), "uType");
    // 参数值
    sprintf_s(contactInfo.argValue[0], sizeof(contactInfo.argValue[0]), "%08X", hWnd);
    // 宽字节转char
    memset(temp1, 0, sizeof(temp1));
    WideCharToMultiByte(CP_ACP, 0, lpText, wcslen(lpText), temp1, sizeof(temp1), NULL, NULL);
    strcpy(contactInfo.argValue[1], temp1);
    // 宽字节转char
    memset(temp2, 0, sizeof(temp2));
    WideCharToMultiByte(CP_ACP, 0, lpCaption, wcslen(lpCaption), temp2, sizeof(temp2), NULL, NULL);
    strcpy(contactInfo.argValue[2], temp2);
    sprintf_s(contactInfo.argValue[3], sizeof(contactInfo.argValue[3]), "%08X", uType);
    printf("I am MessageBoxW\n");

    memcpy(MapFileBase, &contactInfo, sizeof(info));
    ReleaseSemaphore(hSemaphore, 1, NULL);

    fprintf(f, "\n\n****************************************\n");
    fprintf(f, "MessageBoxW Hooked\n");
    GetLocalTime(&st);
    fprintf(f, "DLL日志输出：%d-%d-%d %02d: %02d: %02d: %03d\n", st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond, st.wMilliseconds);
    fprintf(f, "hWnd: %08x\n", hWnd);
    fprintf(f, "lpText: %s\n", temp1);
    fprintf(f, "lpCaption: %s\n", temp2);
    fprintf(f, "uType: %08x\n", uType);
    fprintf(f, "****************************************\n");
    printf("***********\n");

    Sleep(10);
    return OldMessageBoxW(hWnd, lpText, lpCaption, uType);
}


// 文件操作API截获
// File Operations (Create, Write, Read)

static HANDLE(WINAPI* OldCreateFile)(
    LPCTSTR lpFileName,//文件名
    DWORD dwDesireAccess, //访问模式
    DWORD dwShareMode, //共享模式
    LPSECURITY_ATTRIBUTES lpSecurityAttributes, //安全属性
    DWORD dwCreationDisposition, //创建类型
    DWORD dwFlagAndAttributes, //文件属性
    HANDLE hTemplateFile //模板文件句柄
    ) = CreateFile;

extern "C"  __declspec(dllexport)HANDLE WINAPI NewCreateFile(
    LPCTSTR lpFileName,//文件名
    DWORD dwDesireAccess, //访问模式
    DWORD dwShareMode, //共享模式
    LPSECURITY_ATTRIBUTES lpSecurityAttributes, //安全属性
    DWORD dwCreationDisposition, //创建类型
    DWORD dwFlagAndAttributes, //文件属性
    HANDLE hTemplateFile //模板文件句柄
)
{
    HANDLE hFile = OldCreateFile(lpFileName, dwDesireAccess, dwShareMode, lpSecurityAttributes, dwCreationDisposition, dwFlagAndAttributes, hTemplateFile);
    if (GetFileType(hFile) == FILE_TYPE_DISK) {
        char temp[70];
        contactInfo.type = CREATEFILE;
        GetLocalTime(&(contactInfo.st));

        contactInfo.argNum = 7;
        // 参数名
        sprintf_s(contactInfo.argName[0], sizeof(contactInfo.argName[0]), "lpFileName");
        sprintf_s(contactInfo.argName[1], sizeof(contactInfo.argName[1]), "dwDesireAccess");
        sprintf_s(contactInfo.argName[2], sizeof(contactInfo.argName[2]), "dwShareMode");
        sprintf_s(contactInfo.argName[3], sizeof(contactInfo.argName[3]), "lpSecurityAttributes");
        sprintf_s(contactInfo.argName[4], sizeof(contactInfo.argName[4]), "dwCreationDisposition");
        sprintf_s(contactInfo.argName[5], sizeof(contactInfo.argName[5]), "dwFlagAndAttributes");
        sprintf_s(contactInfo.argName[6], sizeof(contactInfo.argName[6]), "hTemplateFile");
        // 参数值
        // 宽字节转char
        memset(temp, 0, sizeof(temp));
        WideCharToMultiByte(CP_ACP, 0, lpFileName, wcslen(lpFileName), temp, sizeof(temp), NULL, NULL);
        strcpy(contactInfo.argValue[0], temp);
        sprintf_s(contactInfo.argValue[1], sizeof(contactInfo.argValue[1]), "%08X", dwDesireAccess);
        sprintf_s(contactInfo.argValue[2], sizeof(contactInfo.argValue[2]), "%08X", dwShareMode);
        sprintf_s(contactInfo.argValue[3], sizeof(contactInfo.argValue[3]), "%08X", lpSecurityAttributes);
        sprintf_s(contactInfo.argValue[4], sizeof(contactInfo.argValue[4]), "%08X", dwCreationDisposition);
        sprintf_s(contactInfo.argValue[5], sizeof(contactInfo.argValue[5]), "%08X", dwFlagAndAttributes);
        sprintf_s(contactInfo.argValue[6], sizeof(contactInfo.argValue[6]), "%08X", hTemplateFile);

        memcpy(MapFileBase, &contactInfo, sizeof(info));
        ReleaseSemaphore(hSemaphore, 1, NULL);

        fprintf(f, "\n\n****************************************\n");
        fprintf(f, "CreateFile Hooked\n");
        GetLocalTime(&st);
        fprintf(f, "DLL日志输出：%d-%d-%d %02d: %02d: %02d: %03d\n", st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond, st.wMilliseconds);
        fprintf(f, "lpFileName: %s\n", temp);
        fprintf(f, "dwDesireAccess: %08x\n", dwDesireAccess);
        fprintf(f, "dwShareMode: %08x\n", dwShareMode);
        fprintf(f, "lpSecurityAttributes: %08x\n", lpSecurityAttributes);
        fprintf(f, "dwCreationDisposition: %08x\n", dwCreationDisposition);
        fprintf(f, "dwFlagAndAttributes: %08x\n", dwFlagAndAttributes);
        fprintf(f, "hTemplateFile: %08x\n", hTemplateFile);
        fprintf(f, "****************************************\n");
    }

    Sleep(10);
    return hFile;

    /*int num = WideCharToMultiByte(CP_OEMCP, NULL, lpFileName, -1, NULL, 0, NULL, FALSE);
    char* pchar = new char[num];
    WideCharToMultiByte(CP_OEMCP, NULL, lpFileName, -1, pchar, num, NULL, FALSE);
    std::cout << "lpFileName ：" << pchar << std::endl;
    std::cout << "dwDesireAccess ：0x" << std::hex << dwDesireAccess << std::endl;
    std::cout << "dwShareMode : 0x" << std::hex << dwShareMode << std::endl;
    std::cout << "lpSecurityAttributes ：0x" << std::hex << lpSecurityAttributes << std::endl;
    std::cout << "dwCreationDisposition ：0x" << std::hex << dwCreationDisposition << std::endl;
    std::cout << "dwFlagAndAttributes ：0x" << std::hex << dwFlagAndAttributes << std::endl;
    std::cout << "hTemplateFile ：0x" << std::hex << hTemplateFile << std::endl;
    return OldCreateFile(lpFileName, dwDesireAccess, dwShareMode, lpSecurityAttributes, dwCreationDisposition, dwFlagAndAttributes, hTemplateFile);*/
}

static BOOL(WINAPI* OldWriteFile)(
    HANDLE       hFile,
    LPCVOID      lpBuffer,
    DWORD        nNumberOfBytesToWrite,
    LPDWORD      lpNumberOfBytesWritten,
    LPOVERLAPPED lpOverlapped
    ) = WriteFile;

extern "C" __declspec(dllexport)BOOL WINAPI NewWriteFile(
    HANDLE       hFile,
    LPCVOID      lpBuffer,
    DWORD        nNumberOfBytesToWrite,
    LPDWORD      lpNumberOfBytesWritten,
    LPOVERLAPPED lpOverlapped
)
{
    if (GetFileType(hFile) == FILE_TYPE_DISK) {
        contactInfo.argNum = 5;
        contactInfo.type = WRITEFILE;
        // 参数名
        sprintf_s(contactInfo.argName[0], sizeof(contactInfo.argName[0]), "hFile");
        sprintf_s(contactInfo.argName[1], sizeof(contactInfo.argName[1]), "lpBuffer");
        sprintf_s(contactInfo.argName[2], sizeof(contactInfo.argName[2]), "nNumberOfBytesToWrite");
        sprintf_s(contactInfo.argName[3], sizeof(contactInfo.argName[3]), "lpNumberOfBytesWritten");
        sprintf_s(contactInfo.argName[4], sizeof(contactInfo.argName[4]), "lpOverlapped");
        // 参数值
        sprintf_s(contactInfo.argValue[0], sizeof(contactInfo.argValue[0]), "%08X", hFile);
        sprintf_s(contactInfo.argValue[1], sizeof(contactInfo.argValue[1]), "%s", lpBuffer);
        sprintf_s(contactInfo.argValue[2], sizeof(contactInfo.argValue[2]), "%08X", nNumberOfBytesToWrite);
        sprintf_s(contactInfo.argValue[3], sizeof(contactInfo.argValue[3]), "%08X", lpNumberOfBytesWritten);
        sprintf_s(contactInfo.argValue[4], sizeof(contactInfo.argValue[4]), "%08X", lpOverlapped);

        GetLocalTime(&(contactInfo.st));
        // 将contactInfo赋值到共享内存
        memcpy(MapFileBase, &contactInfo, sizeof(info));
        // 使得信号量+1
        ReleaseSemaphore(hSemaphore, 1, NULL);

        fprintf(f, "\n\n****************************************\n");
        fprintf(f, "WriteFile Hooked\n");
        GetLocalTime(&st);
        fprintf(f, "DLL日志输出：%d-%d-%d %02d: %02d: %02d: %03d\n", st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond, st.wMilliseconds);
        fprintf(f, "hFile: %08x\n", hFile);
        fprintf(f, "lpBuffer: %s\n", lpBuffer);
        fprintf(f, "nNumberOfBytesToWrite: %08x\n", nNumberOfBytesToWrite);
        fprintf(f, "lpNumberOfBytesWritten: % 08x\n", lpNumberOfBytesWritten);
        fprintf(f, "lpOverlapped: %08x\n", lpOverlapped);
        fprintf(f, "****************************************\n");

    }
    
    Sleep(10);
    return OldWriteFile(hFile, lpBuffer, nNumberOfBytesToWrite, lpNumberOfBytesWritten, lpOverlapped);
}

static BOOL(WINAPI* OldReadFile)(
    HANDLE       hFile,
    LPVOID       lpBuffer,
    DWORD        nNumberOfBytesToRead,
    LPDWORD      lpNumberOfBytesRead,
    LPOVERLAPPED lpOverlapped
    ) = ReadFile;

extern "C" __declspec(dllexport)BOOL WINAPI NewReadFile(
    HANDLE       hFile,
    LPVOID       lpBuffer,
    DWORD        nNumberOfBytesToRead,
    LPDWORD      lpNumberOfBytesRead,
    LPOVERLAPPED lpOverlapped
)
{
    if (GetFileType(hFile) == FILE_TYPE_DISK) {
        contactInfo.argNum = 5;
        contactInfo.type = READFILE;
        // 参数名
        sprintf_s(contactInfo.argName[0], sizeof(contactInfo.argName[0]), "hFile");
        sprintf_s(contactInfo.argName[1], sizeof(contactInfo.argName[1]), "lpBuffer");
        sprintf_s(contactInfo.argName[2], sizeof(contactInfo.argName[2]), "nNumberOfBytesToRead");
        sprintf_s(contactInfo.argName[3], sizeof(contactInfo.argName[3]), "lpNumberOfBytesRead");
        sprintf_s(contactInfo.argName[4], sizeof(contactInfo.argName[4]), "lpOverlapped");
        // 参数值
        sprintf_s(contactInfo.argValue[0], sizeof(contactInfo.argValue[0]), "%08X", hFile);
        sprintf_s(contactInfo.argValue[1], sizeof(contactInfo.argValue[1]), "%08X", lpBuffer);
        sprintf_s(contactInfo.argValue[2], sizeof(contactInfo.argValue[2]), "%08X", nNumberOfBytesToRead);
        sprintf_s(contactInfo.argValue[3], sizeof(contactInfo.argValue[3]), "%08X", lpNumberOfBytesRead);
        sprintf_s(contactInfo.argValue[4], sizeof(contactInfo.argValue[4]), "%08X", lpOverlapped);
        // 共享内存，信号量加一
        GetLocalTime(&(contactInfo.st));
        memcpy(MapFileBase, &contactInfo, sizeof(info));
        ReleaseSemaphore(hSemaphore, 1, NULL);

        fprintf(f, "\n\n****************************************\n");
        fprintf(f, "ReadFile Hooked\n");
        GetLocalTime(&st);
        fprintf(f, "DLL日志输出：%d-%d-%d %02d: %02d: %02d: %03d\n", st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond, st.wMilliseconds);
        fprintf(f, "hFile: %08x\n", hFile);
        fprintf(f, "lpBuffer: %08x\n", lpBuffer);
        fprintf(f, "nNumberOfBytesToRead: %08x\n", nNumberOfBytesToRead);
        fprintf(f, "lpNumberOfBytesRead: %08x\n", lpNumberOfBytesRead);
        fprintf(f, "lpOverlapped: %08x\n", lpOverlapped);
        fprintf(f, "****************************************\n");

    }
    
    Sleep(10);
    return OldReadFile(hFile, lpBuffer, nNumberOfBytesToRead, lpNumberOfBytesRead, lpOverlapped);
}


// 堆操作API截获
// Heap Operations(Create, Destroy, Free)

static HANDLE(WINAPI* OldHeapCreate)(DWORD fIOoptions, SIZE_T dwInitialSize, SIZE_T dwMaximumSize) = HeapCreate;

extern "C" __declspec(dllexport)HANDLE WINAPI NewHeapCreate(DWORD fIOoptions, SIZE_T dwInitialSize, SIZE_T dwMaximumSize)
{
    HANDLE hFile = OldHeapCreate(fIOoptions, dwInitialSize, dwMaximumSize);
    contactInfo.argNum = 4;
    // 参数名
    sprintf_s(contactInfo.argName[0], sizeof(contactInfo.argName[0]), "fIOoptions");
    sprintf_s(contactInfo.argName[1], sizeof(contactInfo.argName[1]), "dwInitialSize");
    sprintf_s(contactInfo.argName[2], sizeof(contactInfo.argName[2]), "dwMaximumSize");
    sprintf_s(contactInfo.argName[3], sizeof(contactInfo.argName[3]), "HANDLE");
    // 参数值
    sprintf_s(contactInfo.argValue[0], sizeof(contactInfo.argValue[0]), "%08X", fIOoptions);
    sprintf_s(contactInfo.argValue[1], sizeof(contactInfo.argValue[1]), "%08X", dwInitialSize);
    sprintf_s(contactInfo.argValue[2], sizeof(contactInfo.argValue[2]), "%08X", dwMaximumSize);
    sprintf_s(contactInfo.argValue[3], sizeof(contactInfo.argValue[3]), "%08X", hFile);

    contactInfo.type = HEAPCREATE;
    GetLocalTime(&(contactInfo.st));
    memcpy(MapFileBase, &contactInfo, sizeof(info));
    ReleaseSemaphore(hSemaphore, 1, NULL);

    fprintf(f, "\n\n****************************************\n");
    fprintf(f, "HeapCreate Hooked\n");
    GetLocalTime(&st);
    fprintf(f, "DLL日志输出：%d-%d-%d %02d: %02d: %02d: %03d\n", st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond, st.wMilliseconds);
    fprintf(f, "fIOoptions: %08x\n", fIOoptions);
    fprintf(f, "dwInitialSize: %08x\n", dwInitialSize);
    fprintf(f, "dwMaximumSize: %08x\n", dwMaximumSize);
    fprintf(f, "hFile: %08x\n", hFile);
    fprintf(f, "****************************************\n");

    Sleep(10);
    return hFile;
}

static BOOL(WINAPI* OldHeapDestroy)(HANDLE) = HeapDestroy;
extern "C" __declspec(dllexport) BOOL WINAPI NewHeapDestroy(HANDLE hHeap)
{
    contactInfo.argNum = 1;
    // 参数名
    sprintf_s(contactInfo.argName[0], sizeof(contactInfo.argName[0]), "hHeap");
    // 参数值
    sprintf_s(contactInfo.argValue[0], sizeof(contactInfo.argValue[0]), "%08X", hHeap);

    contactInfo.type = HEAPDESTROY;
    GetLocalTime(&(contactInfo.st));
    memcpy(MapFileBase, &contactInfo, sizeof(info));
    ReleaseSemaphore(hSemaphore, 1, NULL);

    fprintf(f, "\n\n****************************************\n");
    fprintf(f, "HeapDestroy Hooked\n");
    GetLocalTime(&st);
    fprintf(f, "DLL日志输出：%d-%d-%d %02d: %02d: %02d: %03d\n", st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond, st.wMilliseconds);
    fprintf(f, "hKey: %08x\n", hHeap);
    fprintf(f, "****************************************\n");

    Sleep(10);
    return OldHeapDestroy(hHeap);
}

static BOOL(WINAPI* OldHeapFree)(HANDLE hHeap, DWORD dwFlags, _Frees_ptr_opt_ LPVOID lpMem) = HeapFree;
extern "C" __declspec(dllexport) BOOL WINAPI NewHeapFree(HANDLE hHeap, DWORD dwFlags, _Frees_ptr_opt_ LPVOID lpMem) {
    contactInfo.argNum = 3;
    // 参数名
    sprintf_s(contactInfo.argName[0], sizeof(contactInfo.argName[0]), "hHeap");
    sprintf_s(contactInfo.argName[1], sizeof(contactInfo.argName[1]), "dwFlags");
    sprintf_s(contactInfo.argName[2], sizeof(contactInfo.argName[2]), "lpMem");
    // 参数值
    sprintf_s(contactInfo.argValue[0], sizeof(contactInfo.argValue[0]), "%08X", hHeap);
    sprintf_s(contactInfo.argValue[1], sizeof(contactInfo.argValue[1]), "%08X", dwFlags);
    sprintf_s(contactInfo.argValue[2], sizeof(contactInfo.argValue[2]), "%08X", lpMem);

    contactInfo.type = HEAPFREE;
    GetLocalTime(&(contactInfo.st));
    memcpy(MapFileBase, &contactInfo, sizeof(info));
    ReleaseSemaphore(hSemaphore, 1, NULL);

    fprintf(f, "\n\n****************************************\n");
    fprintf(f, "HeapFree Hooked\n");
    GetLocalTime(&st);
    fprintf(f, "DLL日志输出：%d-%d-%d %02d: %02d: %02d: %03d\n", st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond, st.wMilliseconds);
    fprintf(f, "hKey: %08x\n", hHeap);
    fprintf(f, "dwFlags: %08x\n", dwFlags);
    fprintf(f, "lpMem: %08x\n", lpMem);
    fprintf(f, "****************************************\n");

    Sleep(10);
    return OldHeapFree(hHeap, dwFlags, lpMem);
}


// 注册表操作API截获
// Registry Operations(Create, Delete, Set, Get, Open, Close)

static LSTATUS(WINAPI* OldRegCreateKeyEx)(
    HKEY                        hKey,
    LPCWSTR                     lpSubKey,
    DWORD                       Reserved,
    LPWSTR                      lpClass,
    DWORD                       dwOptions,
    REGSAM                      samDesired,
    const LPSECURITY_ATTRIBUTES lpSecurityAttributes,
    PHKEY                       phkResult,
    LPDWORD                     lpdwDisposition
    ) = RegCreateKeyEx;

extern "C" __declspec(dllexport)LSTATUS WINAPI NewRegCreateKeyEx(
    HKEY                        hKey,
    LPCWSTR                     lpSubKey,
    DWORD                       Reserved,
    LPWSTR                      lpClass,
    DWORD                       dwOptions,
    REGSAM                      samDesired,
    const LPSECURITY_ATTRIBUTES lpSecurityAttributes,
    PHKEY                       phkResult,
    LPDWORD                     lpdwDisposition
)
{
    char temp[70];
    contactInfo.argNum = 9;

    sprintf_s(contactInfo.argName[0], sizeof(contactInfo.argName[0]), "hKey");
    sprintf_s(contactInfo.argName[1], sizeof(contactInfo.argName[1]), "lpSubKey");
    sprintf_s(contactInfo.argName[2], sizeof(contactInfo.argName[2]), "Reserved");
    sprintf_s(contactInfo.argName[3], sizeof(contactInfo.argName[3]), "lpClass");
    sprintf_s(contactInfo.argName[4], sizeof(contactInfo.argName[4]), "dwOptions");
    sprintf_s(contactInfo.argName[5], sizeof(contactInfo.argName[5]), "samDesired");
    sprintf_s(contactInfo.argName[6], sizeof(contactInfo.argName[6]), "lpSecurityAttributes");
    sprintf_s(contactInfo.argName[7], sizeof(contactInfo.argName[7]), "phkResult");
    sprintf_s(contactInfo.argName[8], sizeof(contactInfo.argName[8]), "lpdwDisposition");

    sprintf_s(contactInfo.argValue[0], sizeof(contactInfo.argValue[0]), "%08X", hKey);
    memset(temp, 0, sizeof(temp));
    WideCharToMultiByte(CP_ACP, 0, lpSubKey, wcslen(lpSubKey), temp, sizeof(temp), NULL, NULL);
    strcpy(contactInfo.argValue[1], temp);
    sprintf_s(contactInfo.argValue[2], sizeof(contactInfo.argValue[2]), "%08X", Reserved);
    sprintf_s(contactInfo.argValue[3], sizeof(contactInfo.argValue[3]), "%08X", lpClass);
    sprintf_s(contactInfo.argValue[4], sizeof(contactInfo.argValue[4]), "%08X", dwOptions);
    sprintf_s(contactInfo.argValue[5], sizeof(contactInfo.argValue[5]), "%08X", samDesired);
    sprintf_s(contactInfo.argValue[6], sizeof(contactInfo.argValue[6]), "%08X", lpSecurityAttributes);
    sprintf_s(contactInfo.argValue[7], sizeof(contactInfo.argValue[7]), "%08X", phkResult);
    sprintf_s(contactInfo.argValue[8], sizeof(contactInfo.argValue[8]), "%08X", lpdwDisposition);

    contactInfo.type = REGCREATEKEYEX;
    GetLocalTime(&(contactInfo.st));
    memcpy(MapFileBase, &contactInfo, sizeof(info));
    ReleaseSemaphore(hSemaphore, 1, NULL);

    fprintf(f, "\n\n****************************************\n");
    fprintf(f, "RegCreateKeyEx Hooked\n");
    GetLocalTime(&st);
    fprintf(f, "DLL日志输出：%d-%d-%d %02d: %02d: %02d: %03d\n", st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond, st.wMilliseconds);
    fprintf(f, "hKey: %08x\n", hKey);
    fprintf(f, "lpSubKey: %s\n", temp);
    fprintf(f, "Reserved: %08x\n", Reserved);
    fprintf(f, "lpClass: %08x\n", lpClass);
    fprintf(f, "dwOptions: %08x\n", dwOptions);
    fprintf(f, "samDesired: %08x\n", samDesired);
    fprintf(f, "lpSecurityAttributes: %08x\n", lpSecurityAttributes);
    fprintf(f, "phkResult: %08x\n", phkResult);
    fprintf(f, "lpdwDisposition: %08x\n", lpdwDisposition);
    fprintf(f, "****************************************\n");

    Sleep(10);
    return OldRegCreateKeyEx(hKey, lpSubKey, Reserved, lpClass, dwOptions, samDesired, lpSecurityAttributes, phkResult, lpdwDisposition);
}

static LSTATUS(WINAPI* OldRegSetValueEx)(
    HKEY       hKey,
    LPCWSTR    lpValueName,
    DWORD      Reserved,
    DWORD      dwType,
    const BYTE* lpData,
    DWORD      cbData
    ) = RegSetValueEx;

extern "C" __declspec(dllexport)LSTATUS WINAPI NewRegSetValueEx(
    HKEY       hKey,
    LPCWSTR    lpValueName,
    DWORD      Reserved,
    DWORD      dwType,
    const BYTE * lpData,
    DWORD      cbData
)
{
    char temp1[70], temp2[70];
    contactInfo.argNum = 6;

    sprintf_s(contactInfo.argName[0], sizeof(contactInfo.argName[0]), "hKey");
    sprintf_s(contactInfo.argName[1], sizeof(contactInfo.argName[1]), "lpValueName");
    sprintf_s(contactInfo.argName[2], sizeof(contactInfo.argName[2]), "Reserved");
    sprintf_s(contactInfo.argName[3], sizeof(contactInfo.argName[3]), "dwType");
    sprintf_s(contactInfo.argName[4], sizeof(contactInfo.argName[4]), "lpData");
    sprintf_s(contactInfo.argName[5], sizeof(contactInfo.argName[5]), "cbData");

    sprintf_s(contactInfo.argValue[0], sizeof(contactInfo.argValue[0]), "%08X", hKey);
    memset(temp1, 0, sizeof(temp1));
    WideCharToMultiByte(CP_ACP, 0, lpValueName, wcslen(lpValueName), temp1, sizeof(temp1), NULL, NULL);
    strcpy(contactInfo.argValue[1], temp1);
    sprintf_s(contactInfo.argValue[2], sizeof(contactInfo.argValue[2]), "%08X", Reserved);
    sprintf_s(contactInfo.argValue[3], sizeof(contactInfo.argValue[3]), "%08X", dwType);
    memset(temp2, 0, sizeof(temp2));
    WideCharToMultiByte(CP_ACP, 0, (LPCWCH)lpData, wcslen((LPCWCH)lpData), temp2, sizeof(temp2), NULL, NULL);
    strcpy(contactInfo.argValue[4], temp2);
    sprintf_s(contactInfo.argValue[5], sizeof(contactInfo.argValue[5]), "%08X", cbData);

    contactInfo.type = REGSETVALUEEX;
    GetLocalTime(&(contactInfo.st));
    memcpy(MapFileBase, &contactInfo, sizeof(info));
    ReleaseSemaphore(hSemaphore, 1, NULL);

    fprintf(f, "\n\n****************************************\n");
    fprintf(f, "RegSetValueEx Hooked\n");
    GetLocalTime(&st);
    fprintf(f, "DLL日志输出：%d-%d-%d %02d: %02d: %02d: %03d\n", st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond, st.wMilliseconds);
    fprintf(f, "hKey: %08x\n", hKey);
    fprintf(f, "lpValueName: %s\n", temp1);
    fprintf(f, "Reserved: %08x\n", Reserved);
    fprintf(f, "dwType: %08x\n", dwType);
    fprintf(f, "lpData: %s\n", temp2);
    fprintf(f, "cbData: %08x\n", cbData);
    fprintf(f, "****************************************\n");

    Sleep(10);
    return OldRegSetValueEx(hKey, lpValueName, Reserved, dwType, lpData, cbData);
}

static LSTATUS(WINAPI* OldRegGetValue)(
    HKEY       hKey,
    LPCWSTR    lpSubKey,
    LPCWSTR    lpValue,
    DWORD      dwType,
    LPDWORD   pdwType,
    PVOID     pvData,
    LPDWORD    pcbData
    ) = RegGetValue;

extern "C" __declspec(dllexport)LSTATUS WINAPI NewRegGetValue(
    HKEY       hKey,
    LPCWSTR    lpSubKey,
    LPCWSTR    lpValue,
    DWORD      dwType,
    LPDWORD   pdwType,
    PVOID     pvData,
    LPDWORD    pcbData
)
{
    char temp1[70], temp2[70];
    contactInfo.argNum = 7;

    sprintf_s(contactInfo.argName[0], sizeof(contactInfo.argName[0]), "hKey");
    sprintf_s(contactInfo.argName[1], sizeof(contactInfo.argName[1]), "lpSubKey");
    sprintf_s(contactInfo.argName[2], sizeof(contactInfo.argName[2]), "1pValue");
    sprintf_s(contactInfo.argName[3], sizeof(contactInfo.argName[3]), "dwType");
    sprintf_s(contactInfo.argName[4], sizeof(contactInfo.argName[4]), "pdwType");
    sprintf_s(contactInfo.argName[5], sizeof(contactInfo.argName[5]), "pvData");
    sprintf_s(contactInfo.argName[6], sizeof(contactInfo.argName[6]), "pcbData");

    sprintf_s(contactInfo.argValue[0], sizeof(contactInfo.argValue[0]), "%08X", hKey);
    memset(temp1, 0, sizeof(temp1));
    WideCharToMultiByte(CP_ACP, 0, lpSubKey, wcslen(lpSubKey), temp1, sizeof(temp1), NULL, NULL);
    strcpy(contactInfo.argValue[1], temp1);
    memset(temp2, 0, sizeof(temp2));
    WideCharToMultiByte(CP_ACP, 0, lpValue, wcslen(lpValue), temp2, sizeof(temp2), NULL, NULL);
    strcpy(contactInfo.argValue[2], temp2);
    sprintf_s(contactInfo.argValue[3], sizeof(contactInfo.argValue[3]), "%08X", dwType);
    sprintf_s(contactInfo.argValue[4], sizeof(contactInfo.argValue[4]), "%08X", pdwType);
    sprintf_s(contactInfo.argValue[5], sizeof(contactInfo.argValue[5]), "%08X", pvData);
    sprintf_s(contactInfo.argValue[6], sizeof(contactInfo.argValue[6]), "%08X", pcbData);

    contactInfo.type = REGGETVALUE;
    GetLocalTime(&(contactInfo.st));
    memcpy(MapFileBase, &contactInfo, sizeof(info));
    ReleaseSemaphore(hSemaphore, 1, NULL);

    fprintf(f, "\n\n****************************************\n");
    fprintf(f, "RegGetValue Hooked\n");
    GetLocalTime(&st);
    fprintf(f, "DLL日志输出：%d-%d-%d %02d: %02d: %02d: %03d\n", st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond, st.wMilliseconds);
    fprintf(f, "hKey: %08x\n", hKey);
    fprintf(f, "lpSubKey: %s\n", temp1);
    fprintf(f, "1pValue: %s\n", temp2);
    fprintf(f, "dwType: %08x\n", dwType);
    fprintf(f, "pdwType: %08x\n", pdwType);
    fprintf(f, "pvData: %08x\n", pvData);
    fprintf(f, "pcbData: %08x\n", pcbData);
    fprintf(f, "****************************************\n");

    Sleep(10);
    return OldRegGetValue(hKey, lpSubKey, lpValue, dwType, pdwType, pvData, pcbData);
}

static LSTATUS(WINAPI* OldRegCloseKey)(HKEY hKey) = RegCloseKey;

extern "C" __declspec(dllexport)LSTATUS WINAPI NewRegCloseKey(HKEY hKey)
{
    contactInfo.argNum = 1;

    sprintf_s(contactInfo.argName[0], sizeof(contactInfo.argName[0]), "hKey");

    sprintf_s(contactInfo.argValue[0], sizeof(contactInfo.argValue[0]), "%08X", hKey);

    contactInfo.type = REGCLOSEKEY;
    GetLocalTime(&(contactInfo.st));
    memcpy(MapFileBase, &contactInfo, sizeof(info));
    ReleaseSemaphore(hSemaphore, 1, NULL);

    fprintf(f, "\n\n****************************************\n");
    fprintf(f, "RegCloseKey Hooked\n");
    GetLocalTime(&st);
    fprintf(f, "DLL日志输出：%d-%d-%d %02d: %02d: %02d: %03d\n", st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond, st.wMilliseconds);
    fprintf(f, "hKey: %08x\n", hKey);
    fprintf(f, "****************************************\n");

    Sleep(10);
    return OldRegCloseKey(hKey);
}

static LSTATUS(WINAPI* OldRegOpenKeyEx)(
    HKEY    hKey,
    LPCWSTR lpSubKey,
    DWORD   ulOptions,
    REGSAM  samDesired,
    PHKEY   phkResult
    ) = RegOpenKeyEx;

extern "C" __declspec(dllexport)LSTATUS WINAPI NewRegOpenKeyEx(
    HKEY    hKey,
    LPCWSTR lpSubKey,
    DWORD   ulOptions,
    REGSAM  samDesired,
    PHKEY   phkResult
)
{
    char temp[70];
    contactInfo.argNum = 5;

    sprintf_s(contactInfo.argName[0], sizeof(contactInfo.argName[0]), "hKey");
    sprintf_s(contactInfo.argName[1], sizeof(contactInfo.argName[1]), "lpSubKey");
    sprintf_s(contactInfo.argName[2], sizeof(contactInfo.argName[2]), "ulOptions");
    sprintf_s(contactInfo.argName[3], sizeof(contactInfo.argName[3]), "samDesired");
    sprintf_s(contactInfo.argName[4], sizeof(contactInfo.argName[4]), "phkResult");

    sprintf_s(contactInfo.argValue[0], sizeof(contactInfo.argValue[0]), "%08X", hKey);
    memset(temp, 0, sizeof(temp));
    WideCharToMultiByte(CP_ACP, 0, lpSubKey, wcslen(lpSubKey), temp, sizeof(temp), NULL, NULL);
    strcpy(contactInfo.argValue[1], temp);
    sprintf_s(contactInfo.argValue[2], sizeof(contactInfo.argValue[2]), "%08X", ulOptions);
    sprintf_s(contactInfo.argValue[3], sizeof(contactInfo.argValue[3]), "%08X", samDesired);
    sprintf_s(contactInfo.argValue[4], sizeof(contactInfo.argValue[4]), "%08X", phkResult);

    contactInfo.type = REGOPENKEYEX;
    GetLocalTime(&(contactInfo.st));
    memcpy(MapFileBase, &contactInfo, sizeof(info));
    ReleaseSemaphore(hSemaphore, 1, NULL);

    fprintf(f, "\n\n****************************************\n");
    fprintf(f, "RegOpenKeyEx Hooked\n");
    GetLocalTime(&st);
    fprintf(f, "DLL日志输出：%d-%d-%d %02d: %02d: %02d: %03d\n", st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond, st.wMilliseconds);
    fprintf(f, "hKey: %08x\n", hKey);
    fprintf(f, "lpSubKey: %s\n", temp);
    fprintf(f, "ulOptions: %08x\n", ulOptions);
    fprintf(f, "samDesired: %08x\n", samDesired);
    fprintf(f, "phkResult: %08x\n", phkResult);
    fprintf(f, "****************************************\n");

    Sleep(10);
    return OldRegOpenKeyEx(hKey, lpSubKey, ulOptions, samDesired, phkResult);
}

static LSTATUS(WINAPI* OldRegDeleteValue)(
    HKEY    hKey,
    LPCWSTR lpValueName
    ) = RegDeleteValue;

extern "C" __declspec(dllexport)LSTATUS WINAPI NewRegDeleteValue(
    HKEY    hKey,
    LPCWSTR lpValueName
)
{
    char temp[70];
    contactInfo.argNum = 2;

    sprintf_s(contactInfo.argName[0], sizeof(contactInfo.argName[0]), "hKey");
    sprintf_s(contactInfo.argName[1], sizeof(contactInfo.argName[1]), "lpValueName");

    sprintf_s(contactInfo.argValue[0], sizeof(contactInfo.argValue[0]), "%08X", hKey);
    memset(temp, 0, sizeof(temp));
    WideCharToMultiByte(CP_ACP, 0, lpValueName, wcslen(lpValueName), temp, sizeof(temp), NULL, NULL);
    strcpy(contactInfo.argValue[1], temp);

    contactInfo.type = REGDELETEVALUE;
    GetLocalTime(&(contactInfo.st));
    memcpy(MapFileBase, &contactInfo, sizeof(info));
    ReleaseSemaphore(hSemaphore, 1, NULL);

    fprintf(f, "\n\n****************************************\n");
    fprintf(f, "RegDeleteValue Hooked\n");
    GetLocalTime(&st);
    fprintf(f, "DLL日志输出：%d-%d-%d %02d: %02d: %02d: %03d\n", st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond, st.wMilliseconds);
    fprintf(f, "hKey: %08x\n", hKey);
    fprintf(f, "lpValueName: %s\n", temp);
    fprintf(f, "****************************************\n");

    Sleep(10);
    return OldRegDeleteValue(hKey, lpValueName);
}


// 网络通信操作API截获
// Socket Operations(Create, Destroy, Free)

static SOCKET(WINAPI* Oldsocket)(
    int af,
    int type,
    int protocol
    ) = socket;

extern "C" __declspec(dllexport)SOCKET WINAPI Newsocket(int af, int type, int protocol) 
{
    contactInfo.argNum = 3;

    sprintf_s(contactInfo.argName[0], sizeof(contactInfo.argName[0]), "af");
    sprintf_s(contactInfo.argName[1], sizeof(contactInfo.argName[1]), "type");
    sprintf_s(contactInfo.argName[2], sizeof(contactInfo.argName[2]), "protocol");

    sprintf_s(contactInfo.argValue[0], sizeof(contactInfo.argValue[0]), "%08X", af);
    sprintf_s(contactInfo.argValue[1], sizeof(contactInfo.argValue[1]), "%08X", type);
    sprintf_s(contactInfo.argValue[2], sizeof(contactInfo.argValue[2]), "%08X", protocol);

    contactInfo.type = ASOCKET;
    GetLocalTime(&(contactInfo.st));
    memcpy(MapFileBase, &contactInfo, sizeof(info));
    ReleaseSemaphore(hSemaphore, 1, NULL);

    fprintf(f, "\n\n****************************************\n");
    fprintf(f, "socket Hooked\n");
    GetLocalTime(&st);
    fprintf(f, "DLL日志输出：%d-%d-%d %02d: %02d: %02d: %03d\n", st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond, st.wMilliseconds);
    fprintf(f, "af: %08x\n", af);
    fprintf(f, "type: %08x\n", type);
    fprintf(f, "protocol: %08x\n", protocol);
    fprintf(f, "****************************************\n");

    Sleep(10);
    return Oldsocket(af, type, protocol);
}

static int (WINAPI* Oldbind)(
    SOCKET         s,
    const sockaddr* name,
    int            namelen
    ) = bind;

extern "C" __declspec(dllexport)int WINAPI Newbind(SOCKET s, const sockaddr* name, int namelen)
{
    //name->sa_data
    contactInfo.argNum = 5;

    sprintf_s(contactInfo.argName[0], sizeof(contactInfo.argName[0]), "s");
    sprintf_s(contactInfo.argName[1], sizeof(contactInfo.argName[1]), "name");
    sprintf_s(contactInfo.argName[2], sizeof(contactInfo.argName[2]), "namelen");
    sprintf_s(contactInfo.argName[3], sizeof(contactInfo.argName[3]), "IP");
    sprintf_s(contactInfo.argName[4], sizeof(contactInfo.argName[4]), "port");

    sprintf_s(contactInfo.argValue[0], sizeof(contactInfo.argValue[0]), "%08X", s);
    sprintf_s(contactInfo.argValue[1], sizeof(contactInfo.argValue[1]), "%08X", name);
    sprintf_s(contactInfo.argValue[2], sizeof(contactInfo.argValue[2]), "%08X", namelen);
    struct sockaddr_in* sock = (struct sockaddr_in*)name;
    char addr[256] = { 0 };
    inet_ntop(AF_INET, sock, addr, sizeof(addr));
    int port = ntohs(sock->sin_port);
    sprintf_s(contactInfo.argValue[3], sizeof(contactInfo.argValue[3]), "%s", addr);
    sprintf_s(contactInfo.argValue[4], sizeof(contactInfo.argValue[4]), "%d", port);

    contactInfo.type = BIND;
    GetLocalTime(&(contactInfo.st));
    memcpy(MapFileBase, &contactInfo, sizeof(info));
    ReleaseSemaphore(hSemaphore, 1, NULL);

    fprintf(f, "\n\n****************************************\n");
    fprintf(f, "bind Hooked\n");
    GetLocalTime(&st);
    fprintf(f, "DLL日志输出：%d-%d-%d %02d: %02d: %02d: %03d\n", st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond, st.wMilliseconds);
    fprintf(f, "s: %08x\n", s);
    fprintf(f, "name: %08x\n", name);
    fprintf(f, "namelen: %08x\n", namelen);
    fprintf(f, "IP: %s\n", addr);
    fprintf(f, "port: %d\n", port);
    fprintf(f, "****************************************\n");
    
    Sleep(10);
    return Oldbind(s, name, namelen);
}

static int (WINAPI* Oldsend)(
    SOCKET     s,
    const char* buf,
    int        len,
    int        flags
    ) = send;

extern "C" __declspec(dllexport)int WINAPI Newsend(SOCKET s, const char* buf, int len, int flags)
{
    contactInfo.argNum = 5;

    sprintf_s(contactInfo.argName[0], sizeof(contactInfo.argName[0]), "s");
    sprintf_s(contactInfo.argName[1], sizeof(contactInfo.argName[1]), "buf");
    sprintf_s(contactInfo.argName[2], sizeof(contactInfo.argName[2]), "len");
    sprintf_s(contactInfo.argName[3], sizeof(contactInfo.argName[3]), "flags");
    sprintf_s(contactInfo.argName[4], sizeof(contactInfo.argName[4]), "data");

    sprintf_s(contactInfo.argValue[0], sizeof(contactInfo.argValue[0]), "%08X", s);
    sprintf_s(contactInfo.argValue[1], sizeof(contactInfo.argValue[1]), "%08X", buf);
    sprintf_s(contactInfo.argValue[2], sizeof(contactInfo.argValue[2]), "%08X", len);
    sprintf_s(contactInfo.argValue[3], sizeof(contactInfo.argValue[3]), "%08X", flags);
    sprintf_s(contactInfo.argValue[4], sizeof(contactInfo.argValue[4]), "%s", buf);

    contactInfo.type = SEND;
    GetLocalTime(&(contactInfo.st));
    memcpy(MapFileBase, &contactInfo, sizeof(info));
    ReleaseSemaphore(hSemaphore, 1, NULL);

    fprintf(f, "\n\n****************************************\n");
    fprintf(f, "send Hooked\n");
    GetLocalTime(&st);
    fprintf(f, "DLL日志输出：%d-%d-%d %02d: %02d: %02d: %03d\n", st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond, st.wMilliseconds);
    fprintf(f, "s: %08x\n", s);
    fprintf(f, "buf: %08x\n", buf);
    fprintf(f, "len: %08x\n", len);
    fprintf(f, "flags: %08x\n", flags);
    fprintf(f, "data: %s\n", buf);
    fprintf(f, "****************************************\n");

    Sleep(10);
    return Oldsend(s, buf, len, flags);
}

static int (WINAPI* Oldrecv)(
    SOCKET     s,
    char* buf,
    int        len,
    int        flags
    ) = recv;

extern "C" __declspec(dllexport)int WINAPI Newrecv(SOCKET s, char* buf, int len, int flags)
{

    contactInfo.argNum = 4;

    sprintf_s(contactInfo.argName[0], sizeof(contactInfo.argName[0]), "s");
    sprintf_s(contactInfo.argName[1], sizeof(contactInfo.argName[1]), "buf");
    sprintf_s(contactInfo.argName[2], sizeof(contactInfo.argName[2]), "len");
    sprintf_s(contactInfo.argName[3], sizeof(contactInfo.argName[3]), "flags");

    sprintf_s(contactInfo.argValue[0], sizeof(contactInfo.argValue[0]), "%08X", s);
    sprintf_s(contactInfo.argValue[1], sizeof(contactInfo.argValue[1]), "%08X", buf);
    sprintf_s(contactInfo.argValue[2], sizeof(contactInfo.argValue[2]), "%08X", len);
    sprintf_s(contactInfo.argValue[3], sizeof(contactInfo.argValue[3]), "%08X", flags);

    contactInfo.type = RECV;
    GetLocalTime(&(contactInfo.st));
    memcpy(MapFileBase, &contactInfo, sizeof(info));
    ReleaseSemaphore(hSemaphore, 1, NULL);

    fprintf(f, "\n\n****************************************\n");
    fprintf(f, "recv Hooked\n");
    GetLocalTime(&st);
    fprintf(f, "DLL日志输出：%d-%d-%d %02d: %02d: %02d: %03d\n", st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond, st.wMilliseconds);
    fprintf(f, "s: %08x\n", s);
    fprintf(f, "buf: %08x\n", buf);
    fprintf(f, "len: %08x\n", len);
    fprintf(f, "flags: %08x\n", flags);
    fprintf(f, "data: %s\n", buf);
    fprintf(f, "****************************************\n");

    Sleep(10);
    return Oldrecv(s, buf, len, flags);
}


// DllMain

BOOL APIENTRY DllMain(HMODULE hModule,
    DWORD  ul_reason_for_call,
    LPVOID lpReserved
)
{
    f = fopen("writeLog.txt", "a+");
    if (f == NULL) printf("error");
    else printf("log open successfully!\n");

    switch (ul_reason_for_call)
    {
        case DLL_PROCESS_ATTACH:
        {
            DisableThreadLibraryCalls(hModule);
            DetourTransactionBegin();
            DetourUpdateThread(GetCurrentThread());
            DetourAttach(&(PVOID&)OldMessageBoxW, NewMessageBoxW);
            DetourAttach(&(PVOID&)OldMessageBoxA, NewMessageBoxA);
            DetourAttach(&(PVOID&)OldCreateFile, NewCreateFile);
            DetourAttach(&(PVOID&)OldWriteFile, NewWriteFile);
            DetourAttach(&(PVOID&)OldReadFile, NewReadFile);
            DetourAttach(&(PVOID&)OldHeapCreate, NewHeapCreate);
            DetourAttach(&(PVOID&)OldHeapDestroy, NewHeapDestroy);
            DetourAttach(&(PVOID&)OldHeapFree, NewHeapFree);
            DetourAttach(&(PVOID&)OldRegCreateKeyEx, NewRegCreateKeyEx);
            DetourAttach(&(PVOID&)OldRegSetValueEx, NewRegSetValueEx);
            DetourAttach(&(PVOID&)OldRegGetValue, NewRegGetValue);
            DetourAttach(&(PVOID&)OldRegDeleteValue, NewRegDeleteValue);
            DetourAttach(&(PVOID&)OldRegCloseKey, NewRegCloseKey);
            DetourAttach(&(PVOID&)OldRegOpenKeyEx, NewRegOpenKeyEx);
            DetourAttach(&(PVOID&)Oldsocket, Newsocket);
            DetourAttach(&(PVOID&)Oldbind, Newbind);
            DetourAttach(&(PVOID&)Oldsend, Newsend);
            DetourAttach(&(PVOID&)Oldrecv, Newrecv);

            DetourTransactionCommit();
            break;
        }
        case DLL_THREAD_ATTACH:

        case DLL_THREAD_DETACH:

        case DLL_PROCESS_DETACH:
        {
            DetourTransactionBegin();
            DetourUpdateThread(GetCurrentThread());
            DetourDetach(&(PVOID&)OldMessageBoxW, NewMessageBoxW);
            DetourDetach(&(PVOID&)OldMessageBoxA, NewMessageBoxA);
            DetourDetach(&(PVOID&)OldCreateFile, NewCreateFile);
            DetourDetach(&(PVOID&)OldWriteFile, NewWriteFile);
            DetourDetach(&(PVOID&)OldReadFile, NewReadFile);
            DetourDetach(&(PVOID&)OldHeapCreate, NewHeapCreate);
            DetourDetach(&(PVOID&)OldHeapDestroy, NewHeapDestroy);
            DetourDetach(&(PVOID&)OldHeapFree, NewHeapFree);
            DetourDetach(&(PVOID&)OldRegCreateKeyEx, NewRegCreateKeyEx);
            DetourDetach(&(PVOID&)OldRegSetValueEx, NewRegSetValueEx);
            DetourDetach(&(PVOID&)OldRegGetValue, NewRegGetValue);
            DetourDetach(&(PVOID&)OldRegDeleteValue, NewRegDeleteValue);
            DetourDetach(&(PVOID&)OldRegCloseKey, NewRegCloseKey);
            DetourDetach(&(PVOID&)OldRegOpenKeyEx, NewRegOpenKeyEx);
            DetourDetach(&(PVOID&)Oldsocket, Newsocket);
            DetourDetach(&(PVOID&)Oldbind, Newbind);
            DetourDetach(&(PVOID&)Oldsend, Newsend);
            DetourDetach(&(PVOID&)Oldrecv, Newrecv);

            DetourTransactionCommit();

            UnmapViewOfFile(MapFileBase);
            CloseHandle(hMappingFile);
            break;
        }
    }
    return TRUE;
}