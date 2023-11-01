#include "pch.h"
#include <iostream>

int main()
{
	SocketUtils::Init();

	SOCKET clientSocket = ::socket(AF_INET, SOCK_STREAM, 0);
	if (clientSocket == INVALID_SOCKET)
		return 0;
	u_long on = 1;
	if (::ioctlsocket(clientSocket, FIONBIO, &on) == INVALID_SOCKET)
		return 0;

	SOCKADDR_IN serverAddr;
	::memset(&serverAddr, 0, sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	::inet_pton(AF_INET, "127.0.0.1", &serverAddr.sin_addr);
	serverAddr.sin_port = ::htons(7777); // 80 : HTTP


	// connect
	while (true)
	{
		if (::connect(clientSocket, (SOCKADDR*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR)
		{
			if (::WSAGetLastError() == WSAEWOULDBLOCK) continue;
			if (::WSAGetLastError() == WSAEISCONN) break;
		}
	}

	//send
	while (true)
	{
		char sendBuffer[100] = "Hello I am Client!";
		int32 sendLen = sizeof(sendBuffer);

		if (::send(clientSocket, sendBuffer, sendLen, 0) == SOCKET_ERROR)
		{
			// 원래 블록했어야 했는데 ... 너가 논블로킹 하라며?
			if (::WSAGetLastError() == WSAEWOULDBLOCK)
				continue;
			
		}
		cout << "Send Data ! Len = " << sendLen << endl;
		this_thread::sleep_for(1s);
	}

	SocketUtils::Close(clientSocket);

}