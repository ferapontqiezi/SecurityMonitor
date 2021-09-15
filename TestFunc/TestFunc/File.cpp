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
			printf("�´μ�!\n");
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

// �����ļ�ΪE:\\TestInitialNullForStudent\\InjectDll\\Debug\\writeFile.txt
void Create_File() {
	CHAR* pBuffer;
	int fileSize = 0;
	char writeString[100];
	bool flag;

	HANDLE hOpenFile = (HANDLE)CreateFile(L"E:\\TestInitialNullForStudent\\InjectDll\\Debug\\writeFile.txt", GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, NULL, NULL);
	if (hOpenFile == INVALID_HANDLE_VALUE)
	{
		hOpenFile = NULL;
		printf("CreateFileʧ��!\n");
		return;
	}
	printf("CreateFile�ɹ�![E:\\TestInitialNullForStudent\\InjectDll\\Debug\\writeFile.txt]\n");
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
		printf("CreateFileʧ��!\n");
		return;
	}
	printf("CreateFile�ɹ�![E:\\TestInitialNullForStudent\\InjectDll\\Debug\\writeFile.txt]\n");
	printf("�������ַ���:");
	scanf("%s", writeString);
	flag = WriteFile(hOpenFile, writeString, strlen(writeString), NULL, NULL);
	if (flag) {
		printf("WriteFile�ɹ�!\n");
		printf("����[E:\\TestInitialNullForStudent\\InjectDll\\Debug\\writeFile.txt]!\n");
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
		printf("���ܴ򿪸��ļ�!\n");
		return;
	}
	printf("OpenFile�ɹ�![E:\\TestInitialNullForStudent\\InjectDll\\Debug\\writeFile.txt]\n");
	fileSize = GetFileSize(hOpenFile, NULL);
	pBuffer = (char*)malloc((fileSize + 1) * sizeof(char));
	flag = ReadFile(hOpenFile, pBuffer, fileSize, NULL, NULL);
	pBuffer[fileSize] = 0;
	if (flag) {
		printf("�ɹ���ȡ�����ַ���: %s!\n", pBuffer);
	}
	free(pBuffer);
	CloseHandle(hOpenFile);
}