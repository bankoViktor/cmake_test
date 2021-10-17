#include "../include/Server.h"
#include <iostream>

Server g_server;

int main()
{
	std::cout << "Server starting..." << std::endl;

	g_server.Run();

	system("pause");

	return EXIT_SUCCESS;
}
