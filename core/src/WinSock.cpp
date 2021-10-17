#include "../include/WinSock.h"
#include <ws2tcpip.h>
#include <iostream>
#include <string> 

#pragma comment(lib, "Ws2_32.lib")

WSADATA* WinSock::m_pWsaData = nullptr;

bool WinSock::Initialization()
{
	if (!m_pWsaData)
	{
		m_pWsaData = new WSADATA;
		ZeroMemory(m_pWsaData, sizeof(WSADATA));

		int iResult = WSAStartup(MAKEWORD(2, 2), m_pWsaData);
		if (iResult != 0) {
			std::cout << "WSAStartup failed: " << WSAGetLastError() << std::endl;
			return false;
		}

		std::cout << m_pWsaData->szDescription << ". Status: " << m_pWsaData->szSystemStatus << std::endl;
	}

	return true;
}

bool WinSock::Uninitialization()
{
	if (m_pWsaData)
	{
		int iResult = WSACleanup();
		if (iResult != 0) {
			std::cout << "WSACleanup failed: " << WSAGetLastError() << std::endl;
			return false;
		}

		std::cout << m_pWsaData->szDescription << ". Stopped" << std::endl;

		delete m_pWsaData;
		m_pWsaData = nullptr;
	}

	return true;
}

bool WinSock::GetInitializationStatus()
{
	return m_pWsaData != nullptr;
}

bool WinSock::CreateSocket(SOCKET* pSocket, int port)
{
	if (m_pWsaData == nullptr)
		return false;

	*pSocket = INVALID_SOCKET;

	addrinfo hints;
	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	hints.ai_flags = AI_PASSIVE;

	addrinfo *pServerInfo = nullptr;

	std::string strPort = std::to_string(port);

	int iResult = getaddrinfo(NULL, strPort.c_str(), &hints, &pServerInfo);
	if (iResult != 0)
		return false;

	SOCKET socket = ::socket(pServerInfo->ai_family, pServerInfo->ai_socktype, pServerInfo->ai_protocol);

	if (socket == INVALID_SOCKET)
		return false;

	iResult = bind(socket, pServerInfo->ai_addr, (int)pServerInfo->ai_addrlen);

	freeaddrinfo(pServerInfo);

	if (iResult == SOCKET_ERROR) {
		closesocket(socket);
		return false;
	}

	if (listen(socket, SOMAXCONN) == SOCKET_ERROR) {
		closesocket(socket);
		return false;
	}

	*pSocket = socket;

	return true;
}

bool WinSock::CloseSocket(SOCKET socket)
{
	int iResult = closesocket(socket);
	return iResult == 0;
}

SOCKET WinSock::Accept(SOCKET socket, SOCKET *pClientSocket)
{
	if (m_pWsaData == nullptr)
		return false;

	*pClientSocket = INVALID_SOCKET;

	SOCKET clientSocket = accept(socket, NULL, NULL);
	if (clientSocket == INVALID_SOCKET)
		return false;

	*pClientSocket = clientSocket;

	return true;
}
