#pragma once


#ifdef _WIN32
#define Function_Extern extern "C" __declspec(dllexport)
#else
#define Function_Extern extern "C"
#endif