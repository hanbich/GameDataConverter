//! @date   2024/02/28
//! @file   GameDataConverter
//! @author chsoo82
//! @brief  Excel 파일를 로드해서 JsonFile 로 변환합니다. 그리고 타 프로젝트에서 생성된 JsonFile을 불러들이기 쉽도록 인터페이스를 생성합니다.


#include <iostream>

#include "GameDataType.h"
#include "Singleton.h"
#include "ConfigJsonParser.h"
#include "CommandCoordinator.h"

using namespace GDC;

int main(int argv, char* argc[])
{
    _LOG_FUNCTION_START;
    ConfigJsonParser::Get()->LoadFile("config.json");

    CommandCoordinator commandCoordinator;
    if (argv > 1)
    {
		commandCoordinator.InputCommand(argc[1]);
	}
    else
    {
        commandCoordinator.InputCommand("all");
    }

    ConfigJsonParser::Delete();

    _LOG_FUNCTION_END;
    return 0;
}

