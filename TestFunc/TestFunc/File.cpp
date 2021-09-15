#include "head.h"

void showMenuF();
void Create_File();
void Write_File();
void Read_File();

int main() {
	int op = 0;
	while (true) {
		showMenuF();
		scanf("%d", &op);
		switch (op)
		{
		case 0: {
			printf("下次见!\n");
			break;
		}
		case 1: {
			Create_File();
			break;
		}
		case 2: {
			Write_File();
			break;
		}
		case 3: {
			Read_File();
			break;
		}
		}

		if (op == 0) {
			break;
		}
	}
	return 0;
}

void showMenuF() {
	printf("\n\n");
	printf("-------The Menu for Testing File Functions------\n");
	printf("1.CreateFile      2.WriteFile        3.ReadFile\n ");
}

// 测试文件为E:\\TestInitialNullForStudent\\InjectDll\\Debug\\writeFile.txt
void Create_File() {
	CHAR* pBuffer;
	int fileSize = 0;
	char writeString[100];
	bool flag;

	HANDLE hOpenFile = (HANDLE)CreateFile(L"E:\\TestInitialNullForStudent\\InjectDll\\Debug\\writeFile.txt", GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, NULL, NULL);
	if (hOpenFile == INVALID_HANDLE_VALUE)
	{
		hOpenFile = NULL;
		printf("CreateFile失败!\n");
		return;
	}
	printf("CreateFile成功![E:\\TestInitialNullForStudent\\InjectDll\\Debug\\writeFile.txt]\n");
}

void Write_File() {
	CHAR* pBuffer;
	int fileSize = 0;
	char writeString[100];
	bool flag;

	HANDLE hOpenFile = (HANDLE)CreateFile(L"E:\\TestInitialNullForStudent\\InjectDll\\Debug\\writeFile.txt", GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, NULL, NULL);
	if (hOpenFile == INVALID_HANDLE_VALUE)
	{
		hOpenFile = NULL;
		printf("CreateFile失败!\n");
		return;
	}
	printf("CreateFile成功![E:\\TestInitialNullForStudent\\InjectDll\\Debug\\writeFile.txt]\n");
	printf("请输入字符串:");
	scanf("%s", writeString);
	flag = WriteFile(hOpenFile, writeString, strlen(writeString), NULL, NULL);
	if (flag) {
		printf("WriteFile成功!\n");
		printf("请检查[E:\\TestInitialNullForStudent\\InjectDll\\Debug\\writeFile.txt]!\n");
	}
	FlushFileBuffers(hOpenFile);
	CloseHandle(hOpenFile);
}

void Read_File() {
	CHAR* pBuffer;
	int fileSize = 0;
	bool flag;
	HANDLE hOpenFile = (HANDLE)CreateFile(L"E:\\TestInitialNullForStudent\\InjectDll\\Debug\\writeFile.txt", GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_ALWAYS, NULL, NULL);
	if (hOpenFile == INVALID_HANDLE_VALUE)
	{
		hOpenFile = NULL;
		printf("不能打开该文件!\n");
		return;
	}
	printf("OpenFile成功![E:\\TestInitialNullForStudent\\InjectDll\\Debug\\writeFile.txt]\n");
	fileSize = GetFileSize(hOpenFile, NULL);
	pBuffer = (char*)malloc((fileSize + 1) * sizeof(char));
	flag = ReadFile(hOpenFile, pBuffer, fileSize, NULL, NULL);
	pBuffer[fileSize] = 0;
	if (flag) {
		printf("成功读取如下字符串: %s!\n", pBuffer);
	}
	free(pBuffer);
	CloseHandle(hOpenFile);
}