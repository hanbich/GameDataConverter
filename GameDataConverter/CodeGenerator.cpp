#include <iostream>
#include <fstream>

#include "Type.h"

#include "ConfigJsonParser.h"
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
		_ofStreamPtr = make_shared<ofstream>(path, std::ios::out | std::ios::trunc);
		if((_ofStreamPtr == nullptr) || (_ofStreamPtr->fail()))
		{
			tstring message = "Failed to open file: " + path;
			_GDC_ASSERT(message);
		}
	}

	CodeGenerator::~CodeGenerator()
	{
		if(_ofStreamPtr != nullptr)
		{
			_ofStreamPtr->close();
		}
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

	void CodeGenerator::CodeGenerator::AddLine(const tstring& inLine, int inTabCount)
	{
		AddTeb(inTabCount);
		AddLineBase(inLine);
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

	void HeaderFileGenerator::Generate()
	{
		StartStream();
		BaseClassStream();
		EndStream();
	}

	void HeaderFileGenerator::StartStream()
	{
		AddLine("#pragma once");
		AddLine("");
		AddLine("//! @file   " + GetFileName());
		AddLine("//! @brief  자동 생성된 파일입니다. 임의로 수정하지 마십시오.");
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

		//class row_TableBase
		//{
		//public:
		//	row_TableBase() = default;
		//	~row_TableBase() = default;

		//public:
		//	virtual void Initialize(const rapidjson::Value& inValue) = 0;
		//	virtual void WriteLog() const = 0;
		//};

		//template <class T>
		//class TableBase
		//{
		//public:
		//	TableBase(const std::string& inName) : _name(inName) {}
		//	~TableBase() = default;

		//	const std::string& GetName() const { return _name; }
		//	virtual void Initialize(const rapidjson::Value& inValue) = 0;

		//	void WriteLog() const
		//	{
		//		std::cout << "-------------------------" << std::endl;
		//		std::cout << "Table Name - " << _name << std::endl;
		//		std::cout << "-------------------------" << std::endl;

		//		for (auto& data : _dataMap)
		//		{
		//			data.second.WriteLog();
		//		}
		//	}

		//protected:
		//	std::string	_name;

		//	std::map<int, T> _dataMap;
		//};

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
		AddLine("~TableBase() = default;", tabCount + 1);
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
#pragma endregion // HeaderFileGenerator

#pragma region SourceFileGenerator
	SourceFileGenerator::SourceFileGenerator(const tstring inFileName)
		: CodeGenerator(inFileName)
	{

	}

	SourceFileGenerator::~SourceFileGenerator()
	{

	}

	void SourceFileGenerator::Generate()
	{
		StartStream();
		EndStream();
	}

	void SourceFileGenerator::StartStream()
	{
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


#pragma endregion // SourceFileGenerator
} // namespace GDC
