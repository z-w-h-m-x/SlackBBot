#ifdef _WIN32
#define APIEXPORT extern "C" __declspec(dllexport)
#else
#define APIEXPORT extern "C"
#endif