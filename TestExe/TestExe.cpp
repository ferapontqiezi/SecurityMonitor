#include<stdio.h>
#include<stdlib.h>
#include<windows.h>

#pragma comment(lib, "ws2_32.lib")  //加载 ws2_32.dll
#pragma warning(disable: 4996)

#define PAGE_SIZE 2048

using namespace std;

void heapCreateAndDestory();
void writeFileString();
void readFileString();
void regCreateAndSetValue();
void regOpenAndDelValue();
void showMenu();
void heapRepeatedRelease();
void modifyExeProgram();
void selfReplication();
void modifyStartupRegistry();
void openAnotherFolder();
void recvData();
void sendData();
void memoryOperation();

int main() {
	int op = 0;
	while (true) {
		showMenu();
		scanf("%d", &op);
		switch (op)
		{
		case 0: {
			printf("bye!\n");
			break;
		}
		case 1: {
			MessageBoxA(NULL, "I'm MessageBoxA", "I'm MessageBoxA's title", MB_OK);
			break;
		}
		case 2: {
			MessageBoxW(NULL, L"I'm MessageBoxW", L"I'm MessageBoxW's title", MB_OK);
			break;
		}
		case 3: {
			heapCreateAndDestory();
			break;
		}
		case 4: {
			writeFileString();
			break;
		}
		case 5: {
			readFileString();
			break;
		}
		case 6: {
			regCreateAndSetValue();
			break;
		}
		case 7: {
			regOpenAndDelValue();
			break;
		}
		case 8: {
			recvData();
			break;
		}
		case 9: {
			sendData();
			break;
		}
		case 10: {
			heapRepeatedRelease();
			break;
		}
		case 11: {
			modifyExeProgram();
			break;
		}
		case 12: {
			selfReplication();
			break;
		}
		case 13: {
			modifyStartupRegistry();
			break;
		}
		case 14: {
			openAnotherFolder();
			break;
		}
		case 15: {
			memoryOperation();
			break;
		}
		}

		if (op == 0) {
			break;
		}
	}
	return 0;
}

void showMenu() {
	printf("\n\n");
	printf("---------------------------The Menu for Testing Functions------------------------------\n");
	printf("Normal operations:\n");
	printf("1.MessageBoxA      2.MessageBoxW            3.heapCreateAndDestory   4.writeFileString\n");
	printf("5.readFileString   6.regCreateAndSetValue   7.regOpenAndDelValue     8.socketRecvData\n");
	printf("9.socketSendData\n");
	printf("Dangered operations:\n");
	printf("10.heapRepeatedRelease   11.modifyExeFile    12.selfReplication\n");
	printf("13.modifyStartupRegistry   14.openAnotherFolder\n");
	printf("Please input the number to choose the function(1~14): \n");
}

void heapCreateAndDestory() {

	printf("Press any key to start HeapCreate!\n");
	getchar();
	HANDLE hHeap = HeapCreate(HEAP_NO_SERIALIZE, PAGE_SIZE * 10, PAGE_SIZE * 100);

	int* pArr = (int*)HeapAlloc(hHeap, 0, sizeof(int) * 30);
	for (int i = 0; i < 30; ++i)
	{
		pArr[i] = i + 1;
	}
	printf("Successfully create a heap!\n");
	for (int i = 0; i < 30; ++i)
	{
		if (i % 5 == 0)
			printf_s("\n");
		printf("%3d ", pArr[i]);
	}
	printf_s("\n\n");
	printf("Press any key to start HeapFree!\n");
	getchar();
	HeapFree(hHeap, 0, pArr);
	printf("Successfully free the heap!\n");

	printf("Press any key to start HeapDestory!\n");
	getchar();
	HeapDestroy(hHeap);
	printf("Successfully destory the heap!\n");
}

void writeFileString()
{
	CHAR* pBuffer;
	int fileSize = 0;
	char writeString[100];
	bool flag;
	// 测试文件为E:\\TestInitialNullForStudent\\InjectDll\\Debug\\writeFile.txt
	HANDLE hOpenFile = (HANDLE)CreateFile(L"E:\\TestInitialNullForStudent\\InjectDll\\Debug\\writeFile.txt", GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, NULL, NULL);
	if (hOpenFile == INVALID_HANDLE_VALUE)
	{
		hOpenFile = NULL;
		printf("Can not open the file!\n");
		return;
	}
	printf("Successfully open the file![E:\\TestInitialNullForStudent\\InjectDll\\Debug\\writeFile.txt]\n");
	printf("Please input a string:");
	scanf("%s", writeString);
	flag = WriteFile(hOpenFile, writeString, strlen(writeString), NULL, NULL);
	if (flag) {
		printf("Successfully write the file!\n");
		printf("Please go to [E:\\TestInitialNullForStudent\\InjectDll\\Debug\\writeFile.txt] to look the result!\n");
	}
	FlushFileBuffers(hOpenFile);
	CloseHandle(hOpenFile);
}

void readFileString() {
	CHAR* pBuffer;
	int fileSize = 0;
	bool flag;
	HANDLE hOpenFile = (HANDLE)CreateFile(L"E:\\TestInitialNullForStudent\\InjectDll\\Debug\\writeFile.txt", GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_ALWAYS, NULL, NULL);
	if (hOpenFile == INVALID_HANDLE_VALUE)
	{
		hOpenFile = NULL;
		printf("Can not open the file!\n");
		return;
	}
	printf("Successfully open the file![E:\\TestInitialNullForStudent\\InjectDll\\Debug\\writeFile.txt]\n");
	fileSize = GetFileSize(hOpenFile, NULL);
	pBuffer = (char*)malloc((fileSize + 1) * sizeof(char));
	flag = ReadFile(hOpenFile, pBuffer, fileSize, NULL, NULL);
	pBuffer[fileSize] = 0;
	if (flag) {
		printf("Successfully read a string: %s!\n", pBuffer);
	}
	free(pBuffer);
	CloseHandle(hOpenFile);
}

void regCreateAndSetValue() 
{
	// 创建注册表并设置键值
	HKEY hKey = NULL;
	TCHAR Data[256];
	memset(Data, 0, sizeof(Data));
	wcsncpy_s(Data, TEXT("http://cse.hust.edu.cn/"), 256);

	size_t lRet = RegCreateKeyEx(HKEY_CURRENT_USER, (LPWSTR)L"aTestKeyForCreate", 0, NULL, REG_OPTION_NON_VOLATILE,
		KEY_ALL_ACCESS, NULL, &hKey, NULL);
	if (lRet == ERROR_SUCCESS) {
		printf("Create regValue successfully!\n");
	}
	else {
		printf("Fail to create!\n");
	}
	// 修改注册表键值，没有则创建它
	size_t iLen = wcslen(Data);
	// 设置键值
	lRet = RegSetValueEx(hKey, L"aTestKeyForSet", 0, REG_SZ, (CONST BYTE*)Data, sizeof(TCHAR) * iLen);
	if (lRet == ERROR_SUCCESS)
	{
		printf("Set regValue successfully!\n");
		return;
	}
	else {
		printf("Fail to set value!\n");
	}
	RegCloseKey(hKey);
}

void regOpenAndDelValue() {
	HKEY hKey = NULL;
	size_t lRet = RegOpenKeyEx(HKEY_CURRENT_USER, (LPWSTR)L"aTestKeyForCreate", 0, KEY_ALL_ACCESS, &hKey);
	if (lRet == ERROR_SUCCESS) {
		printf("Open successfully!\n");
	}
	else {
		printf("Open failed!\n");
	}
	lRet = RegDeleteValue(hKey, L"aTestKeyForSet");
	if (lRet == ERROR_SUCCESS) {
		printf("Delete successfully!\n");
	}
	else {
		printf("Fail to delete!\n");
	}
	RegCloseKey(hKey);
}

void heapRepeatedRelease() {

	printf("Press any key to start HeapCreate!\n");
	getchar();
	HANDLE hHeap = HeapCreate(HEAP_NO_SERIALIZE, PAGE_SIZE * 10, PAGE_SIZE * 100);

	int* pArr = (int*)HeapAlloc(hHeap, 0, sizeof(int) * 30);
	for (int i = 0; i < 30; ++i)
	{
		pArr[i] = i + 1;
	}
	printf("Successfully create!\n");
	for (int i = 0; i < 30; ++i)
	{
		if (i % 5 == 0)
			printf_s("\n");
		printf("%3d ", pArr[i]);
	}
	printf_s("\n\n");
	printf("Press any key to start the first HeapFree!\n");
	getchar();
	HeapFree(hHeap, 0, pArr);
	printf("Press any key to start the second HeapFree!\n");
	getchar();
	HeapFree(hHeap, 0, pArr);
	printf("Press any key to destroy the heap!\n");
	getchar();
	HeapDestroy(hHeap);
}

void modifyExeProgram() {
	// 测试文件为E:\\TestInitialNullForStudent\\InjectDll\\Debug\\modifyExe.exe
	HANDLE hOpenFile = (HANDLE)CreateFile(L"E:\\TestInitialNullForStudent\\InjectDll\\Debug\\modifyExe.exe", GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, NULL, NULL);
	CloseHandle(hOpenFile);
}

void selfReplication() {
	// TestExe自我复制
	HANDLE hOpenFile = (HANDLE)CreateFile(L"TestExe.exe", GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_ALWAYS, NULL, NULL);
	CloseHandle(hOpenFile);
}

void modifyStartupRegistry() {
	HKEY hKey = NULL;
	size_t lRet = RegOpenKeyEx(HKEY_CURRENT_USER, (LPWSTR)L"SOFTWARE\Microsoft\Windows\CurrentVersion\Run", 0, KEY_READ, &hKey);
	if (lRet == ERROR_SUCCESS) {
		printf("Open StartupRegistry Successfully!\n");
	}
	else {
		printf("Fail to open the StartupRegistry!\n");
	}
	RegCloseKey(hKey);
}

void openAnotherFolder() {
	HANDLE hOpenFile = (HANDLE)CreateFile(L"E:\\TestInitialNullForStudent\\openAnotherFolder.txt", GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, NULL, NULL);
	CloseHandle(hOpenFile);
}

void recvData() {
	//初始化DLL
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);
	//创建套接字
	SOCKET sock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	//向服务器发起请求
	sockaddr_in sockAddr;
	memset(&sockAddr, 0, sizeof(sockAddr));  //每个字节都用0填充
	sockAddr.sin_family = PF_INET;
	sockAddr.sin_addr.s_addr = inet_addr("127.0.0.1");
	sockAddr.sin_port = htons(1234);
	connect(sock, (SOCKADDR*)&sockAddr, sizeof(SOCKADDR));
	Sleep(500);
	//接收服务器传回的数据
	char szBuffer[MAXBYTE] = { 0 };
	recv(sock, szBuffer, MAXBYTE, NULL);
	//输出接收到的数据
	printf("The message from the server: %s\n", szBuffer);
	//关闭套接字
	closesocket(sock);
	//终止使用 DLL
	WSACleanup();
}

void sendData() {
	//初始化 DLL
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);
	//创建套接字
	SOCKET servSock = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	//绑定套接字
	sockaddr_in sockAddr;
	memset(&sockAddr, 0, sizeof(sockAddr));  //每个字节都用0填充
	sockAddr.sin_family = PF_INET;  //使用IPv4地址
	sockAddr.sin_addr.s_addr = inet_addr("127.0.0.1");  //具体的IP地址
	sockAddr.sin_port = htons(1234);  //端口
	bind(servSock, (SOCKADDR*)&sockAddr, sizeof(SOCKADDR));
	//进入监听状态
	listen(servSock, 20);
	//接收客户端请求
	SOCKADDR clntAddr;
	int nSize = sizeof(SOCKADDR);
	SOCKET clntSock = accept(servSock, (SOCKADDR*)&clntAddr, &nSize);
	//向客户端发送数据
	char str[32] = "Hello World!";
	send(clntSock, str, strlen(str) + sizeof(char), NULL);
	//关闭套接字
	closesocket(clntSock);
	closesocket(servSock);
	//终止 DLL 的使用
	WSACleanup();
}

void memoryOperation() {
	getchar();
	char temp[100] = "";
	printf("Press any key to copy the memory!\n");
	getchar();
	memcpy(temp, "Hello \n", 6);
	printf("%s", temp);
	printf("Press any key to move the memory!\n");
	getchar();
	memmove(temp, "World!\n", 6);
	printf("%s", temp);
}