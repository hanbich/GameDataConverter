#include <iostream>
#include <fstream>

#include "GameDataType.h" 

#include "GameDataUtil.h"

using namespace std;
using namespace rapidjson;

namespace GDC
{
#pragma region GameDataUtil
	std::string GameDataUtil::ToLower(const std::string inValue)
	{
		std::string str = inValue;
		std::transform(str.begin(), str.end(), str.begin(), tolower);
		return str;
	}

	bool GameDataUtil::AtoBool(const std::string inValue)
	{
		std::string&& str = ToLower(inValue);
		if (str == "true")
			return true;
		else if (str == "false")
			return false;
		else
			_GDC_ASSERT("Invalid Bool Value");

		return false;
	}

	bool GameDataUtil::to_bool(const rapidjson::Value& inValue, const bool inDefalutVal)
	{
		if (inValue.IsNull())
			return inDefalutVal;

		if (inValue.IsBool())
			return inValue.GetBool();
		else if (inValue.IsString())
			return AtoBool(inValue.GetString());
		else
			_GDC_ASSERT("Invalid Bool Value");

		return inDefalutVal;
	}

	char GameDataUtil::to_char(const rapidjson::Value& inValue, const char inDefalutVal)
	{
		if (inValue.IsNull())
			return inDefalutVal;

		int val = atoi(inValue.GetString());
		if ((val > CHAR_MAX) || (val < CHAR_MIN))
		{
			_GDC_ASSERT("Invalid char Value");
			return inDefalutVal;
		}
		return static_cast<char>(val);
	}

	unsigned char GameDataUtil::to_uchar(const rapidjson::Value& inValue, const unsigned char inDefalutVal)
	{
		if (inValue.IsNull())
			return inDefalutVal;

		int val = atoi(inValue.GetString());
		if ((val > UCHAR_MAX) || (val < 0))
		{
			_GDC_ASSERT("Invalid unsigned char Value");
			return inDefalutVal;
		}
		return static_cast<unsigned char>(val);
	}

	short GameDataUtil::to_short(const rapidjson::Value& inValue, const short inDefalutVal)
	{
		if (inValue.IsNull())
			return inDefalutVal;

		int val = atoi(inValue.GetString());
		if ((val > SHRT_MAX) || (val < SHRT_MIN))
		{
			_GDC_ASSERT("Invalid short Value");
			return inDefalutVal;
		}
		return static_cast<short>(val);
	}

	unsigned short GameDataUtil::to_ushort(const rapidjson::Value& inValue, const unsigned short inDefalutVal)
	{
		if (inValue.IsNull())
			return inDefalutVal;

		int val = atoi(inValue.GetString());
		if ((val > USHRT_MAX) || (val < 0))
		{
			_GDC_ASSERT("Invalid unsigned short Value");
			return inDefalutVal;
		}
		return static_cast<unsigned short>(val);
	}

	int	GameDataUtil::to_int(const rapidjson::Value& inValue, const int inDefalutVal)
	{
		if (inValue.IsNull())
			return inDefalutVal;

		int val = atoi(inValue.GetString());
		if ((val > INT_MAX) || (val < INT_MIN))
		{
			_GDC_ASSERT("Invalid int Value");
			return inDefalutVal;
		}
		return val;
	}

	unsigned int GameDataUtil::to_uint(const rapidjson::Value& inValue, const unsigned int inDefalutVal)
	{
		if (inValue.IsNull())
			return inDefalutVal;

		std::string str = inValue.GetString();
		long long val = std::stoll(inValue.GetString());
		if ((val > UINT_MAX) || (val < 0))
		{
			_GDC_ASSERT("Invalid unsigned Value");
			return inDefalutVal;
		}
		return static_cast<unsigned int>(val);
	}

	long GameDataUtil::to_long(const rapidjson::Value& inValue, const long inDefalutVal)
	{
		int val = atol(inValue.GetString());
		if ((val > LONG_MAX) || (val < LONG_MIN))
		{
			_GDC_ASSERT("Invalid int Value");
			return inDefalutVal;
		}
		return val;
	}

	unsigned long GameDataUtil::to_ulong(const rapidjson::Value& inValue, const unsigned long inDefalutVal)
	{
		unsigned long val = std::stoul(inValue.GetString());
		if ((val > ULONG_MAX) || (val < 0))
		{
			_GDC_ASSERT("Invalid unsigned Value");
			return inDefalutVal;
		}
		return static_cast<unsigned long>(val);
	}

	long long GameDataUtil::to_longlong(const rapidjson::Value& inValue, const long long inDefalutVal)
	{
		long long val = atoll(inValue.GetString());
		if ((val > LLONG_MAX) || (val < LLONG_MIN))
		{
			_GDC_ASSERT("Invalid int Value");
			return inDefalutVal;
		}
		return val;
	}

	unsigned long long GameDataUtil::to_ulonglong(const rapidjson::Value& inValue, const unsigned long long inDefalutVal)
	{
		unsigned long long val = std::stoull(inValue.GetString());
		if ((val > ULLONG_MAX) || (val < 0))
		{
			_GDC_ASSERT("Invalid int Value");
			return inDefalutVal;
		}
		return val;
	}

	long long GameDataUtil::to_int64(const rapidjson::Value& inValue, const long long inDefalutVal)
	{
		long long val = atoll(inValue.GetString());
		if ((val > LLONG_MAX) || (val < LLONG_MIN))
		{
			_GDC_ASSERT("Invalid int Value");
			return inDefalutVal;
		}
		return val;
	}

	unsigned long long GameDataUtil::to_uint64(const rapidjson::Value& inValue, const unsigned long long inDefalutVal)
	{
		unsigned long long val = std::stoull(inValue.GetString());
		if ((val > ULLONG_MAX) || (val < 0))
		{
			_GDC_ASSERT("Invalid int Value");
			return inDefalutVal;
		}
		return val;
	}

	std::string	 GameDataUtil::to_string(const rapidjson::Value& inValue, const std::string& inDefalutVal)
	{
		if (inValue.IsNull())
			return inDefalutVal;

		return inValue.GetString();
	}

	float GameDataUtil::to_float(const rapidjson::Value& inValue, const float inDefalutVal)
	{
		if (inValue.IsNull())
			return inDefalutVal;

		return std::stof(inValue.GetString());;
	}

	double GameDataUtil::to_double(const rapidjson::Value& inValue, const double inDefalutVal)
	{
		if (inValue.IsNull())
			return inDefalutVal;

		return std::stod(inValue.GetString());;
	}

#pragma endregion // GameDataUtil
} // namespace GDC