#pragma once
//! @date   2024/04/15
//! @file   GameDataUtil.h
//! @author chsoo82
//! @brief  
//!         

#ifndef __GDC_GAME_DATA_UTIL_H__
#define __GDC_GAME_DATA_UTIL_H__

namespace GDC
{
	class GameDataUtil
	{
	public:
		GameDataUtil() = default;
		~GameDataUtil() = default;

	private:
		static std::string ToLower(const std::string inValue);
		static bool AtoBool(const std::string inValue);

	public:
		static bool to_bool(const rapidjson::Value& inValue, const bool inDefalutVal);
		static char to_char(const rapidjson::Value& inValue, const char inDefalutVal);
		static unsigned char to_uchar(const rapidjson::Value& inValue, const unsigned char inDefalutVal);
		static short to_short(const rapidjson::Value& inValue, const short inDefalutVal);
		static unsigned short to_ushort(const rapidjson::Value& inValue, const unsigned short inDefalutVal);
		static int	to_int(const rapidjson::Value& inValue, const int inDefalutVal);
		static unsigned int to_uint(const rapidjson::Value& inValue, const unsigned int inDefalutVal);
		static long to_long(const rapidjson::Value& inValue, const long inDefalutVal);
		static unsigned long to_ulong(const rapidjson::Value& inValue, const unsigned long inDefalutVal);
		static long long to_longlong(const rapidjson::Value& inValue, const long long inDefalutVal);
		static unsigned long long to_ulonglong(const rapidjson::Value& inValue, const unsigned long long inDefalutVal);
		static std::string	 to_string(const rapidjson::Value& inValue, const std::string& inDefalutVal);
		static float  to_float(const rapidjson::Value& inValue, const float inDefalutVal);
		static double  to_double(const rapidjson::Value& inValue, const double inDefalutVal);
	};

} // namespace GDC

#endif // __GDC_GAME_DATA_UTIL_H__