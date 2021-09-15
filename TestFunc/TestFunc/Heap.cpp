#include "head.h"

void showMenuH();
void Heap_Create();
void Heap_Free();
void Heap_Destroy();

int main() {
	int op = 0;
	while (true) {
		showMenuH();
		scanf("%d", &op);
		switch (op)
		{
		case 0: {
			printf("下次见!\n");
			break;
		}
		case 1: {
			Heap_Create();
			break;
		}
		case 2: {
			Heap_Free();
			break;
		}
		case 3: {
			Heap_Destroy();
			break; 
		}
		}

		if (op == 0) {
			break;
		}
	}
	return 0;
}

void showMenuH() {
	printf("\n\n");
	printf("-------The Menu for Testing Heap Functions------\n");
	printf("1.HeapCreate      2.HeapFree        3.HeapDestory\n ");
}

void Heap_Create() {
	printf("按任意键开始HeapCreate!\n");
	getchar();
	getchar();
	HANDLE hHeap = HeapCreate(HEAP_NO_SERIALIZE, PAGE_SIZE * 10, PAGE_SIZE * 100);
	int* pArr = (int*)HeapAlloc(hHeap, 0, sizeof(int) * 30);
	for (int i = 0; i < 30; ++i)
	{
		pArr[i] = i * 10 + 0x11;
	}
		for (int i = 0; i < 30; ++i)
	{
		if (i % 5 == 0)
			printf_s("\n");
		printf("%5d ", pArr[i]);
	}
	printf("\nHeapCreate成功!\n");
}

void Heap_Free() {
	HANDLE hHeap = HeapCreate(HEAP_NO_SERIALIZE, PAGE_SIZE * 10, PAGE_SIZE * 100);
	int* pArr = (int*)HeapAlloc(hHeap, 0, sizeof(int) * 30);
	printf_s("\n\n");
	printf("按任意键开始HeapFree!\n");
	getchar();
	getchar();
	HeapFree(hHeap, 0, pArr);
	printf("HeapFree成功!\n");
}

void Heap_Destroy() {
	HANDLE hHeap = HeapCreate(HEAP_NO_SERIALIZE, PAGE_SIZE * 10, PAGE_SIZE * 100);
	printf("按任意键开始HeapDestory!\n");
	getchar();
	getchar();
	HeapDestroy(hHeap);
	printf("HeapDestory成功!\n");
}