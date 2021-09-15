#include "head.h"

void showMenuM();

int main() {
	int op = 0;
	while (true) {
		showMenuM();
		scanf("%d", &op);
		switch (op)
		{
		case 0: {
			printf("�´μ�!\n");
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
		}

		if (op == 0) {
			break;
		}
	}
	return 0;
}

void showMenuM() {
	printf("\n\n");
	printf("----The Menu for Testing MessageBox Functions---\n");
	printf("1.MessageBoxA                   2.MessageBoxW  \n");
}