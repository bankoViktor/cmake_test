#ifndef _HTTP_HEADER_COLLECTION_H
#define _HTTP_HEADER_COLLECTION_H

#include "export.h"
#include <vector>
#include "HttpHeader.h"


class DLLEXPORTED HttpHeaderCollection
{
private:
	std::vector<HttpHeader*> *m_pHeaders;

private:
	HttpHeader* TryGet(const char* name) const;

public:
	HttpHeaderCollection();
	HttpHeaderCollection(const HttpHeaderCollection& copy);
	~HttpHeaderCollection();
	void AddHeader(const HttpHeader& header);
	void AddHeader(const char* name, const char* value);
	HttpHeader& operator[](const char* name);
	bool IsContains(const char* name);
};


#endif // !_HTTP_HEADER_COLLECTION_H
