#include "pch.h"
#include <thread>
#include <vector>
#include <mutex>
#include <windows.h>
#include <atomic>
#include <iostream>

using namespace std;

// server
// 1. 새로운 소켓 생성 (Socket)
// 2. 소켓에 주소/포트 설정(bind)
//  ----------------------------- UDP
// 3. 소켓 오픈 (listen) -------- TCP
// 4. 접속 (accept) ------------- TCP
// 5. 클라이언트와 통신

int main()
{
	WSADATA wsaData;
	if (::WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
		return 0;

	// 1 소켓 생성
	// af : address family (af_inet : ipv4, af_inet6 : ipv6)
	// type : TCP = SOCK_STREAM, UDP = SOCK_DGRAM
	// protocol : 0
	// return : descriptor
	// error : int32 형식으로 WSAGetLastError() 함수로 리턴
	SOCKET listenSocket = ::socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (listenSocket == INVALID_SOCKET) return 0;

	//2 Bind
	// 연결 목적지 : IP, PORT 설정
	SOCKADDR_IN serverAddr;
	::memset(&serverAddr, 0, sizeof(serverAddr));

	// 구조체에 정보를 채워주는 것
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_addr.s_addr = ::htonl(INADDR_ANY); // IP
	serverAddr.sin_port = htons(7777); // PORT

	::bind(listenSocket, (SOCKADDR*)&serverAddr, sizeof(serverAddr));

	////3 listen
	//if (::listen(listenSocket, SOMAXCONN) == SOCKET_ERROR) return 0;

	//4 accept
	while (true)
	{
		SOCKADDR_IN clientAddr;
		::memset(&clientAddr, 0, sizeof(clientAddr));
		int32 addrLen = sizeof(clientAddr);

		// 패킷 주고받기
		while (true)
		{
			char recvBuffer[100];
			int32 recvLen = ::recvfrom(listenSocket, recvBuffer, sizeof(recvBuffer), 0, (SOCKADDR*)&clientAddr, &addrLen);
			if (recvLen <= 0)
				return 0;

			cout << "Recv buffer :" << recvBuffer << endl;
			this_thread::sleep_for(1s);
		}
	}

	::WSACleanup();
}