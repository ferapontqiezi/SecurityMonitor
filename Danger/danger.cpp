#include<stdio.h>
#include<stdlib.h>
#include<windows.h>

#pragma comment(lib, "ws2_32.lib")
#pragma warning(disable: 4996)

#define MAXSIZE 2048

using namespace std;

void showMenuD();
void Modify_Executable();
void Heap_Free_Repeat();
void Open_Other_Folder();
void Self_Replication();
void Modify_StartUp_Registry();


int main() {
	int op = 0;
	while (true) {
		showMenuD();
		scanf("%d", &op);
		switch (op)
		{
		case 0: {
			printf("bye!\n");
			break;
		}
		case 1: {
			Modify_Executable();
			break;
		}
		case 2: {
			Heap_Free_Repeat();
			break;
		}
		case 3: {
			Open_Other_Folder();
			break;
		}
		case 4: {
			Self_Replication();
			break;
		}
		case 5: {
			Modify_StartUp_Registry();
			break;
		}
		}

		if (op == 0) {
			break;
		}
	}
	return 0;
}

void showMenuD() {
	printf("\n\n");
	printf("----------------The Menu for Testing Danger Functions---------------\n");
	printf("1.修改可执行文件            2.堆重复释放               3.打开其他文件夹\n");
	printf("4.自我复制行为              5.修改StartUp注册表项      \n");
}

void Modify_Executable() {
	// 测试文件为E:\CodeC++\dust.exe
	// 如果打开了EXE文件就标记为是可能的修改EXE的危险操作
	HANDLE hOpenFile = (HANDLE)CreateFile(L"E:\\CodeC++\\dust.exe", GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, NULL, NULL);
	if (hOpenFile == INVALID_HANDLE_VALUE)
	{
		hOpenFile = NULL;
		printf("修改E:\\CodeC++\\dust.exe失败!\n");
		return;
	}
	printf("修改E:\\CodeC++\\dust.exe成功!\n");
	CloseHandle(hOpenFile);
}

void Heap_Free_Repeat() {

	printf("按任意键开始HeapCreate!\n");
	getchar();
	getchar();
	HANDLE hHeap = HeapCreate(HEAP_NO_SERIALIZE, MAXSIZE * 10, MAXSIZE * 100);
	int* heapAdress = (int*)HeapAlloc(hHeap, 0, sizeof(int) * 30);
	printf("\nHeapCreate成功!\n");
	// 重复释放堆，多次HeapFree()
	printf("下面开始重复释放堆操作：HeapFree!\n");
	printf("按任意键开始第1次HeapFree!\n");
	getchar();
	getchar();
	HeapFree(hHeap, 0, heapAdress);
	printf("按任意键开始第2次HeapFree!\n");
	getchar();
	getchar();
	HeapFree(hHeap, 0, heapAdress);
	printf("按任意键开始HeapDestroy!\n");
	getchar();
	getchar();
	HeapDestroy(hHeap);
}

void Open_Other_Folder() {
	// 用CreateFile句柄来实现创建文件C:\Drivers\OpenOtherFolder.txt
	// 达到去访问C盘其他文件夹的目的（危险行为）
	HANDLE hOpenFile = (HANDLE)CreateFile(L"C:\\Drivers\\OpenOtherFolder.txt", GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, NULL, NULL);
	printf("打开C:\\Drivers文件夹成功!\n");
	printf("创建C:\\Drivers\\OpenOtherFolder.txt文件成功!\n");
	CloseHandle(hOpenFile);
}

void Self_Replication() {
	// 测试文件为E:\TestInitialNullForStudent\InjectDll\Debug\Danger.exe
	// 如果打开了EXE文件就标记为是可能的复制EXE的危险操作
	HANDLE hOpenFile = (HANDLE)CreateFile(L"E:\\TestInitialNullForStudent\\InjectDll\\Debug\\Danger.exe", GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_ALWAYS, NULL, NULL);
	printf("自我复制成功!\n");
	CloseHandle(hOpenFile);
}

void Modify_StartUp_Registry() {
	// 启动项为HKEY_CURRENT_USER的SOFTWARE\Microsoft\Windows\CurrentVersion\Run
	HKEY hKey = NULL;
	size_t lRet = RegOpenKeyEx(HKEY_CURRENT_USER, (LPWSTR)L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run", 0, KEY_READ, &hKey);
	if (lRet == ERROR_SUCCESS) {
		printf("成功打开了StartUp注册表!\n");
	}
	else {
		printf("打开StartUp注册表失败!\n");
	}
	RegCloseKey(hKey);
}

