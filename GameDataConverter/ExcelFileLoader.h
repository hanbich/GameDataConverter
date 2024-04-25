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
    class TableData;
    class DataCoordinator;
    class ExcelFileLoader
    {
    public:
        ExcelFileLoader() = default;
        ~ExcelFileLoader() = default;

        ExcelFileLoader(ExcelFileLoader const&) = delete;	// ���� ������ ����
        void operator=(ExcelFileLoader const&) = delete;	// ���� ������ ����

        static int LoadFile(const tstring& inFileName, TableDataPtr outTableDataPtr);
        static int LoadFiles(DataCoordinator& outDataCoordinator);
    };
} // namespace GDC

#endif // __GDC_EXCEL_FILE_LOADER_H__

