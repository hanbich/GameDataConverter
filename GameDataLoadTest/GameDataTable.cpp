#include <iostream>
#include <fstream>

#include "Type.h" 

#include "GameDataUtil.h"
#include "GameDataTable.h"

using namespace std;
using namespace rapidjson;

namespace GDC
{
#pragma region GameDataTable
	void row_BaseType::Initialize(const Value& inValue)
	{
		_ID			= GameDataUtil::to_int(inValue[0], _ID);
		_bool_		= GameDataUtil::to_bool(inValue[1], _bool_);
		_char_		= GameDataUtil::to_char(inValue[2], _char_);
		_uchar_		= GameDataUtil::to_uchar(inValue[3], _uchar_);
		_short_		= GameDataUtil::to_short(inValue[4], _short_);
		_ushort_	= GameDataUtil::to_ushort(inValue[5], _ushort_);
		_int_		= GameDataUtil::to_int(inValue[6], _int_);
		_uint_		= GameDataUtil::to_uint(inValue[7], _uint_);
		_int64_		= GameDataUtil::to_longlong(inValue[8], _int64_);
		_uint64_	= GameDataUtil::to_ulonglong(inValue[9], _uint64_);
		_long_		= GameDataUtil::to_long(inValue[10], _long_);
		_ulong_		= GameDataUtil::to_ulong(inValue[11], _ulong_);
		_longlong_	= GameDataUtil::to_longlong(inValue[12], _longlong_);
		_ulonglong_ = GameDataUtil::to_ulonglong(inValue[13], _ulonglong_);
		_string_	= GameDataUtil::to_string(inValue[14], _string_);
		_float_		= GameDataUtil::to_float(inValue[15], _float_);
		_double_	= GameDataUtil::to_double(inValue[16], _double_);
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
		_ID = GameDataUtil::to_int(inValue[0], _ID);
		_bool_ = GameDataUtil::to_bool(inValue[1], _bool_);
		_char_ = GameDataUtil::to_char(inValue[2], _char_);
		_uchar_ = GameDataUtil::to_uchar(inValue[3], _uchar_);
		_short_ = GameDataUtil::to_short(inValue[4], _short_);
		_ushort_ = GameDataUtil::to_ushort(inValue[5], _ushort_);
		_int_ = GameDataUtil::to_int(inValue[6], _int_);
		_uint_ = GameDataUtil::to_uint(inValue[7], _uint_);
		_int64_ = GameDataUtil::to_longlong(inValue[8], _int64_);
		_uint64_ = GameDataUtil::to_ulonglong(inValue[9], _uint64_);
		_long_ = GameDataUtil::to_long(inValue[10], _long_);
		_ulong_ = GameDataUtil::to_ulong(inValue[11], _ulong_);
		_longlong_ = GameDataUtil::to_longlong(inValue[12], _longlong_);
		_ulonglong_ = GameDataUtil::to_ulonglong(inValue[13], _ulonglong_);
		_string_ = GameDataUtil::to_string(inValue[14], _string_);
		_float_ = GameDataUtil::to_float(inValue[15], _float_);
		_double_ = GameDataUtil::to_double(inValue[16], _double_);
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