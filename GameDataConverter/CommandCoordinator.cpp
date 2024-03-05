#include "Type.h" 
#include "CommandCoordinator.h"

//#define __FUNCTION_POINTER_SAMPLE__
namespace GDC
{
#ifdef __FUNCTION_POINTER_SAMPLE__
	void fun1(void) {
		std::cout << "inside fun1\n";
	}

	int fun2() {
		std::cout << "inside fun2\n";
		return 2;
	}

	int fun3(int a) {
		std::cout << "inside fun3\n";
		return a;
	}

	std::vector<int> fun4() {
		std::cout << "inside fun4\n";
		std::vector<int> v(4, 100);
		return v;
	}
#endif // __FUNCTION_POINTER_SAMPLE__

#pragma region CommandHandler
	bool CommandHandler::LoadFile()
	{
		_LOG_FUNCTION_START;

		_LOG_FUNCTION_END;
		return true;
	}

	bool CommandHandler::OutPutFileProbabilityData()
	{
		_LOG_FUNCTION_START;

		_LOG_FUNCTION_END;

		return true;
	}

	bool CommandHandler::PrintProbabilityData()
	{
		_LOG_FUNCTION_START;

		_LOG_FUNCTION_END;

		return true;
	}

	bool CommandHandler::GenerateLottoNombers()
	{
		_LOG_FUNCTION_START;

		_LOG_FUNCTION_END;

		return true;
	}

	bool CommandHandler::ClearData()
	{
		_LOG_FUNCTION_START;

		_LOG_FUNCTION_END;

		return true;
	}
#pragma endregion // CommandHandler


#pragma region CommandCoordinator
	CommandCoordinator::CommandCoordinator()
	{
#ifdef __FUNCTION_POINTER_SAMPLE__
		{
			Insert("fun1", fun1);
			Insert("fun2", fun2);
			Insert("fun3", fun3);
			Insert("fun4", fun4);
		}
#endif // __FUNCTION_POINTER_SAMPLE__

		Insert("load", CommandHandler::LoadFile);
		Insert("output", CommandHandler::OutPutFileProbabilityData);
		Insert("print", CommandHandler::PrintProbabilityData);
		Insert("generate", CommandHandler::GenerateLottoNombers);
		Insert("clear", CommandHandler::ClearData);
	}

	CommandCoordinator::~CommandCoordinator()
	{
		_commandFunctionMap.clear();
	}

	bool CommandCoordinator::InputCommand()
	{
#ifdef __FUNCTION_POINTER_SAMPLE__
		{
			SearchAndCall<void>("fun1");
			int retVal = SearchAndCall<int>("fun3", 2);
			SearchAndCall<int>("fun2");
			auto temp = SearchAndCall<std::vector<int>>("fun4");
		}
#endif // __FUNCTION_POINTER_SAMPLE__

		bool retVal1 = SearchAndCall<bool>("load");
		bool retVal2 = SearchAndCall<bool>("output");
		bool retVal3 = SearchAndCall<bool>("print");
		bool retVal4 = SearchAndCall<bool>("generate");
		bool retVal5 = SearchAndCall<bool>("clear");

		return true;
	}
#pragma endregion // DataCoordinator
} // namespace La1

