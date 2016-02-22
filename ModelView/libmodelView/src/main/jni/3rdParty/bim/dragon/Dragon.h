#ifndef __YZDRAGON_H__
#define __YZDRAGON_H__
//#pragma warning (disable : 4251)
//#pragma warning (disable : 4996)

#ifdef _WIN32
#ifdef MODEL_EXPORTS
#define MODEL_API __declspec(dllexport)
#else
#define MODEL_API __declspec(dllimport)
#endif
#else
#define MODEL_API
#endif

#include "YZPrerequire.h"

namespace YZ
{
	//MODEL版本号
	//static const char* YZModelVersion = _u8("1.2.0");
}

#endif