#ifndef _WINSOCK_H
#define _WINSOCK_H

#include <WinSock2.h>
#include "export.h"
#include <sstream>

#define RX_BUFFER_SIZE		512 * 1 // 512KB

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

	// HTTP ���������		ISO-8859-1
	// HTTP ��������� ����	Content-Type ��� ISO-8859-1

	static bool Receive(SOCKET socket, std::string& received);
	//static void Transmit(const char* data, size_t size);
};

#endif // _WINSOCK_H
