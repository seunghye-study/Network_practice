#include "pch.h"
#include <iostream>
#include <WinSock2.h>



//클라이언트
// 1 소켓 생성
// 2 서버에 요청
// 3 통신

// 엔디언 방식
// 리틀 엔디언 (우리가 사용하는 방식)
// -- 주소를 큰수부터 거꾸로 적어나가기 (오른쪽 -> 왼쪽)
// 빅 엔디언 (네트워크 표준)
// -- 주소를 차례대로 적어나가기 (왼쪽 -> 오른쪽)


int main()
{
	WSADATA wsaData;
	if (::WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
		return 0;

	SOCKET clientSocket = ::socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (clientSocket == 0) return 0;


	// 연결할 서버의 주소
	SOCKADDR_IN serverAddr;
	::memset(&serverAddr, 0, sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	//serverAddr.sin_addr.s_addr = ::htonl(INADDR_ANY); // IP
	::inet_pton(AF_INET, "127.0.0.1", &serverAddr.sin_addr);
	serverAddr.sin_port = htons(7777); // PORT, htons -> 엔디언 맞춰주는 함수

	// 서버는 바인딩, 클라이언트는 커넥트
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