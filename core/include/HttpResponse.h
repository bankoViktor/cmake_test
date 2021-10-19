#ifndef _HTTP_RESPONSE_H
#define _HTTP_RESPONSE_H

#include "HttpRequest.h"
#include "export.h"
#include <string>


class DLLEXPORTED HttpResponse
{
private:
	const HttpRequest& request;
	const char* m_pszBody;

public:
	HttpResponse(const HttpRequest &request);
	~HttpResponse();
	void Write(const char * content);
};


#endif // !_HTTP_RESPONSE_H
