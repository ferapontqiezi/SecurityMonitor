#include <stdio.h>  
#include <iostream>
#include <string>
#include <winsock2.h>  

#pragma comment(lib, "ws2_32.lib")
#pragma warning(disable: 4996)

#define _WINSOCK_DEPRECATED_NO_WARNINGS

using namespace std;


void WebSendAndRec(char* url) {
	
	WSADATA wsaData;
	SOCKET Socket;
	SOCKADDR_IN SockAddr;
	int lineCount = 0;
	int rowCount = 0;
	struct hostent* host;
	//::locale local;
	char buffer[10000] = { 0 };
	int i = 0;
	int nDataLength;
	// string website_HTML;

	char* get_http = (char*)malloc(256);
	*get_http = NULL;
	strcat(get_http, "GET / HTTP/1.1\r\nHost: ");
	strcat(get_http, url);
	strcat(get_http, "\r\nConnection: close\r\n\r\n");

	// string website_HTML;

	if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
		printf("WSAStartup failed.\n");
		return;
	}
	printf("url: %s\n", url);

	Socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	// 如果URL解析失败，会直接报异常，程序崩溃
	host = gethostbyname(url);

	printf("h_name: %s\n", host->h_name);
	printf("host->h_addrtype: %d\n", host->h_addrtype);
	printf("h_length: %d\n", host->h_length);

	SockAddr.sin_port = htons(80);
	SockAddr.sin_family = AF_INET;
	SockAddr.sin_addr.s_addr = *((unsigned long*)host->h_addr);

	if (::connect(Socket, (SOCKADDR*)(&SockAddr), sizeof(SockAddr)) != 0) {
		printf("连接失败\n");
		return;
	}

	// send GET / HTTP
	send(Socket, get_http, strlen(get_http), 0);


	// recieve html
	while ((nDataLength = recv(Socket, buffer, 10000, 0)) > 0) {
		int i = 0;
	}

	closesocket(Socket);
	WSACleanup();
	return;
}

int main(int argc, char* argv[]) {
	char str[200];
	cout << "请输入域名：";
	cin >> str;
	char* url = str;
	WebSendAndRec(url);
	return 0;
}