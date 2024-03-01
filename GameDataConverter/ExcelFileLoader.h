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
    class ExcelFileLoader
    {
    public:
        ExcelFileLoader() {}
        ~ExcelFileLoader() {}

        int LoadFile();
    };
} // namespace GDC

#endif // __GDC_EXCEL_FILE_LOADER_H__

