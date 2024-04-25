#include <format>

#include "GameDataType.h" 
#include "Singleton.h"
#include "DataCoordinator.h"
#include "ExcelFileLoader.h"
#include "JsonFileWriter.h"
#include "ConfigJsonParser.h"
#include "CodeGenerator.h"
#include "CommandCoordinator.h"

//#define __FUNCTION_POINTER_SAMPLE__
using namespace std;
using namespace GDC;

namespace GDC
{
#pragma region CommandHandler
	bool CommandHandler::GenerateAll()
	{
		_LOG_FUNCTION_START;

		DataCoordinator dataCoordinator;
		JsonFileWriter jsonFileWriter;

		ExcelFileLoader::LoadFiles(dataCoordinator);
		jsonFileWriter.WriteFile(dataCoordinator);

		// 内靛 积己
		const tstring& srcFileName = ConfigJsonParser::Get()->GetWriteSrcFileName();

		HeaderFileGenerator hfGenerator(srcFileName);
		hfGenerator.Generate(dataCoordinator);

		SourceFileGenerator sfGenerator(srcFileName);
		sfGenerator.Generate(dataCoordinator);

		_LOG_FUNCTION_END;
		return true;
	}

	bool CommandHandler::GenerateDataOnly()
	{
		_LOG_FUNCTION_START;

		DataCoordinator dataCoordinator;
		JsonFileWriter jsonFileWriter;

		ExcelFileLoader::LoadFiles(dataCoordinator);
		jsonFileWriter.WriteFile(dataCoordinator);

		_LOG_FUNCTION_END;

		return true;
	}

	bool CommandHandler::GenerateSrcOnly()
	{
		_LOG_FUNCTION_START;

		DataCoordinator dataCoordinator;
		JsonFileWriter jsonFileWriter;

		// 内靛 积己
		const tstring& srcFileName = ConfigJsonParser::Get()->GetWriteSrcFileName();

		HeaderFileGenerator hfGenerator(srcFileName);
		hfGenerator.Generate(dataCoordinator);

		SourceFileGenerator sfGenerator(srcFileName);
		sfGenerator.Generate(dataCoordinator);

		_LOG_FUNCTION_END;

		return true;
	}
#pragma endregion // CommandHandler


#pragma region CommandCoordinator
	CommandCoordinator::CommandCoordinator()
	{
		Insert("all", CommandHandler::GenerateAll);
		Insert("data", CommandHandler::GenerateDataOnly);
		Insert("src", CommandHandler::GenerateSrcOnly);
	}

	CommandCoordinator::~CommandCoordinator()
	{
		_commandFunctionMap.clear();
	}

	bool CommandCoordinator::InputCommand(const tstring& inCommand)
	{
		_LOG_MESSAGE(format("inCommand - {}", inCommand));
		if (inCommand.empty())
		{
			return SearchAndCall<bool>("all");
		}
		else if (inCommand == "all")
		{
			return SearchAndCall<bool>("all");
		}
		else if (inCommand == "data")
		{
			return SearchAndCall<bool>("data");
		}
		else if (inCommand == "src")
		{
			return SearchAndCall<bool>("src");
		}
		else
		{
			_GDC_ASSERT("Invalid Command");
		}

		return false;
	}
#pragma endregion // DataCoordinator
} // namespace La1

