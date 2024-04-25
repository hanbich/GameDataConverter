#pragma once
//! @date   2024/02/28
//! @file   ExcelFileLoader.h
//! @author chsoo82
//! @brief  Excel 파일을 로딩 후 데이터를 케싱함.
//!         OpenXLSX 라이브러리 사용(https://github.com/troldal/OpenXLSX)

#ifndef __GDC_EXCEL_FILE_LOADER_H__
#define __GDC_EXCEL_FILE_LOADER_H__

namespace GDC
{
    class TableData;
    class DataCoordinator;
    class ExcelFileLoader
    {
    public:
        ExcelFileLoader() = default;
        ~ExcelFileLoader() = default;

        ExcelFileLoader(ExcelFileLoader const&) = delete;	// 복사 생성자 삭제
        void operator=(ExcelFileLoader const&) = delete;	// 대입 연산자 삭제

        static int LoadFile(const tstring& inFileName, TableDataPtr outTableDataPtr);
        static int LoadFiles(DataCoordinator& outDataCoordinator);
    };
} // namespace GDC

#endif // __GDC_EXCEL_FILE_LOADER_H__

