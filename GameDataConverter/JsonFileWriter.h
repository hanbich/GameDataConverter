#pragma once
//! @date   2024/02/28
//! @file   JsonFileWriter.h
//! @author chsoo82
//! @brief  Excel ���Ͽ��� �ε�� �����͵��� JsonFile �� ��ȯ
//!         rapidjson ���̺귯�� ���(https://github.com/Tencent/rapidjson)

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



