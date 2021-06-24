#pragma once

#ifdef _MYDLL_EXPORT

#define DLL_API _declspec(dllexport)

#else

#define DLL_API _declspec(dllimport)

#endif


DLL_API int Add(int, int);
