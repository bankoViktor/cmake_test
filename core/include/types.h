#ifndef _TYPES_H
#define _TYPES_H

#include "HttpRequest.h"
#include "HttpResponse.h"
#include <vector>


typedef void (*REQUEST_HANDLER)(const HttpRequest& req, HttpResponse& resp);


typedef struct _REQUEST_HANDLER_INFO
{
	const char* pszMethod;
	const char* pszResource;
	REQUEST_HANDLER handler;
	const void* reserved;
} REQUEST_HANDLER_INFO;

using HttpHandlerCollection = std::vector<REQUEST_HANDLER_INFO>;


#endif // !_TYPES_H
