// 参考文献：基于Windows平台的实现
// https://www.cnblogs.com/DOMLX/p/9601511.html


#include <stdio.h>  
#include <iostream>
#include <string>
#include <winsock2.h>  

#pragma comment(lib, "ws2_32.lib")
#pragma warning(disable: 4996)

#define _WINSOCK_DEPRECATED_NO_WARNINGS

using namespace std;

int main()
{
    // 初始化WSA  
    WORD sockVersion = MAKEWORD(2, 2);
    WSADATA wsaData;
    if (WSAStartup(sockVersion, &wsaData) != 0)
    {
        printf("加载WinSock失败!\n\n");
        return 0;
    }

    // 创建用于监听的套接字
    SOCKET slisten = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (slisten == INVALID_SOCKET)
    {
        printf("套接字Socket错误!\n\n");
        return 0;
    }

    // 绑定IP和端口  
    sockaddr_in addrSrv;
    addrSrv.sin_family = AF_INET;
    addrSrv.sin_port = htons(8888); // 1024以上的端口号
    addrSrv.sin_addr.S_un.S_addr = INADDR_ANY;
    if (bind(slisten, (LPSOCKADDR)&addrSrv, sizeof(addrSrv)) == SOCKET_ERROR)
    {
        printf("bind错误!\n");
        printf("Failed bind: %d\n\n", WSAGetLastError());
    }

    //开始监听  
    if (listen(slisten, 5) == SOCKET_ERROR)
    {
        printf("listen错误!\n");
        printf("Listen failed: %d\n\n", WSAGetLastError());
        return 0;
    }

    //循环接收数据  
    SOCKET sockConn;
    sockaddr_in clientAddr;
    int nAddrlen = sizeof(clientAddr);
    char revData[255] = {};
    STARTUPINFOA startupInfo;
    PROCESS_INFORMATION  processInfo;
    ZeroMemory(&startupInfo, sizeof(startupInfo));
    ZeroMemory(&processInfo, sizeof(processInfo));
    
    char str[] = "E:\\TestInitialNullForStudent\\InjectDll\\Debug\\Client.exe"; // 客户端路径
    CreateProcessA(str, NULL, NULL, NULL, TRUE, CREATE_NEW_CONSOLE, NULL, NULL, &startupInfo, &processInfo);
    while (true)
    {
        printf("\n等待连接中……\n");
        sockConn = accept(slisten, (SOCKADDR*)&clientAddr, &nAddrlen);
        if (sockConn == INVALID_SOCKET)
        {
            printf("收到错误!\n\n");
            continue;
        }
        printf("连接成功：%s \r\n\n", inet_ntoa(clientAddr.sin_addr));

        //接收数据  
        int ret = recv(sockConn, revData, 255, 0);
        if (ret > 0)
        {
            revData[ret] = 0x00;
            printf("收到来自服务端的数据：%s\n", revData);
            printf("\n");
        }

        //发送数据
        // string title = "客户端你好！我是服务端！";
        string data;
        printf("\n请输入想要传输的数据（字符串形式）: \n");
        cin >> data;
        // title += data;
        const char* sendData;
        sendData = data.c_str();   //string转const char* 
        send(sockConn, sendData, strlen(sendData), 0);

        closesocket(sockConn);
    }

    // 关闭socket
    closesocket(slisten);
    WSACleanup();
    return 0;
}