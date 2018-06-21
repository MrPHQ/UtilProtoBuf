// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files:
#include <windows.h>


#include <atomic>

// TODO: reference additional headers your program requires here


#ifdef _DEBUG
#pragma comment(lib,"google/protobuf/lib/libprotocd.lib")
#pragma comment(lib,"google/protobuf/lib/libprotobufd.lib")
#else
#pragma comment(lib,"google/protobuf/lib/libprotoc.lib")
#pragma comment(lib,"google/protobuf/lib/libprotobuf.lib")
#endif