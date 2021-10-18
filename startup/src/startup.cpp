#include "../include/startup.h"
#include "../../core/include/HttpInterface.h"
#include <iostream>

void indexWithRouteParamHandler(const HttpRequest& req, HttpResponse& resp)
{
	std::cout << req.m_pszMethod << "   " << req.m_pszUri << "     " << " index page content " << std::endl;
}

void Startup(HttpInterfaceConfigurator& config)
{
	// Прямое указания стандартного метода HTTP
	config.on(HttpMethods::Get, "/", [](const HttpRequest& req, HttpResponse& resp)
		{
			std::cout << req.m_pszMethod << "   " << req.m_pszUri << std::endl;
		}
	);

	// Пользовательский метод пользовательского протокола на базе HTTP
	config.on("MAKE", "/", [](const HttpRequest& req, HttpResponse& resp)
		{
			std::cout << req.m_pszMethod << "   " << req.m_pszUri << std::endl;
		}
	);

	config.get("/index/{id}", indexWithRouteParamHandler);
}
