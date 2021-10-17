#ifndef _HTTP_RESPONSE_H
#define _HTTP_RESPONSE_H

#include "HttpRequest.h"
#include "export.h"

class DLLEXPORTED HttpResponse
{
private:
	const HttpRequest* m_pRequest;

public:
	HttpResponse(const HttpRequest &request);
	~HttpResponse();
};

#endif // !_HTTP_RESPONSE_H
