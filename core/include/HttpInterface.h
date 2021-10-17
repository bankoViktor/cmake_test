#ifndef _HTTP_INTRFACE_H
#define _HTTP_INTRFACE_H

#include <WinSock2.h>
#include "HttpRequest.h"
#include "HttpResponse.h"
#include "export.h"
#include "Utils.h"
#include <vector>

#define DEFAULT_PORT	80


typedef void (*REQUEST_HANDLER)(const HttpRequest& req, HttpResponse& resp);


typedef struct _REQUEST_HANDLER_INFO
{
	const char* pszMethod;
	const char* pszResource;
	REQUEST_HANDLER handler;
} REQUEST_HANDLER_INFO;


class DLLEXPORTED HttpInterface
{
private:
	unsigned short m_dwPort;
	SOCKET m_socket;
	std::vector<REQUEST_HANDLER_INFO>* m_pRequestHandlers;

private:
	void AcceptingHandler();
	void RequestHandler(SOCKET clientSocket);

public:
	HttpInterface();
	~HttpInterface();
	void Start(unsigned short dwPort);
	HttpInterface& on(const char* pszMethod, const char* pszResource, REQUEST_HANDLER handler);
	HttpInterface& get(const char* pszResource, REQUEST_HANDLER handler);
	HttpInterface& post(const char* pszResource, REQUEST_HANDLER handler);
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
