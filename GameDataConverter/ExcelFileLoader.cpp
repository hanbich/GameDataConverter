#include "OpenXLSX.hpp"

#include "Type.h"
#include "ConfigJsonParser.h"

#include "ExcelFileLoader.h"

using namespace std;
using namespace OpenXLSX;

namespace GDC
{
    int ExcelFileLoader::LoadFile()
    {
        string path = ConfigJsonParser::Get()->GetLoadPath();
        path += "Spreadsheet.xlsx";

        XLDocument doc;
        doc.create(path);
        auto wks = doc.workbook().worksheet("Sheet1");

        wks.cell("A1").value() = "Hello, OpenXLSX!";

        doc.save();

        return 0;
    }
} // namespace GDC