#include "../include/startup.h"
#include "../../core/include/HttpInterface.h"
#include <iostream>


void Startup(HttpInterface& httpInterface)
{
	httpInterface.on(HttpMethods::Get, "/", [](const HttpRequest& req, HttpResponse& resp)
		{
			std::cout << req.m_pszMethod << "   " << req.m_pszUri << std::endl;
		}
	);
	httpInterface.get("/index", [](const HttpRequest& req, HttpResponse& resp)
		{
			std::cout << req.m_pszMethod << "   " << req.m_pszUri << "     " << " index page content " << std::endl;
		}
	);
}
