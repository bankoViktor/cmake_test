#include "../include/Server.h"
#include "../../core/include/WinSock.h"
#include <iostream>
#include "../../core/include/HttpInterfaceConfigurator.h"

#define USING(obj)		{ obj;
#define USING_END()		}

Server::Server()
{
	WinSock::Initialization();

	m_pHttpInterface = nullptr;
}

Server::~Server()
{
	SafeReleasePonter(m_pHttpInterface);

	WinSock::Uninitialization();
}

void Server::Run()
{
	const char* pszStartupLibraryName = "startup.dll";
	const int dwPort = 80;

	USING(HMODULE hModule = LoadLibraryA(pszStartupLibraryName))
		if (!hModule)
		{
			std::cout << "The startup dynamic library '" << pszStartupLibraryName << "' not found." << std::endl;
			return;
		}
		else
		{
			STARTUPPROC srartupProc = (STARTUPPROC)GetProcAddress(hModule, "Startup");
			if (!srartupProc)
			{
				std::cout << "The startup function in '" << pszStartupLibraryName << "' not found." << std::endl;
				return;
			}

			USING(HttpInterfaceConfigurator configurator)
				srartupProc(configurator);
				m_pHttpInterface = new HttpInterface(configurator);
			USING_END() // configurator free

			m_pHttpInterface->Start(dwPort);

			std::cout << "Started on port " << dwPort << std::endl;

			while (true) {}

			FreeLibrary(hModule);
		}
	USING_END()
}
