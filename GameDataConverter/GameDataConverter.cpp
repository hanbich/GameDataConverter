﻿//! @date   2024/02/28
//! @file   GameDataConverter
//! @author chsoo82
//! @brief  Excel 파일를 로드해서 JsonFile 로 변환합니다. 그리고 타 프로젝트에서 생성된 JsonFile을 불러들이기 쉽도록 인터페이스를 생성합니다.


#include <iostream>

#include "GameDataType.h"
#include "DataCoordinator.h"
#include "ExcelFileLoader.h"
#include "JsonFileWriter.h"
#include "ConfigJsonParser.h"
#include "CodeGenerator.h"

using namespace GDC;

int main()
{
    ConfigJsonParser::Get()->LoadFile("config.json");

    DataCoordinator dataCoordinator;
    JsonFileWriter jsonFileWriter;

    ExcelFileLoader::LoadFiles(dataCoordinator);
    jsonFileWriter.WriteFile(dataCoordinator);

    // 코드 생성
    {
        HeaderFileGenerator hfGenerator("GameDataTable_generated.h");
        hfGenerator.Generate(dataCoordinator);
        SourceFileGenerator sfGenerator("GameDataTable_generated.cpp");
        sfGenerator.Generate(dataCoordinator);
    }

    ConfigJsonParser::Delete();

    return 0;
}

