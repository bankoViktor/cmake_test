#include "../include/startup.h"
#include "../../core/include/HttpInterface.h"
#include <iostream>

void indexWithRouteParamHandler(const HttpRequest& req, HttpResponse& resp)
{
	std::cout << req.m_sMethod << "   " << req.m_sUri << "     " << " index page content " << std::endl;
}

void Startup(HttpInterfaceConfigurator& config)
{
	// ѕр€мое указани€ стандартного метода HTTP
	config.on(HttpMethods::Get, "/", [](const HttpRequest& req, HttpResponse& resp)
		{
			std::cout << req.m_sMethod << "   " << req.m_sUri << std::endl;
		}
	);

	// ѕользовательский метод пользовательского протокола на базе HTTP
	config.on("MAKE", "/", [](const HttpRequest& req, HttpResponse& resp)
		{
			std::cout << req.m_sMethod << "   " << req.m_sUri << std::endl;
		}
	);

	config.get("/index/{id}", indexWithRouteParamHandler);
}
