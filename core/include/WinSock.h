#ifndef _WINSOCK_H
#define _WINSOCK_H

#include <WinSock2.h>
#include "export.h"

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

	//static void Receive();
	//static void Transmit(const char* data, size_t size);
};

#endif // _WINSOCK_H
