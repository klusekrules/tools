#pragma once
#pragma warning( disable : 4251 )
#pragma warning( disable : 4275 )
#ifdef _WIN32
#   define NARZEDZIA_API __declspec(dllexport)
#   define NARZEDZIA_EXPIMP_TEMPLATE
#else
#   define NARZEDZIA_API 
#endif