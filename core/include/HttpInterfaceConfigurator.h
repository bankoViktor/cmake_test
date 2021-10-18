#ifndef _HTTP_INTERGACE_CONFIGURATOR_H
#define _HTTP_INTERGACE_CONFIGURATOR_H

#include "export.h"
#include "types.h"
#include "HttpMethods.h"

class DLLEXPORTED HttpInterfaceConfigurator
{
private:
	HttpHandlerCollection* m_pRequestHandlers;

public:
	HttpInterfaceConfigurator();
	~HttpInterfaceConfigurator();
	HttpInterfaceConfigurator& on(const char* pszMethod, const char* pszResource, REQUEST_HANDLER handler);
	HttpInterfaceConfigurator& on(HttpMethods method, const char* pszResource, REQUEST_HANDLER handler);
	HttpInterfaceConfigurator& get(const char* pszResource, REQUEST_HANDLER handler);
	HttpInterfaceConfigurator& post(const char* pszResource, REQUEST_HANDLER handler);
};


#endif // !_HTTP_INTERGACE_CONFIGURATOR_H