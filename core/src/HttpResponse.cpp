#include "../include/HttpResponse.h"
#include "../include/Utils.h"

HttpResponse::HttpResponse(const HttpRequest& request)
{
	m_pRequest = &request;
}

HttpResponse::~HttpResponse()
{

}