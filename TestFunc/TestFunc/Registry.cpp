#include "head.h"

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
			printf("下次见!\n");
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
	// 创建注册表并设置键值
	HKEY hKey = NULL;

	size_t lRet = RegCreateKeyEx(HKEY_CURRENT_USER, (LPWSTR)L"AaaaTest", 0, NULL, REG_OPTION_NON_VOLATILE,
		KEY_ALL_ACCESS, NULL, &hKey, NULL);
	if (lRet == ERROR_SUCCESS) {
		printf("成功创建注册表!\n");
	}
	else {
		printf("创建注册表失败!\n");
	}
}

void Reg_Set_ValueEx(){
    // 创建注册表并设置键值
	HKEY hKey = NULL;
	TCHAR Data[256];
	memset(Data, 0, sizeof(Data));
	wcsncpy_s(Data, TEXT("http://cse.hust.edu.cn/"), 256);
	size_t lRet = RegCreateKeyEx(HKEY_CURRENT_USER, (LPWSTR)L"AaaaTest", 0, NULL, REG_OPTION_NON_VOLATILE,
		KEY_ALL_ACCESS, NULL, &hKey, NULL);
	// 修改注册表键值，没有则创建它
	size_t iLen = wcslen(Data);
	// 设置键值
	lRet = RegSetValueEx(hKey, L"AaaaTest", 0, REG_SZ, (CONST BYTE*)Data, sizeof(TCHAR) * iLen);
	if (lRet == ERROR_SUCCESS)
	{
		printf("Set regValue成功!\n");
		return;
	}
	else {
		printf("set regValue失败!\n");
	}
	RegCloseKey(hKey);
}

void Reg_Open_KeyEx() {
	HKEY hKey = NULL;
	size_t lRet = RegOpenKeyEx(HKEY_CURRENT_USER, (LPWSTR)L"AaaaTest", 0, KEY_ALL_ACCESS, &hKey);
	if (lRet == ERROR_SUCCESS) {
		printf("成功打开注册表!\n");
	}
	else {
		printf("打开注册表失败!\n");
	}
}

void Reg_Close_Key() {
	HKEY hKey = NULL;
	size_t lRet = RegOpenKeyEx(HKEY_CURRENT_USER, (LPWSTR)L"AaaaTest", 0, KEY_ALL_ACCESS, &hKey);
	if (lRet == ERROR_SUCCESS) {
		printf("成功打开注册表!\n");
	}
	else {
		printf("打开注册表失败!\n");
	}
    RegCloseKey(hKey);
    printf("成功关闭注册表!\n");
}

void Reg_Get_Value() {
    TCHAR Data[256];
    memset(Data, 0, sizeof(Data));
	size_t len = 256;
	size_t type = REG_SZ;
	size_t r2 = RegGetValue(HKEY_CURRENT_USER, (LPWSTR)L"AaaaTest", L"ZhangYunpeng", RRF_RT_REG_SZ,(LPDWORD)&type, Data, (LPDWORD)&len);
    if(r2 == ERROR_SUCCESS) {
        printf("成功获取注册表值!\n");
        wprintf(L"%ls", Data);
    }
    else {
        printf("获取注册表值失败!\n");
    }
}

void Reg_Delete_Value() {
    HKEY hKey = NULL;
	size_t lRet = RegOpenKeyEx(HKEY_CURRENT_USER, (LPWSTR)L"AaaaTest", 0, KEY_ALL_ACCESS, &hKey);
	if (lRet == ERROR_SUCCESS) {
		printf("成功打开注册表!\n");
	}
	else {
		printf("打开注册表失败!\n");
	}
	lRet = RegDeleteValue(hKey, (LPWSTR)L"AaaaTest");
	if (lRet == ERROR_SUCCESS) {
		printf("成功删除注册表value!\n");
	}
	else {
		printf("删除注册表value失败!\n");
	}
	RegCloseKey(hKey);
}