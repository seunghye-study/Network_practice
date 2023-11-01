#include "pch.h"
#include <iostream>
#include <WinSock2.h>



//Ŭ���̾�Ʈ
// 1 ���� ����
// 2 ������ ��û
// 3 ���

// ����� ���
// ��Ʋ ����� (�츮�� ����ϴ� ���)
// -- �ּҸ� ū������ �Ųٷ� ������� (������ -> ����)
// �� ����� (��Ʈ��ũ ǥ��)
// -- �ּҸ� ���ʴ�� ������� (���� -> ������)


int main()
{
	WSADATA wsaData;
	if (::WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
		return 0;

	SOCKET clientSocket = ::socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (clientSocket == 0) return 0;


	// ������ ������ �ּ�
	SOCKADDR_IN serverAddr;
	::memset(&serverAddr, 0, sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	//serverAddr.sin_addr.s_addr = ::htonl(INADDR_ANY); // IP
	::inet_pton(AF_INET, "127.0.0.1", &serverAddr.sin_addr);
	serverAddr.sin_port = htons(7777); // PORT, htons -> ����� �����ִ� �Լ�

	// ������ ���ε�, Ŭ���̾�Ʈ�� Ŀ��Ʈ
	/*if (::connect(clientSocket, (SOCKADDR*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR)
		return 0;

	std::cout << "Connect to server!" << std::endl;*/

	while (true)
	{
		// send buffer
		char sendBuffer[100] = "hello";
		int32 resultCode = ::sendto(clientSocket, sendBuffer, sizeof(sendBuffer), 0, (SOCKADDR*)&serverAddr, sizeof(serverAddr));
		if (resultCode == SOCKET_ERROR)
			return 0;

		cout << "send data" << endl;
		this_thread::sleep_for(1s);
	}

	::closesocket(clientSocket);
	::WSACleanup();

}