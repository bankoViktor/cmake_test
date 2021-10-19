#include "../include/HttpResponse.h"
#include "../include/Utils.h"


HttpResponse::HttpResponse(const HttpRequest& request) :
	request(request)
{
	m_pszBody = nullptr;
}

HttpResponse::~HttpResponse()
{
	SafeReleasePonter(m_pszBody);
}

void HttpResponse::Write(const char* content)
{
	SafeReleasePonter(m_pszBody);

	auto len = strlen(content) + 1;
	m_pszBody = new char[len];
	strcpy_s((char*)m_pszBody, len, content);
}
