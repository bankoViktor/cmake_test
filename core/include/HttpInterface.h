#ifndef _HTTP_INTRFACE_H
#define _HTTP_INTRFACE_H

#include <WinSock2.h>
#include "HttpInterfaceConfigurator.h"
#include "types.h"
#include "export.h"


#define DEFAULT_PORT	80


class DLLEXPORTED HttpInterface
{
private:
	unsigned short m_dwPort;
	SOCKET m_socket;
	HttpHandlerCollection* m_pRequestHandlers;

private:
	void AcceptingHandler();
	void RequestHandler(SOCKET clientSocket);
	bool Receive(
		SOCKET socket,
		HttpHeaderCollection& headers,
		std::string& method,
		std::string& uri,
		std::string& protocolName,
		std::string& protocolVersion,
		std::string& body);
	bool Transmit(
		SOCKET socket,
		const HttpResponse& response);

public:
	HttpInterface(const HttpInterfaceConfigurator& configurator);
	~HttpInterface();
	void Start(unsigned short dwPort);
};


#endif // !_HTTP_INTRFACE_H
