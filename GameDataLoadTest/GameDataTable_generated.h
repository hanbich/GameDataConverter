#pragma once

//! @file   GameDataTable_generated.h
//! @brief  자동 생성된 파일입니다. 임의로 수정하지 마세요.

#ifndef __GDC_GAMEDATATABLE_GENERATED_H__
#define __GDC_GAMEDATATABLE_GENERATED_H__

namespace GDC
{
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
        virtual ~TableBase() = default;

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
        std::string _name;

        std::map<int, T> _dataMap;
    };

    class row_BaseType : public row_TableBase
    {
    public:
        row_BaseType() = default;
        ~row_BaseType() = default;

    public:
        virtual void Initialize(const rapidjson::Value& inValue);
        virtual void WriteLog() const;

    public:
        int _ID = 0;
        bool _bool_ = false;
        char _char_ = 0;
        unsigned char _uchar_ = 0;
        short _short_ = 0;
        unsigned short _ushort_ = 0;
        int _int_ = 0;
        unsigned int _uint_ = 0;
        long long _int64_ = 0;
        unsigned long long _uint64_ = 0;
        long _long_ = 0;
        unsigned long _ulong_ = 0;
        long long _longlong_ = 0;
        unsigned long long _ulonglong_ = 0;
        std::string _string_ = "";
        float _float_ = 0.0f;
        double _double_ = 0.0;
    };

    class BaseType_Table : public TableBase<row_BaseType>
    {
    public:
        BaseType_Table() : TableBase("BaseType"){}
        ~BaseType_Table() = default;
        BaseType_Table(BaseType_Table const&) = delete;
        void operator=(BaseType_Table const&) = delete;

        virtual void Initialize(const rapidjson::Value& inValue);
    };

    class row_BaseType_temp : public row_TableBase
    {
    public:
        row_BaseType_temp() = default;
        ~row_BaseType_temp() = default;

    public:
        virtual void Initialize(const rapidjson::Value& inValue);
        virtual void WriteLog() const;

    public:
        int _ID = 0;
        bool _bool_ = false;
        char _char_ = 0;
        unsigned char _uchar_ = 0;
        short _short_ = 0;
        unsigned short _ushort_ = 0;
        int _int_ = 0;
        unsigned int _uint_ = 0;
        long long _int64_ = 0;
        unsigned long long _uint64_ = 0;
        long _long_ = 0;
        unsigned long _ulong_ = 0;
        long long _longlong_ = 0;
        unsigned long long _ulonglong_ = 0;
        std::string _string_ = "";
        float _float_ = 0.0f;
        double _double_ = 0.0;
    };

    class BaseType_temp_Table : public TableBase<row_BaseType_temp>
    {
    public:
        BaseType_temp_Table() : TableBase("BaseType_temp"){}
        ~BaseType_temp_Table() = default;
        BaseType_temp_Table(BaseType_temp_Table const&) = delete;
        void operator=(BaseType_temp_Table const&) = delete;

        virtual void Initialize(const rapidjson::Value& inValue);
    };

}
#endif // 
