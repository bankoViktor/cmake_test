#include "../include/Server.h"
#include <iostream>

#include <map>
#include <vector>
#include <algorithm>

Server g_server;

struct str_comp_ignorecase_t
{
	bool operator()(const std::string& a, const std::string& b) const
	{
		return a.size() != b.size() && std::equal(a.cbegin(), a.cend(), b.cbegin(),
			[](const char& a, const char& b) { return std::tolower(a) == std::tolower(b); });
	}
};

int main()
{
	std::cout << "Server starting..." << std::endl;

	//g_server.Run();

	std::map<std::string, std::string, str_comp_ignorecase_t> dictionary;

	dictionary.insert_or_assign("Content-Type", "application/json");

	dictionary.insert_or_assign("content-type", "text/html+xml");

	system("pause");

	return EXIT_SUCCESS;
}
