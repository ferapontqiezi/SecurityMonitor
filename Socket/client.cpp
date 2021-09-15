// 参考文献：基于Windows平台的实现
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
	// 初始化WSA  
	WORD sockVersion = MAKEWORD(2, 2);
	WSADATA data;
	if (WSAStartup(sockVersion, &data) != 0)
	{
		printf("加载WinSock失败!\n\n");
		return 0;
	}

	//循环接收数据  
	while (true) {
		SOCKET sockConn = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		if (sockConn == INVALID_SOCKET)
		{
			printf("不合法的socket!\n\n");
			return 0;
		}

		sockaddr_in serAddr;
		serAddr.sin_family = AF_INET;
		serAddr.sin_port = htons(8888); // 1024以上的端口号
		serAddr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");	// 本机ip
		if (connect(sockConn, (sockaddr*)&serAddr, sizeof(serAddr)) == SOCKET_ERROR)
		{  // 连接失败 
			printf("连接失败!\n\n");
			closesocket(sockConn);
			return 0;
		}

		string data;
		printf("\n请输入想要传输的数据（字符串形式）: \n");
		cin >> data;
		const char* sendData;
		sendData = data.c_str();   //string转const char* 
		//char * sendData = "你好，TCP服务端，我是客户端\n";
		send(sockConn, sendData, strlen(sendData), 0);
		//send()用来将数据由指定的socket传给对方主机
		//int send(int s, const void * msg, int len, unsigned int flags)
		//s为已建立好连接的socket，msg指向数据内容，len则为数据长度，参数flags一般设0
		//成功则返回实际传送出去的字符数，失败返回-1，错误原因存于error 

		char recData[255];
		int ret = recv(sockConn, recData, 255, 0);
		if (ret > 0) {
			recData[ret] = 0x00;
			printf("收到来自服务端的数据：%s\n", recData);
		}
		closesocket(sockConn);
	}


	WSACleanup();
	return 0;
}
