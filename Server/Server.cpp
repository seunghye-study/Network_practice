#include "pch.h"
#include <thread>
#include <vector>
#include <mutex>

using namespace std;
#include <windows.h>
#include <atomic>
#include <iostream>
#include "TestMain.h"
#include "ThreadManager.h"

int main()
{
	SocketUtils::Init();

	SOCKET listenSocket = ::socket(AF_INET, SOCK_STREAM, 0);
	if (listenSocket == INVALID_SOCKET)
		return 0;

	u_long on = 1;
	if (::ioctlsocket(listenSocket, FIONBIO, &on) == INVALID_SOCKET)
		return 0;

	SocketUtils::SetReuseAddress(listenSocket, true);

	if (SocketUtils::BindAnyAddress(listenSocket, 7777) == false) 
		return 0;

	if (SocketUtils::Listen(listenSocket, SOMAXCONN) == false)
		return 0;

	SOCKADDR_IN clientAddr;
	int32 addrLen = sizeof(clientAddr);


	//accept 
	while (true)
	{
		SOCKET clientSocket = ::accept(listenSocket, (SOCKADDR*)&clientAddr, &addrLen);
		if (clientSocket == INVALID_SOCKET)
		{
			//�ϰ� ����ŷ���� �϶��.. Ŭ�� �ȵ����� ����ؾ��ϴµ�..
			if (::WSAGetLastError() == WSAEACCES)
			{
				cout << "WSAGetLastError" << endl;
				continue;
			}
		}
		cout << "client connected!" << endl;

		//Recv
		while (true)
		{
			char recvBuffer[1000];
			int32 recvLen = ::recv(clientSocket, recvBuffer, sizeof(recvBuffer), 0);
			if (recvLen == SOCKET_ERROR)
			{
				if (::WSAGetLastError() == WSAEWOULDBLOCK)
					continue;

				//TODO
				break;
			}
			cout << "recv data = " << recvBuffer << endl;
			cout << "recv data len = " << recvLen << endl;
		}
	}
	SocketUtils::Close(listenSocket);
}