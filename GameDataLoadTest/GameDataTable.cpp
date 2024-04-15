#include <iostream>
#include <fstream>

#include "Type.h" 

#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/filereadstream.h"

#include "GameDataTable.h"

using namespace std;
using namespace rapidjson;

namespace GDC
{
	std::string GDC_Util::ToLower(const std::string inValue)
	{
		std::string str = inValue;
		std::transform(str.begin(), str.end(), str.begin(), tolower);
		return str;
	}

	bool GDC_Util::AtoBool(const std::string inValue)
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

	bool GDC_Util::to_bool(const rapidjson::Value& inValue, const bool inDefalutVal)
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

	char GDC_Util::to_char(const rapidjson::Value& inValue, const char inDefalutVal)
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

	unsigned char GDC_Util::to_uchar(const rapidjson::Value& inValue, const unsigned char inDefalutVal)
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

	short GDC_Util::to_short(const rapidjson::Value& inValue, const short inDefalutVal)
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

	unsigned short GDC_Util::to_ushort(const rapidjson::Value& inValue, const unsigned short inDefalutVal)
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

	int	GDC_Util::to_int(const rapidjson::Value& inValue, const int inDefalutVal)
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

	unsigned int GDC_Util::to_uint(const rapidjson::Value& inValue, const unsigned int inDefalutVal)
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

	long GDC_Util::to_long(const rapidjson::Value& inValue, const long inDefalutVal)
	{
		int val = atol(inValue.GetString());
		if ((val > LONG_MAX) || (val < LONG_MIN))
		{
			_GDC_ASSERT("Invalid int Value");
			return inDefalutVal;
		}
		return val;
	}

	unsigned long GDC_Util::to_ulong(const rapidjson::Value& inValue, const unsigned long inDefalutVal)
	{
		unsigned long val = std::stoul(inValue.GetString());
		if ((val > ULONG_MAX) || (val < 0))
		{
			_GDC_ASSERT("Invalid unsigned Value");
			return inDefalutVal;
		}
		return static_cast<unsigned long>(val);
	}

	long long GDC_Util::to_longlong(const rapidjson::Value& inValue, const long long inDefalutVal)
	{
		long long val = atoll(inValue.GetString());
		if ((val > LLONG_MAX) || (val < LLONG_MIN))
		{
			_GDC_ASSERT("Invalid int Value");
			return inDefalutVal;
		}
		return val;
	}

	unsigned long long GDC_Util::to_ulonglong(const rapidjson::Value& inValue, const unsigned long long inDefalutVal)
	{
		unsigned long long val = std::stoull(inValue.GetString());
		if ((val > ULLONG_MAX) || (val < 0))
		{
			_GDC_ASSERT("Invalid int Value");
			return inDefalutVal;
		}
		return val;
	}

	std::string	 GDC_Util::to_string(const rapidjson::Value& inValue, const std::string& inDefalutVal)
	{
		if (inValue.IsNull())
			return inDefalutVal;

		return inValue.GetString();
	}

	float GDC_Util::to_float(const rapidjson::Value& inValue, const float inDefalutVal)
	{
		if (inValue.IsNull())
			return inDefalutVal;

		return std::stof(inValue.GetString());;
	}

	double GDC_Util::to_double(const rapidjson::Value& inValue, const double inDefalutVal)
	{
		if (inValue.IsNull())
			return inDefalutVal;

		return std::stod(inValue.GetString());;
	}

#pragma region GameDataTable
	void row_BaseType::Initialize(const Value& inValue)
	{
		_ID			= GDC_Util::to_int(inValue[0], _ID);
		_bool_		= GDC_Util::to_bool(inValue[1], _bool_);
		_char_		= GDC_Util::to_char(inValue[2], _char_);
		_uchar_		= GDC_Util::to_uchar(inValue[3], _uchar_);
		_short_		= GDC_Util::to_short(inValue[4], _short_);
		_ushort_	= GDC_Util::to_ushort(inValue[5], _ushort_);
		_int_		= GDC_Util::to_int(inValue[6], _int_);
		_uint_		= GDC_Util::to_uint(inValue[7], _uint_);
		_int64_		= GDC_Util::to_longlong(inValue[8], _int64_);
		_uint64_	= GDC_Util::to_ulonglong(inValue[9], _uint64_);
		_long_		= GDC_Util::to_long(inValue[10], _long_);
		_ulong_		= GDC_Util::to_ulong(inValue[11], _ulong_);
		_longlong_	= GDC_Util::to_longlong(inValue[12], _longlong_);
		_ulonglong_ = GDC_Util::to_ulonglong(inValue[13], _ulonglong_);
		_string_	= GDC_Util::to_string(inValue[14], _string_);
		_float_		= GDC_Util::to_float(inValue[15], _float_);
		_double_	= GDC_Util::to_double(inValue[16], _double_);
	}

	void row_BaseType::WriteLog() const
	{
		std::cout << "-------------------------" << std::endl;
		std::cout << "ID : " << _ID << std::endl;
		std::cout << "bool : " << _bool_ << std::endl;
		std::cout << "char : " << static_cast<int>(_char_) << std::endl;
		std::cout << "uchar : " << static_cast<int>(_uchar_) << std::endl;
		std::cout << "short : " << _short_ << std::endl;
		std::cout << "ushort : " << _ushort_ << std::endl;
		std::cout << "int : " << _int_ << std::endl;
		std::cout << "uint : " << _uint_ << std::endl;
		std::cout << "int64 : " << _int64_ << std::endl;
		std::cout << "uint64 : " << _uint64_ << std::endl;
		std::cout << "long : " << _long_ << std::endl;
		std::cout << "ulong : " << _ulong_ << std::endl;
		std::cout << "longlong : " << _longlong_ << std::endl;
		std::cout << "ulonglong : " << _ulonglong_ << std::endl;
		std::cout << "string : " << _string_ << std::endl;
		std::cout << "float : " << _float_ << std::endl;
		std::cout << "double : " << _double_ << std::endl;
		std::cout << "-------------------------" << std::endl;
	}

	void BaseType_Table::Initialize(const rapidjson::Value& inValue)
	{
		for (SizeType i = 0; i < inValue.Size(); i++)
		{
			row_BaseType row;
			row.Initialize(inValue[i]);
			_dataMap.insert(std::make_pair(row._ID, row));
		}
	}

	//void BaseType_Table::WriteLog() const
	//{

	//}

	void row_BaseType_temp::Initialize(const Value& inValue)
	{
		_ID = GDC_Util::to_int(inValue[0], _ID);
		_bool_ = GDC_Util::to_bool(inValue[1], _bool_);
		_char_ = GDC_Util::to_char(inValue[2], _char_);
		_uchar_ = GDC_Util::to_uchar(inValue[3], _uchar_);
		_short_ = GDC_Util::to_short(inValue[4], _short_);
		_ushort_ = GDC_Util::to_ushort(inValue[5], _ushort_);
		_int_ = GDC_Util::to_int(inValue[6], _int_);
		_uint_ = GDC_Util::to_uint(inValue[7], _uint_);
		_int64_ = GDC_Util::to_longlong(inValue[8], _int64_);
		_uint64_ = GDC_Util::to_ulonglong(inValue[9], _uint64_);
		_long_ = GDC_Util::to_long(inValue[10], _long_);
		_ulong_ = GDC_Util::to_ulong(inValue[11], _ulong_);
		_longlong_ = GDC_Util::to_longlong(inValue[12], _longlong_);
		_ulonglong_ = GDC_Util::to_ulonglong(inValue[13], _ulonglong_);
		_string_ = GDC_Util::to_string(inValue[14], _string_);
		_float_ = GDC_Util::to_float(inValue[15], _float_);
		_double_ = GDC_Util::to_double(inValue[16], _double_);
	}

	void row_BaseType_temp::WriteLog() const
	{
		std::cout << "-------------------------" << std::endl;
		std::cout << "ID : " << _ID << std::endl;
		std::cout << "bool : " << _bool_ << std::endl;
		std::cout << "char : " << static_cast<int>(_char_) << std::endl;
		std::cout << "uchar : " << static_cast<int>(_uchar_) << std::endl;
		std::cout << "short : " << _short_ << std::endl;
		std::cout << "ushort : " << _ushort_ << std::endl;
		std::cout << "int : " << _int_ << std::endl;
		std::cout << "uint : " << _uint_ << std::endl;
		std::cout << "int64 : " << _int64_ << std::endl;
		std::cout << "uint64 : " << _uint64_ << std::endl;
		std::cout << "long : " << _long_ << std::endl;
		std::cout << "ulong : " << _ulong_ << std::endl;
		std::cout << "longlong : " << _longlong_ << std::endl;
		std::cout << "ulonglong : " << _ulonglong_ << std::endl;
		std::cout << "string : " << _string_ << std::endl;
		std::cout << "float : " << _float_ << std::endl;
		std::cout << "double : " << _double_ << std::endl;
		std::cout << "-------------------------" << std::endl;
	}

	void BaseType_temp_Table::Initialize(const rapidjson::Value& inValue)
	{
		for (SizeType i = 0; i < inValue.Size(); i++)
		{
			row_BaseType_temp row;
			row.Initialize(inValue[i]);
			_dataMap.insert(std::make_pair(row._ID, row));
		}
	}

	//void BaseType_temp_Table::WriteLog() const
	//{
	//	std::cout << "-------------------------" << std::endl;
	//	std::cout << "Table Name - " << _name << std::endl;
	//	std::cout << "-------------------------" << std::endl;

	//	for (auto& data : _dataMap)
	//	{
	//		data.second.WriteLog();
	//	}
	//}
#pragma endregion // GameDataTable

} // namespace GDC