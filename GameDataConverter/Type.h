#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <map>
#include <queue>
#include <typeinfo>
#include <typeindex>
#include <cassert>
#include <time.h>
#include <random>

#include "Singleton.h"

typedef char	int8;
typedef short	int16;
typedef __int32	int32;
typedef __int64	int64;

typedef unsigned char		uint8;
typedef unsigned short		uint16;
typedef unsigned __int32	uint32;
typedef unsigned __int64	uint64;

typedef std::string		tstring;

typedef std::vector<int32> Int32Vec;
typedef std::vector<int8>  Int8Vec;

using namespace GDC;

#define _LOG_FUNCTION_START   std::cout << "-- " << __FUNCTION__ << " CodeLine : " << __LINE__ << " START --\n"
#define _LOG_FUNCTION_END	  std::cout << "-- " << __FUNCTION__ << " CodeLine : " << __LINE__ << " E N D --\n"
//#define _LA1_ASSERT(x, y)	 if(false == x) std::cout << "Assert - Message : " << #y << "\n"; assert(x);
#define _LA1_ASSERT(Message) std::cout << "Assert - Function : " << __FUNCTION__ << " - Message : " << #Message << "\n"; assert(false)