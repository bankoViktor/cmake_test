#ifndef _WINSOCK_H
#define _WINSOCK_H

#include <WinSock2.h>
#include "export.h"
#include <sstream>


#define RX_BUFFER_SIZE			512 // 512KB


class DLLEXPORTED WinSock
{
private: 
	static WSADATA* m_pWsaData;

public:
	static bool Initialization();
	static bool Uninitialization();
	static bool GetInitializationStatus();
	static bool CreateSocket(SOCKET* pSocket, int port);
	static bool CloseSocket(SOCKET socket);
	static SOCKET Accept(SOCKET socket, SOCKET* pClientSocket);

	// HTTP кодировка		ISO-8859-1
	// HTTP кодировка тела	Content-Type или ISO-8859-1

	static bool Receive(SOCKET socket, std::string& received);
	static bool Transmit(SOCKET socket, const std::string& content);
};


#endif // _WINSOCK_H
