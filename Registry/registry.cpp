#include<stdio.h>
#include<stdlib.h>
#include<windows.h>

#pragma comment(lib, "ws2_32.lib")
#pragma warning(disable: 4996)

using namespace std;

void showMenuR();
void Reg_Create_KeyEx();
void Reg_Set_ValueEx();
void Reg_Open_KeyEx();
void Reg_Close_Key();
void Reg_Get_Value();
void Reg_Delete_Value();


int main() {
	int op = 0;
	while (true) {
		showMenuR();
		scanf("%d", &op);
		switch (op)
		{
		case 0: {
			printf("�´μ�!\n");
			break;
		}
		case 1: {
			Reg_Create_KeyEx();
			break;
		}
		case 2: {
			Reg_Set_ValueEx();
			break;
		}
		case 3: {
			Reg_Open_KeyEx();
			break;
		}
		case 4: {
			Reg_Close_Key();
			break;
		}
		case 5: {
			Reg_Get_Value();
			break;
		}
		case 6: {
			Reg_Delete_Value();
			break;
		}
		}

		if (op == 0) {
			break;
		}
	}
	return 0;
}

void showMenuR() {
	printf("\n\n");
	printf("---------The Menu for Testing Registry Functions----------\n");
	printf("1.Reg_Create_KeyEx    2.Reg_Set_ValueEx    3.Reg_Open_KeyEx\n");
	printf("4.Reg_Close_Key       5.Reg_Get_Value      6.Reg_Delete_Value\n");
}

void Reg_Create_KeyEx()
{
	// ����ע������ü�ֵ
	HKEY hKey = NULL;

	size_t lRet = RegCreateKeyEx(HKEY_CURRENT_USER, (LPWSTR)L"AaaaTest", 0, NULL, REG_OPTION_NON_VOLATILE,
		KEY_ALL_ACCESS, NULL, &hKey, NULL);
	if (lRet == ERROR_SUCCESS) {
		printf("�ɹ�����ע���!\n");
	}
	else {
		printf("����ע���ʧ��!\n");
	}
}

void Reg_Set_ValueEx() {
	// ����ע������ü�ֵ
	HKEY hKey = NULL;
	TCHAR Data[256];
	memset(Data, 0, sizeof(Data));
	wcsncpy_s(Data, TEXT("http://cse.hust.edu.cn/"), 256);
	size_t lRet = RegCreateKeyEx(HKEY_CURRENT_USER, (LPWSTR)L"AaaaTest", 0, NULL, REG_OPTION_NON_VOLATILE,
		KEY_ALL_ACCESS, NULL, &hKey, NULL);
	// �޸�ע����ֵ��û���򴴽���
	size_t iLen = wcslen(Data);
	// ���ü�ֵ
	lRet = RegSetValueEx(hKey, L"TestName", 0, REG_SZ, (CONST BYTE*)Data, sizeof(TCHAR) * iLen);
	if (lRet == ERROR_SUCCESS)
	{
		printf("ע������ü�ֵ�ɹ�!\n");
		return;
	}
	else {
		printf("ע������ü�ֵʧ��!\n");
	}
	RegCloseKey(hKey);
}

void Reg_Open_KeyEx() {
	HKEY hKey = NULL;
	size_t lRet = RegOpenKeyEx(HKEY_CURRENT_USER, (LPWSTR)L"AaaaTest", 0, KEY_ALL_ACCESS, &hKey);
	if (lRet == ERROR_SUCCESS) {
		printf("�ɹ���ע���!\n");
	}
	else {
		printf("��ע���ʧ��!\n");
	}
}

void Reg_Close_Key() {
	HKEY hKey = NULL;
	size_t lRet = RegOpenKeyEx(HKEY_CURRENT_USER, (LPWSTR)L"AaaaTest", 0, KEY_ALL_ACCESS, &hKey);
	if (lRet == ERROR_SUCCESS) {
		printf("�ɹ���ע���!\n");
	}
	else {
		printf("��ע���ʧ��!\n");
	}
	RegCloseKey(hKey);
	printf("�ɹ��ر�ע���!\n");
}

void Reg_Get_Value() {
	TCHAR Data[256];
	memset(Data, 0, sizeof(Data));
	size_t len = 256;
	size_t type = REG_SZ;
	size_t r2 = RegGetValue(HKEY_CURRENT_USER, (LPWSTR)L"AaaaTest", L"TestName", RRF_RT_REG_SZ, (LPDWORD)&type, Data, (LPDWORD)&len);
	if (r2 == ERROR_SUCCESS) {
		printf("�ɹ���ȡע���ֵ!\n");
		wprintf(L"%ls", Data);
	}
	else {
		printf("��ȡע���ֵʧ��!\n");
	}
}

void Reg_Delete_Value() {
	HKEY hKey = NULL;
	size_t lRet = RegOpenKeyEx(HKEY_CURRENT_USER, (LPWSTR)L"AaaaTest", 0, KEY_ALL_ACCESS, &hKey);
	if (lRet == ERROR_SUCCESS) {
		printf("�ɹ���ע���!\n");
	}
	else {
		printf("��ע���ʧ��!\n");
	}
	lRet = RegDeleteValue(hKey, (LPWSTR)L"TestName");
	if (lRet == ERROR_SUCCESS) {
		printf("�ɹ�ɾ��ע���value!\n");
	}
	else {
		printf("ɾ��ע���valueʧ��!\n");
	}
	RegCloseKey(hKey);
}