#ifndef _HTTP_METHODS_H
#define _HTTP_METHODS_H


enum class HttpMethods
{
	Get,
	Head,
	Post,
	Put,
	Delete,
	Connect,
	Options,
	Trace,
	Patch,
};


class HttpHelper
{
public:
	static const char* Translate(HttpMethods method);
};


#endif // !_HTTP_METHODS_H
