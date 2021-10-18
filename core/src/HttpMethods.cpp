#include "..\include\HttpMethods.h"

const char* HttpHelper::Translate(HttpMethods method)
{
	switch (method)
	{
	case HttpMethods::Get:		return "GET";
	case HttpMethods::Head:		return "HEAD";
	case HttpMethods::Post:		return "POST";
	case HttpMethods::Put:		return "PUT";
	case HttpMethods::Delete:	return "DELETE";
	case HttpMethods::Connect:	return "CONNECT";
	case HttpMethods::Options:	return "OPTIONS";
	case HttpMethods::Trace:	return "TRACE";
	case HttpMethods::Patch:	return "PATCH";
	default:					return nullptr;
	}
}
