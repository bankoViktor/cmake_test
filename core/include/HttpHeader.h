#ifndef _HTTP_HEADER_H
#define _HTTP_HEADER_H

#include "export.h"
#include <string>

class DLLEXPORTED HttpHeader
{
public:
	const char* m_pszName;
	const char* m_pszValue;

public:
	HttpHeader(const char* name, const char* value);
	HttpHeader(const std::string& name, const std::string& value);
	HttpHeader(const HttpHeader& copy);
	~HttpHeader();
	long long asLongLong() const;
};


#endif // !_HTTP_HEADER_H
