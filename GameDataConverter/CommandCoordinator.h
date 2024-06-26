#pragma once
//! @date   2024/02/28
//! @file   CommandCoordination.h
//! @author chsoo82
//! @brief  
//!         

#ifndef __GDC_COMMAND_COORDINATOR_H__
#define __GDC_COMMAND_COORDINATOR_H__

namespace GDC
{
	class CommandHandler
	{
	public:
		static bool GenerateAll();
		static bool GenerateDataOnly();
		static bool GenerateSrcOnly();
	};

	class CommandCoordinator
	{
		// every function pointer will be stored as this type
		typedef void (*voidFunctionType)(void);
		typedef std::map<tstring, std::pair<voidFunctionType, std::type_index>> CommandFunctionMap;

	public:
		CommandCoordinator();
		~CommandCoordinator();

		CommandCoordinator(CommandCoordinator const&) = delete;	// 복사 생성자 삭제
		void operator=(CommandCoordinator const&) = delete;	// 대입 연산자 삭제

		bool InputCommand(const tstring& inCommand);

	private:
		template<typename T>
		void Insert(const tstring& inCommandStr, T inFunctionT)
		{
			const auto functionType = std::type_index(typeid(inFunctionT));
			const auto findIter = _commandFunctionMap.find(inCommandStr);
			if (findIter == std::end(_commandFunctionMap))
			{
				_commandFunctionMap.insert(std::make_pair(inCommandStr, std::make_pair((voidFunctionType)inFunctionT, functionType)));
			}
		}

		template<typename T, typename... Args>
		T SearchAndCall(const std::string& inCommandStr, Args&&... args)
		{
			auto findIter = _commandFunctionMap.find(inCommandStr);
			if (findIter == std::end(_commandFunctionMap))
			{
				return T();
			}

			auto functionPair = findIter->second;

			auto typeCastedFunction = (T(*)(Args ...))(functionPair.first);

			if (functionPair.second != std::type_index(typeid(typeCastedFunction)))
			{
				return T();
			}

			return typeCastedFunction(std::forward<Args>(args)...);
		}

	private:
		CommandFunctionMap _commandFunctionMap;
	};
} // namespace GDC

#endif // __GDC_COMMAND_COORDINATOR_H__
