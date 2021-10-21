#include "../include/startup.h"
#include "../../core/include/HttpInterface.h"
#include <iostream>


void indexWithRouteParamHandler(const HttpRequest& req, HttpResponse& resp)
{
	resp.SetStatusCode(HttpStatusCodes::NotFound);
	resp.Write("Document Not Found", "text/html");
}

void Startup(HttpInterfaceConfigurator& config)
{
	// ѕр€мое указани€ стандартного метода HTTP
	config.on(HttpMethods::Get, "/", [](const HttpRequest& req, HttpResponse& resp)
		{
			auto payload = "<!DOCTYPE><html lang=\"en\"><head><title>Test page</title></head><body><h2>Test page</h2></body></html>";
			resp.Write(payload, "text/html");
		}
	);

	// ѕользовательский метод пользовательского протокола на базе HTTP
	config.on("MAKE", "/", [](const HttpRequest& req, HttpResponse& resp)
		{
			std::cout << "make" << std::endl;
		}
	);

	config.post("/index", indexWithRouteParamHandler);
}
