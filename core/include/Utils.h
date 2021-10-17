#ifndef _UTILS_H
#define _UTILS_H

#include <string>


#define SafeReleasePonter(ptr)		if (ptr){ delete ptr; ptr = nullptr; }


#ifdef __cplusplus
extern "C" {
#endif


bool StringCompare(const char* a, const char* b, bool caseInsensitive = false);
void ToUpper(std::string& str);
void ToLower(std::string& str);
void LeftTrim(std::string& str);


#ifdef __cplusplus
}
#endif


#endif // !_UTILS_H
