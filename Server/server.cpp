// �ο����ף�����Windowsƽ̨��ʵ��
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
    // ��ʼ��WSA  
    WORD sockVersion = MAKEWORD(2, 2);
    WSADATA wsaData;
    if (WSAStartup(sockVersion, &wsaData) != 0)
    {
        printf("����WinSockʧ��!\n\n");
        return 0;
    }

    // �������ڼ������׽���
    SOCKET slisten = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (slisten == INVALID_SOCKET)
    {
        printf("�׽���Socket����!\n\n");
        return 0;
    }

    // ��IP�Ͷ˿�  
    sockaddr_in addrSrv;
    addrSrv.sin_family = AF_INET;
    addrSrv.sin_port = htons(8888); // 1024���ϵĶ˿ں�
    addrSrv.sin_addr.S_un.S_addr = INADDR_ANY;
    if (bind(slisten, (LPSOCKADDR)&addrSrv, sizeof(addrSrv)) == SOCKET_ERROR)
    {
        printf("bind����!\n");
        printf("Failed bind: %d\n\n", WSAGetLastError());
    }

    //��ʼ����  
    if (listen(slisten, 5) == SOCKET_ERROR)
    {
        printf("listen����!\n");
        printf("Listen failed: %d\n\n", WSAGetLastError());
        return 0;
    }

    //ѭ����������  
    SOCKET sockConn;
    sockaddr_in clientAddr;
    int nAddrlen = sizeof(clientAddr);
    char revData[255] = {};
    STARTUPINFOA startupInfo;
    PROCESS_INFORMATION  processInfo;
    ZeroMemory(&startupInfo, sizeof(startupInfo));
    ZeroMemory(&processInfo, sizeof(processInfo));
    
    char str[] = "E:\\TestInitialNullForStudent\\InjectDll\\Debug\\Client.exe"; // �ͻ���·��
    CreateProcessA(str, NULL, NULL, NULL, TRUE, CREATE_NEW_CONSOLE, NULL, NULL, &startupInfo, &processInfo);
    while (true)
    {
        printf("\n�ȴ������С���\n");
        sockConn = accept(slisten, (SOCKADDR*)&clientAddr, &nAddrlen);
        if (sockConn == INVALID_SOCKET)
        {
            printf("�յ�����!\n\n");
            continue;
        }
        printf("���ӳɹ���%s \r\n\n", inet_ntoa(clientAddr.sin_addr));

        //��������  
        int ret = recv(sockConn, revData, 255, 0);
        if (ret > 0)
        {
            revData[ret] = 0x00;
            printf("�յ����Է���˵����ݣ�%s\n", revData);
            printf("\n");
        }

        //��������
        // string title = "�ͻ�����ã����Ƿ���ˣ�";
        string data;
        printf("\n��������Ҫ��������ݣ��ַ�����ʽ��: \n");
        cin >> data;
        // title += data;
        const char* sendData;
        sendData = data.c_str();   //stringתconst char* 
        send(sockConn, sendData, strlen(sendData), 0);

        closesocket(sockConn);
    }

    // �ر�socket
    closesocket(slisten);
    WSACleanup();
    return 0;
}