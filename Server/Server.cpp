#include <vector>
#include <mutex>
#include <windows.h>
#include <atomic>
#include <iostream>
#include "pch.h"
using namespace std;

// server
// 1. ���ο� ���� ���� (Socket)
// 2. ���Ͽ� �ּ�/��Ʈ ����(bind)
// 3. ���� ���� (listen)
// 4. ���� (accept)
// 5. Ŭ���̾�Ʈ�� ���

int main()
{
	WSADATA wsaData;
	if (::WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
		return 0;

	// 1 ���� ����
	// af : address family (af_inet : ipv4, af_inet6 : ipv6)
	// type : TCP = SOCK_STREAM, UDP = SOCK_DGRAM
	// protocol : 0
	// return : descriptor
	// error : int32 �������� WSAGetLastError() �Լ��� ����
	SOCKET listenSocket = ::socket(AF_INET, SOCK_STREAM, 0);
	if (listenSocket == 0) return 0;

	//2 Bind
	// ���� ������ : IP, PORT ����
	SOCKADDR_IN serverAddr;
	::memset(&serverAddr, 0, sizeof(serverAddr));

	// ����ü�� ������ ä���ִ� ��
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_addr.s_addr = ::htonl(INADDR_ANY); // IP
	serverAddr.sin_port = htons(7777); // PORT

	::bind(listenSocket, (SOCKADDR*)&serverAddr, sizeof(serverAddr));

	//3 listen
	if (::listen(listenSocket, SOMAXCONN) == SOCKET_ERROR) return 0;

	//4 accept
	while (true)
	{
		SOCKADDR_IN clientAddr;
		::memset(&clientAddr, 0, sizeof(clientAddr));
		__int32 addrLen = sizeof(clientAddr);

		// ��� -> Ŭ���̾�Ʈ���� �����ϱ� �������� ����Ѵ�
		SOCKET clientSocket = ::accept(listenSocket, (SOCKADDR*)&clientAddr, &addrLen);
		if (clientSocket == INVALID_SOCKET) return 0;


		char ip[16];
		::inet_ntop(AF_INET, &clientAddr.sin_addr, ip, sizeof(ip));
		cout << "Client Connected, IP :" << ip << endl;

		// ��Ŷ �ְ�ޱ�
		while (true)
		{
			char recvBuffer[100];
			__int32 recvLen = ::recv(clientSocket, recvBuffer, sizeof(recvBuffer), 0);
			if (recvBuffer <= 0)
				return 0;

			cout << "Recv buffer :" << recvBuffer << endl;

		}
	}

	::WSACleanup();
}