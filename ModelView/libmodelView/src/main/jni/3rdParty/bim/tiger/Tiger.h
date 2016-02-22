#ifndef __YZTiger_H__
#define __YZTiger_H__
//#pragma warning (disable : 4251)

#ifdef _WIN32
#ifdef MODELDB_EXPORTS
#define MODELDB_API __declspec(dllexport)
#else
#define MODELDB_API __declspec(dllimport)
#endif
#else
#define MODELDB_API
#endif

#include "YZPrerequire.h"

namespace YZ
{
	//DB版本号
	static const std::string YZModelDBVersion = _u8("1.2.0");
}

#endif