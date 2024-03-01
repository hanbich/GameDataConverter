//! @date   2024/02/28
//! @file   GameDataConverter
//! @author chsoo82
//! @brief  Excel 파일를 로드해서 JsonFile 로 변환합니다. 그리고 타 프로젝트에서 생성된 JsonFile을 불러들이기 쉽도록 인터페이스를 생성합니다.


#include <iostream>

#include "ExcelFileLoader.h"
#include "JsonFileWriter.h"

int main()
{

    GDC::ExcelFileLoader excelFileLoader;
    GDC::JsonFileWriter jsonFileWriter;

    excelFileLoader.LoadFile();
    jsonFileWriter.LoadFile();

    return 0;
}

