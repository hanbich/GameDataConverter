#pragma once
//! @date   2024/02/28
//! @file   ExcelFileLoader.h
//! @author chsoo82
//! @brief  Excel ������ �ε� �� �����͸� �ɽ���.
//!         OpenXLSX ���̺귯�� ���(https://github.com/troldal/OpenXLSX)

#ifndef __GDC_EXCEL_FILE_LOADER_H__
#define __GDC_EXCEL_FILE_LOADER_H__

namespace GDC
{
    class ExcelFileLoader
    {
    public:
        ExcelFileLoader() = default;
        ~ExcelFileLoader() = default;

        static int LoadFile();
        static int LoadFileAll();
    };
} // namespace GDC

#endif // __GDC_EXCEL_FILE_LOADER_H__

