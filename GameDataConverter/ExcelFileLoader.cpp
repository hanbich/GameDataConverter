#include "OpenXLSX.hpp"

#include "ExcelFileLoader.h"

using namespace OpenXLSX;

namespace GDC
{
    int ExcelFileLoader::LoadFile()
    {
        XLDocument doc;
        doc.create("Spreadsheet.xlsx");
        auto wks = doc.workbook().worksheet("Sheet1");

        wks.cell("A1").value() = "Hello, OpenXLSX!";

        doc.save();

        return 0;
    }
} // namespace GDC