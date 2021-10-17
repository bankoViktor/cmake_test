#ifndef _HTTP_HEADER_COLLECTION_H
#define _HTTP_HEADER_COLLECTION_H

#include "export.h"
#include <string>
#include <vector>
#include <algorithm>


class DLLEXPORTED HttpHeader
{
public:
	std::string *name;
	std::string *value;

public:
	HttpHeader(const std::string &name, const std::string &value);
	~HttpHeader();
	long long asLongLong() const;
};


class DLLEXPORTED HttpHeaderCollection
{
private:
	std::vector<const HttpHeader*> *m_pCollection;

public:
	HttpHeaderCollection();
	HttpHeaderCollection(const HttpHeaderCollection& copy);
	~HttpHeaderCollection();
	void Add(const std::string& name, const std::string& value);
	const HttpHeader* operator[](const char* name);
};


#endif // !_HTTP_HEADER_COLLECTION_H
