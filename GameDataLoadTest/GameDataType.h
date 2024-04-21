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

#include <unordered_map>

#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/filereadstream.h"

#include "Singleton.h"

typedef char	i8;
typedef short	i16;
typedef __int32	i32;
typedef __int64	i64;

typedef unsigned char		ui8;
typedef unsigned short		ui16;
typedef unsigned __int32	ui32;
typedef unsigned __int64	ui64;

typedef std::string			tstring;

typedef std::vector<i32> I32Vec;
typedef std::vector<i8>  I8Vec;
typedef std::vector<tstring> tstrVec;

using namespace GDC;

#define _LOG_FUNCTION_START   std::cout << "-- " << __FUNCTION__ << " CodeLine : " << __LINE__ << " START --\n"
#define _LOG_FUNCTION_END	  std::cout << "-- " << __FUNCTION__ << " CodeLine : " << __LINE__ << " E N D --\n"
//#define _GDC_ASSERT(x, y)	 if(false == x) std::cout << "Assert - Message : " << #y << "\n"; assert(x);
#define _GDC_ASSERT(Message) std::cout << "Assert - Function : " << __FUNCTION__ << " - Message : " << #Message << "\n"; assert(false)