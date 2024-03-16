#pragma once
//! @date   2024/02/28
//! @file   JsonFileWriter.h
//! @author chsoo82
//! @brief  Excel 파일에서 로드된 데이터들을 JsonFile 로 변환
//!         rapidjson 라이브러리 사용(https://github.com/Tencent/rapidjson)

#ifndef __GDC_JSON_FILE_WRITER_H__
#define __GDC_JSON_FILE_WRITER_H__

namespace GDC
{
    class DataCoordinator;
    class JsonFileWriter
    {
    public:
        JsonFileWriter() {}
        ~JsonFileWriter() {}

        int LoadFile();
        int WriteFile(DataCoordinator& refDataCoordinator);
    };
} // namespace GDC

#endif // __GDC_JSON_FILE_WRITER_H__



