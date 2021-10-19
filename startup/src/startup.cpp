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
			resp.Write("<!DOCTYPE><html lang=\"en\"><head><title>Test page</title></head><body><h2>Test page</h2><body></html>");
		}
	);

	// ѕользовательский метод пользовательского протокола на базе HTTP
	config.on("MAKE", "/", [](const HttpRequest& req, HttpResponse& resp)
		{
			std::cout << "make" << std::endl;
		}
	);

	config.get("/index/{id}", indexWithRouteParamHandler);
}
