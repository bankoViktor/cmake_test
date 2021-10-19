#include "../include/Utils.h"
#include <algorithm>


bool StringCompare(const char* a, const char* b, bool caseInsensitive)
{
	size_t la = strlen(a);
	size_t lb = strlen(b);
	if (la != lb) return false;
	for (lb = 0; lb < la; ++lb)
	{
		if (toupper(a[lb]) != toupper(b[lb])) return false;
	}
	return true;
}

void ToUpper(std::string& str)
{
	std::transform(str.begin(), str.end(), str.begin(), ::toupper);
}

void ToLower(std::string& str)
{
	std::transform(str.begin(), str.end(), str.begin(), ::tolower);
}

void LeftTrim(std::string& str)
{
	str.erase(0, str.find_first_not_of(" \r\n\t"));
}
