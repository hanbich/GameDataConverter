#pragma once
//! @date   2024/03/14
//! @file   GameDataTable.h
//! @author chsoo82
//! @brief  자동 생성된 파일입니다. 임의로 수정하지 마십시오.
//!         게임데이터를 로드하기 위한 row 타입 정의 입니다.

#ifndef __GDC_GAME_DATA_TABLE_H__
#define __GDC_GAME_DATA_TABLE_H__

namespace GDC
{
	class GDC_Util
	{
	public:
		GDC_Util() = default;
		~GDC_Util() = default;

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

#pragma region GameDataTable
	class row_TableBase
	{
	public:
		row_TableBase() = default;
		~row_TableBase() = default;

	public:
		virtual void Initialize(const rapidjson::Value& inValue) = 0;
		virtual void WriteLog() const = 0;
	};

	template <class T>
	class TableBase
	{
	public:
		TableBase(const std::string& inName) : _name(inName) {}
		~TableBase() = default;

		const std::string& GetName() const { return _name; }
		virtual void Initialize(const rapidjson::Value& inValue) = 0;

		void WriteLog() const
		{
			std::cout << "-------------------------" << std::endl;
			std::cout << "Table Name - " << _name << std::endl;
			std::cout << "-------------------------" << std::endl;

			for (auto& data : _dataMap)
			{
				data.second.WriteLog();
			}
		}

	protected:
		std::string	_name;

		std::map<int, T> _dataMap;
	};

	class row_BaseType : public row_TableBase
	{
	public:
		row_BaseType() = default;
		~row_BaseType() = default;

	public:
		void Initialize(const rapidjson::Value& inValue);
		void WriteLog() const;

	public:
		int		_ID = 0;
		bool	_bool_ = false;
		char	_char_ = 0;
		unsigned char	_uchar_ = 0;
		short	_short_ = 0;
		unsigned short	_ushort_ = 0;
		int		_int_ = 0;
		unsigned int	_uint_ = 0;
		long long	_int64_ = 0;
		unsigned long long	_uint64_ = 0;
		long	_long_ = 0;
		unsigned long	_ulong_ = 0;
		long long	_longlong_ = 0;
		unsigned long long	_ulonglong_ = 0;
		std::string	_string_ = "";
		float	_float_ = 0.f;
		double	_double_ = 0.0f;
	};

	class BaseType_Table : public TableBase<row_BaseType>
	{
	public:
		BaseType_Table() : TableBase("BaseType") {}
		~BaseType_Table() = default;

		void Initialize(const rapidjson::Value& inValue);
		//void WriteLog() const;
	};

	class row_BaseType_temp : public row_TableBase
	{
	public:
		row_BaseType_temp() = default;
		~row_BaseType_temp() = default;

	public:
		void Initialize(const rapidjson::Value& inValue);
		void WriteLog() const;

	public:
		int		_ID = 0;
		bool	_bool_ = false;
		char	_char_ = 0;
		unsigned char	_uchar_ = 0;
		short	_short_ = 0;
		unsigned short	_ushort_ = 0;
		int		_int_ = 0;
		unsigned int	_uint_ = 0;
		long long	_int64_ = 0;
		unsigned long long	_uint64_ = 0;
		long	_long_ = 0;
		unsigned long	_ulong_ = 0;
		long long	_longlong_ = 0;
		unsigned long long	_ulonglong_ = 0;
		std::string	_string_ = "";
		float	_float_ = 0.f;
		double	_double_ = 0.0f;
	};

	class BaseType_temp_Table : public TableBase<row_BaseType_temp>
	{
	public:
		BaseType_temp_Table() : TableBase("BaseType_temp") {}
		~BaseType_temp_Table() = default;

		void Initialize(const rapidjson::Value& inValue);
		//void WriteLog() const;
	};
#pragma endregion // GameDataTable

} // namespace GDC

#endif // __GDC_GAME_DATA_TABLE_H__