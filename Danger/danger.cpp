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
	printf("1.�޸Ŀ�ִ���ļ�            2.���ظ��ͷ�               3.�������ļ���\n");
	printf("4.���Ҹ�����Ϊ              5.�޸�StartUpע�����      \n");
}

void Modify_Executable() {
	// �����ļ�ΪE:\CodeC++\dust.exe
	// �������EXE�ļ��ͱ��Ϊ�ǿ��ܵ��޸�EXE��Σ�ղ���
	HANDLE hOpenFile = (HANDLE)CreateFile(L"E:\\CodeC++\\dust.exe", GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, NULL, NULL);
	if (hOpenFile == INVALID_HANDLE_VALUE)
	{
		hOpenFile = NULL;
		printf("�޸�E:\\CodeC++\\dust.exeʧ��!\n");
		return;
	}
	printf("�޸�E:\\CodeC++\\dust.exe�ɹ�!\n");
	CloseHandle(hOpenFile);
}

void Heap_Free_Repeat() {

	printf("���������ʼHeapCreate!\n");
	getchar();
	getchar();
	HANDLE hHeap = HeapCreate(HEAP_NO_SERIALIZE, MAXSIZE * 10, MAXSIZE * 100);
	int* heapAdress = (int*)HeapAlloc(hHeap, 0, sizeof(int) * 30);
	printf("\nHeapCreate�ɹ�!\n");
	// �ظ��ͷŶѣ����HeapFree()
	printf("���濪ʼ�ظ��ͷŶѲ�����HeapFree!\n");
	printf("���������ʼ��1��HeapFree!\n");
	getchar();
	getchar();
	HeapFree(hHeap, 0, heapAdress);
	printf("���������ʼ��2��HeapFree!\n");
	getchar();
	getchar();
	HeapFree(hHeap, 0, heapAdress);
	printf("���������ʼHeapDestroy!\n");
	getchar();
	getchar();
	HeapDestroy(hHeap);
}

void Open_Other_Folder() {
	// ��CreateFile�����ʵ�ִ����ļ�C:\Drivers\OpenOtherFolder.txt
	// �ﵽȥ����C�������ļ��е�Ŀ�ģ�Σ����Ϊ��
	HANDLE hOpenFile = (HANDLE)CreateFile(L"C:\\Drivers\\OpenOtherFolder.txt", GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, NULL, NULL);
	printf("��C:\\Drivers�ļ��гɹ�!\n");
	printf("����C:\\Drivers\\OpenOtherFolder.txt�ļ��ɹ�!\n");
	CloseHandle(hOpenFile);
}

void Self_Replication() {
	// �����ļ�ΪE:\TestInitialNullForStudent\InjectDll\Debug\Danger.exe
	// �������EXE�ļ��ͱ��Ϊ�ǿ��ܵĸ���EXE��Σ�ղ���
	HANDLE hOpenFile = (HANDLE)CreateFile(L"E:\\TestInitialNullForStudent\\InjectDll\\Debug\\Danger.exe", GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_ALWAYS, NULL, NULL);
	printf("���Ҹ��Ƴɹ�!\n");
	CloseHandle(hOpenFile);
}

void Modify_StartUp_Registry() {
	// ������ΪHKEY_CURRENT_USER��SOFTWARE\Microsoft\Windows\CurrentVersion\Run
	HKEY hKey = NULL;
	size_t lRet = RegOpenKeyEx(HKEY_CURRENT_USER, (LPWSTR)L"SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run", 0, KEY_READ, &hKey);
	if (lRet == ERROR_SUCCESS) {
		printf("�ɹ�����StartUpע���!\n");
	}
	else {
		printf("��StartUpע���ʧ��!\n");
	}
	RegCloseKey(hKey);
}

