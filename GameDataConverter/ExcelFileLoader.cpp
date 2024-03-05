#include <filesystem>
#include "OpenXLSX.hpp"

#include "Type.h"
#include "ConfigJsonParser.h"
#include "DataCoordinator.h"   

#include "ExcelFileLoader.h"

using namespace std;
using namespace OpenXLSX;

namespace GDC
{
    tstring GetCellValue(const XLCellValue& inValue)
    {
        if (inValue.type() == XLValueType::Empty)
			return tstring();
        else if (inValue.type() == XLValueType::Boolean)
        {
            return inValue.get<bool>() ? tstring("true") : tstring("false");
        }
        else if (inValue.type() == XLValueType::Integer)
        {
            return std::to_string(inValue.get<int>());
        }
        else if (inValue.type() == XLValueType::Float)
        {
            return std::to_string(inValue.get<float>());
        }
        if (inValue.type() == XLValueType::String)
        {
            return inValue.get<std::string>();
        }
        else
        {
            return tstring();
        }
    }

    int ExcelFileLoader::LoadFile()
    {
        try {
            _LOG_FUNCTION_START;

            string path = ConfigJsonParser::Get()->GetLoadPath();
            path += "BaseType.xlsx";

            XLDocument doc(path);
            if (!doc.isOpen())
            {
				throw runtime_error("failed to open the file");
			}

            auto wks = doc.workbook().worksheet("Sheet1");

            i32 colIndex = 0;
            i32 colCount = 0;

            ColumnInfoVec   columnInfoVec;
            RowDataVec      rowDataVec;
            for (auto& row : wks.rows()) 
            {
                colIndex = -2;
                colCount = row.cellCount();
                if (row.rowNumber() == 1) // Type 
                {
                    for (auto& value : std::vector<XLCellValue>(row.values())) 
                    {
                        if (++colIndex < 0) // 첫번때 컬럼은 설명임으로 생략
                            continue;

                       columnInfoVec.push_back(ColumnInfo());
                       auto& refInfo = columnInfoVec.back();
                       refInfo._type = move(GetCellValue(value));
                    }
				}
                else if (row.rowNumber() == 2 || row.rowNumber() == 3) // default value, name
                {
                    for (auto& value : std::vector<XLCellValue>(row.values()))
                    {
                        if (++colIndex < 0) // 첫번때 컬럼은 설명임으로 생략
                            continue;

                        auto& refInfo = columnInfoVec[colIndex];
                        if (row.rowNumber() == 2)
                            refInfo._defaultValue = move(GetCellValue(value));
                        else if (row.rowNumber() == 3)
                            refInfo._name = move(GetCellValue(value));
                    }
                }
                else
                {
                    rowDataVec.push_back(RowData());
					auto& refRowData = rowDataVec.back();
                    refRowData.assign(colCount - 1, tstring());
                    for (auto& value : std::vector<XLCellValue>(row.values()))
                    {
                        if (++colIndex < 0) // 첫번때 컬럼은 설명임으로 생략
                            continue;

                        refRowData[colIndex] = move(GetCellValue(value));
                    }
				}
			}   

            _LOG_FUNCTION_END;
            return 0;
        }
        catch (std::exception& e) {
            //std::cerr << "Error: " << e.what() << std::endl;
            _LA1_ASSERT(e.what());
            return -1;
        }
    }

    int ExcelFileLoader::LoadFileAll()
    {
        return 0;
    }
} // namespace GDC