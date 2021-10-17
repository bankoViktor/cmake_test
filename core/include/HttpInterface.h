#ifndef _HTTP_INTRFACE_H
#define _HTTP_INTRFACE_H

#include <WinSock2.h>
#include "HttpRequest.h"
#include "HttpResponse.h"
#include "export.h"
#include <vector>
#include <sstream>


typedef void (*REQUEST_HANDLER)(const HttpRequest& request, HttpResponse& response);


typedef struct _REQUEST_HANDLER_INFO
{
	const char* pszMethod;
	const char* pszResource;
	REQUEST_HANDLER handler;
} REQUEST_HANDLER_INFO;


class DLLEXPORTED HttpInterface
{
private:
	int m_status;
	int m_port;
	SOCKET m_socket;
	void AcceptingHandler();
	void RequestHandler(SOCKET clientSocket);
	std::vector<REQUEST_HANDLER_INFO> m_requestHandlers;

public:
	HttpInterface();
	~HttpInterface();
	void Start(int port);

	HttpInterface& on(const char* pszMethod, const char* pszResource, REQUEST_HANDLER handler);
	HttpInterface& get(const char* pszResource, REQUEST_HANDLER handler);
	HttpInterface& post(const char* pszResource, REQUEST_HANDLER handler);

private:
	bool Receive(SOCKET socket, std::string& data);
	bool ParseRequest(
		const std::string& content,
		size_t end,
		std::string& method,
		std::string& uri,
		std::string& protocolName,
		std::string& protocolVersion,
		HttpHeaderCollection& headers);
};


namespace HttpMethods
{
#ifdef __cplusplus
	extern "C"
	{
#endif
		DLLEXPORTED const char* const Get = "GET";
		DLLEXPORTED const char* const Head = "HEAD";
		DLLEXPORTED const char* const Post = "POST";
		DLLEXPORTED const char* const Put = "PUT";
		DLLEXPORTED const char* const Delete = "DELETE";
		DLLEXPORTED const char* const Connect = "CONNECT";
		DLLEXPORTED const char* const Options = "OPTIONS";
		DLLEXPORTED const char* const Trace = "TRACE";
		DLLEXPORTED const char* const Patch = "PATCH";
#ifdef __cplusplus
	}
#endif
}


#endif // !_HTTP_INTRFACE_H
