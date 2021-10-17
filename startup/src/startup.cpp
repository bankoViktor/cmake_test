#include "../include/startup.h"
#include "../../core/include/HttpInterface.h"
#include <iostream>


void Startup(HttpInterface& httpInterface)
{
	httpInterface.on(HttpMethods::Get, "/", [](const HttpRequest& req, HttpResponse& resp)
	{
			std::cout << "/" << std::endl;
	});
	httpInterface.get("/index", [](const HttpRequest& req, HttpResponse& resp)
	{
		std::cout << "/index" << std::endl;
	});
}
