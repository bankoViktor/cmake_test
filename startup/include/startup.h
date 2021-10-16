#ifndef _STARTUP_H
#define _STARTUP_H


#define EXPORTED __declspec(dllexport)

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

EXPORTED int startup(void* pArg);

#ifdef __cplusplus
}
#endif // __cplusplus


#endif // !_STARTUP_H
