// �ο����ף�����Windowsƽ̨��ʵ��
// https://www.cnblogs.com/DOMLX/p/9601511.html


#include <stdio.h>
#include <string>
#include <iostream>
#include <winsock2.h>

#pragma comment(lib, "ws2_32.lib")

#define _WINSOCK_DEPRECATED_NO_WARNINGS

using namespace std;

int main()
{
	// ��ʼ��WSA  
	WORD sockVersion = MAKEWORD(2, 2);
	WSADATA data;
	if (WSAStartup(sockVersion, &data) != 0)
	{
		printf("����WinSockʧ��!\n\n");
		return 0;
	}

	//ѭ����������  
	while (true) {
		SOCKET sockConn = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		if (sockConn == INVALID_SOCKET)
		{
			printf("���Ϸ���socket!\n\n");
			return 0;
		}

		sockaddr_in serAddr;
		serAddr.sin_family = AF_INET;
		serAddr.sin_port = htons(8888); // 1024���ϵĶ˿ں�
		serAddr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");	// ����ip
		if (connect(sockConn, (sockaddr*)&serAddr, sizeof(serAddr)) == SOCKET_ERROR)
		{  // ����ʧ�� 
			printf("����ʧ��!\n\n");
			closesocket(sockConn);
			return 0;
		}

		string data;
		printf("\n��������Ҫ��������ݣ��ַ�����ʽ��: \n");
		cin >> data;
		const char* sendData;
		sendData = data.c_str();   //stringתconst char* 
		//char * sendData = "��ã�TCP����ˣ����ǿͻ���\n";
		send(sockConn, sendData, strlen(sendData), 0);
		//send()������������ָ����socket�����Է�����
		//int send(int s, const void * msg, int len, unsigned int flags)
		//sΪ�ѽ��������ӵ�socket��msgָ���������ݣ�len��Ϊ���ݳ��ȣ�����flagsһ����0
		//�ɹ��򷵻�ʵ�ʴ��ͳ�ȥ���ַ�����ʧ�ܷ���-1������ԭ�����error 

		char recData[255];
		int ret = recv(sockConn, recData, 255, 0);
		if (ret > 0) {
			recData[ret] = 0x00;
			printf("�յ����Է���˵����ݣ�%s\n", recData);
		}
		closesocket(sockConn);
	}


	WSACleanup();
	return 0;
}
