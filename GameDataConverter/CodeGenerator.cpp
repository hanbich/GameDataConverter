#include <iostream>
#include <fstream>
#include <format>

#include "Type.h"

#include "ConfigJsonParser.h"
#include "DataCoordinator.h"
#include "CodeGenerator.h"

using namespace std;
using namespace rapidjson;

namespace GDC
{
#pragma region CodeGenerator
	CodeGenerator::CodeGenerator(const tstring& inFileName)
		: _fileName(inFileName)
	{
		string path = ConfigJsonParser::Get()->GetWritePath();
		path += inFileName;
		_ofStreamPtr = make_shared<ofstream>(path, std::ios::out | std::ios::trunc); // 파일의 내용을 모두 삭제하고 쓰기 모드로 열기
		if((_ofStreamPtr == nullptr) || (_ofStreamPtr->fail()))
		{
			tstring message = "Failed to open file: " + path;
			if (_ofStreamPtr != nullptr)
				_ofStreamPtr->close();

			_GDC_ASSERT(message);
		}
	}

	CodeGenerator::~CodeGenerator()
	{
		if(_ofStreamPtr != nullptr)
			_ofStreamPtr->close();
	}

	void CodeGenerator::AddTeb(int inTabCount)
	{
		for(int i = 0; i < inTabCount; ++i)
		{
			GetOfstream() << "    ";
		}
	}

	void CodeGenerator::AddLineBase(const tstring& inLine)
	{
		GetOfstream() << inLine << endl;
	}

	void CodeGenerator::AddLine(const tstring& inLine, int inTabCount)
	{
		AddTeb(inTabCount);
		AddLineBase(inLine);
	}

	tstring CodeGenerator::GetRowClassName(const tstring& inTableName) const
	{
		return "row_" + inTableName;
	}

	tstring CodeGenerator::GetTableClassName(const tstring& inTableName) const
	{
		return inTableName + "_Table";
	}

	tstring CodeGenerator::GetMemberValueName(const ColumnInfo& inColumnInfo) const
	{
		return "_" + inColumnInfo._name;
	}

	tstring CodeGenerator::GetValueType(const ColumnInfo& inColumnInfo) const
	{
		static map<tstring, tstring> typeMap = {
			{"bool", "bool"},
			{"char", "char"},
			{"uchar", "unsigned char"},
			{"short", "short"},
			{"ushort", "unsigned short"},
			{"int", "int"},
			{"uint", "unsigned int"},
			{"int64", "long long"},
			{"uint64", "unsigned long long"},
			{"long", "long"},
			{"ulong", "unsigned long"},
			{"longlong", "long long"},
			{"ulonglong", "unsigned long long"},
			{"string", "std::string"},
			{"float", "float"},
			{"double", "double"}
		};

		return typeMap[inColumnInfo._type];
	}
#pragma endregion // CodeGenerator

#pragma region HeaderFileGenerator
	HeaderFileGenerator::HeaderFileGenerator(const tstring inFileName)
		: CodeGenerator(inFileName)
	{
		tstring tmpFileName = inFileName;
		transform(tmpFileName.begin(), tmpFileName.end(), tmpFileName.begin(), ::toupper);

		_defFileName = "__GDC_" + tmpFileName + "__";
	}

	HeaderFileGenerator::~HeaderFileGenerator()
	{

	}

	void HeaderFileGenerator::Generate(const DataCoordinator& inDataCoordinator)
	{
		StartStream();
		BaseClassStream();

		for (const auto& tableDataPair : inDataCoordinator.GetTableDataPtrMap())
		{
			RawClassStream(tableDataPair.first, tableDataPair.second);
			TableClassStream(tableDataPair.first, tableDataPair.second);
		}

		EndStream();
	}

	void HeaderFileGenerator::StartStream()
	{
		AddLine("#pragma once");
		AddLine("");
		AddLine("//! @file   " + GetFileName());
		AddLine("//! @brief  자동 생성된 파일입니다. 임의로 수정하지 마세요.");
		AddLine("");
		AddLine("#ifndef " + _defFileName);
		AddLine("#define " + _defFileName);
		AddLine("");
		AddLine("namespace GDC");
		AddLine("{");
	}

	void HeaderFileGenerator::EndStream()
	{
		AddLine("}");
		AddLine("#endif // " + _defFileName);
	}

	void HeaderFileGenerator::BaseClassStream()
	{
		const i32 tabCount = 1;

		AddLine("class row_TableBase", tabCount);
		AddLine("{", tabCount);
		AddLine("public:", tabCount);
		AddLine("row_TableBase() = default;", tabCount + 1);
		AddLine("~row_TableBase() = default;", tabCount + 1);
		AddLine("");
		AddLine("public:", tabCount);
		AddLine("virtual void Initialize(const rapidjson::Value& inValue) = 0;", tabCount + 1);
		AddLine("virtual void WriteLog() const = 0;", tabCount + 1);
		AddLine("};", tabCount);
		AddLine("");

		AddLine("template <class T>", tabCount);
		AddLine("class TableBase", tabCount);
		AddLine("{", tabCount);
		AddLine("public:", tabCount);
		AddLine("TableBase(const std::string& inName) : _name(inName) {}", tabCount + 1);
		AddLine("virtual ~TableBase() = default;", tabCount + 1);
		AddLine("");
		AddLine("const std::string& GetName() const { return _name; }", tabCount + 1);
		AddLine("virtual void Initialize(const rapidjson::Value& inValue) = 0;", tabCount + 1);
		AddLine("");
		AddLine("void WriteLog() const", tabCount + 1);
		AddLine("{", tabCount + 1);
		AddLine("std::cout << \"-------------------------\" << std::endl;", tabCount + 2);
		AddLine("std::cout << \"Table Name - \" << _name << std::endl;", tabCount + 2);
		AddLine("std::cout << \"-------------------------\" << std::endl;", tabCount + 2);
		AddLine("");
		AddLine("for (auto& data : _dataMap)", tabCount + 2);
		AddLine("{", tabCount + 2);
		AddLine("data.second.WriteLog();", tabCount + 3);
		AddLine("}", tabCount + 2);
		AddLine("}", tabCount + 1);
		AddLine("");
		AddLine("protected:", tabCount);
		AddLine("std::string _name;", tabCount + 1);
		AddLine("");
		AddLine("std::map<int, T> _dataMap;", tabCount + 1);
		AddLine("};", tabCount);
		AddLine("");
	}

	tstring HeaderFileGenerator::GetDefaultValue(const ColumnInfo& inColumnInfo) const
	{
		tstring valType = inColumnInfo._type;
		tstring defaultVal = inColumnInfo._defaultValue;
		if ((valType == "bool") || (valType == "BOOL"))
		{
			transform(defaultVal.begin(), defaultVal.end(), defaultVal.begin(), ::tolower);
		}
		else if ((valType == "float") || (valType == "double"))
		{
			defaultVal = defaultVal + "f";
		}
		else if (valType == "string")
		{
			defaultVal = "\"" + defaultVal + "\"";
		}

		return defaultVal;
	}

	void HeaderFileGenerator::RawClassMemberStream(const ColumnInfo& inColumnInfo, const i32 inTabCount)
	{
		const tstring&& valueType = GetValueType(inColumnInfo);
		const tstring&& valueName = GetMemberValueName(inColumnInfo);
		const tstring&& defaultVal = GetDefaultValue(inColumnInfo);

		AddLine(std::format("{} {} = {};", valueType, valueName, defaultVal), inTabCount);
	}

	void HeaderFileGenerator::RawClassStream(const tstring& inTableName, const TableDataPtr inTableDataPtr)
	{
		const i32 tabCount = 1;
		const tstring rowClassName = GetRowClassName(inTableName);

		AddLine(std::format("class {} : public row_TableBase", rowClassName), tabCount);
		AddLine("{", tabCount);
		AddLine("public:", tabCount);
		AddLine(std::format("{}() = default;", rowClassName), tabCount + 1);
		AddLine(std::format("~{}() = default;", rowClassName), tabCount + 1);
		AddLine("");
		AddLine("public:", tabCount);
		AddLine("virtual void Initialize(const rapidjson::Value& inValue);", tabCount + 1);
		AddLine("virtual void WriteLog() const;", tabCount + 1);
		AddLine("");
		AddLine("public:", tabCount);
		for (const auto& columnData : inTableDataPtr->GetColumnInfoVec())
		{
			RawClassMemberStream(columnData, tabCount + 1);
		}
		AddLine("}", tabCount);
		AddLine("");
	}

	void HeaderFileGenerator::TableClassStream(const tstring& inTableName, const TableDataPtr inTableDataPtr)
	{
		const i32 tabCount = 1;
		const tstring rowClassName = GetRowClassName(inTableName);
		const tstring tableClassName = GetTableClassName(inTableName);

		AddLine(std::format("class {} : public TableBase<{}>", tableClassName, rowClassName), tabCount);
		AddLine("{", tabCount);
		AddLine("public:", tabCount);
		AddLine(std::format("{}() : TableBase(\"{}\")", tableClassName, inTableName) + "{}", tabCount + 1);
		AddLine(std::format("~{}() = default;", tableClassName), tabCount + 1);
		AddLine("");
		AddLine("virtual void Initialize(const rapidjson::Value& inValue);", tabCount + 1);
		AddLine("}", tabCount);
		AddLine("");
	}
#pragma endregion // HeaderFileGenerator

#pragma region SourceFileGenerator
	SourceFileGenerator::SourceFileGenerator(const tstring inFileName)
		: CodeGenerator(inFileName)
	{

	}

	SourceFileGenerator::~SourceFileGenerator()
	{

	}

	void SourceFileGenerator::Generate(const DataCoordinator& inDataCoordinator)
	{
		StartStream();

		for (const auto& tableDataPair : inDataCoordinator.GetTableDataPtrMap())
		{
			TableClassStream(tableDataPair.first, tableDataPair.second);
		}

		EndStream();
	}

	void SourceFileGenerator::StartStream()
	{
		AddLine("//! @file   " + GetFileName());
		AddLine("//! @brief  자동 생성된 파일입니다. 임의로 수정하지 마세요.");
		AddLine("");
		AddLine("#include <iostream>");
		AddLine("#include <fstream>");
		AddLine("");
		AddLine("#include \"Type.h\"");
		AddLine("");
		AddLine("#include \"ConfigJsonParser.h\"");
		AddLine("#include \"SourceGenerator.h\"");
		AddLine("");
		AddLine("using namespace std;");
		AddLine("using namespace rapidjson;");
		AddLine("");
		AddLine("namespace GDC");
		AddLine("{");
	}

	void SourceFileGenerator::EndStream()
	{
		AddLine("}");
	}

	void SourceFileGenerator::TableClassStream(const tstring& inTableName, const TableDataPtr inTableDataPtr)
	{
		//AddLine("}");
		//AddLine("#endif // " + _defFileName);
	}

#pragma endregion // SourceFileGenerator
} // namespace GDC
