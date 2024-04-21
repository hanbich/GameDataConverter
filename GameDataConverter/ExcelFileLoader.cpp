#include <filesystem>
#include "OpenXLSX.hpp"

#include "GameDataType.h"
#include "ConfigJsonParser.h"
#include "DataCoordinator.h"   

#include "ExcelFileLoader.h"

using namespace std;
using namespace OpenXLSX;

namespace fs = std::filesystem;

namespace GDC
{
    tstring GetCellValue(const XLCellValue& inValue)
    {
        if (inValue.type() == XLValueType::Empty)
			return tstring();
        else if (inValue.type() == XLValueType::Boolean)
        {
            return inValue.get<bool>() ? tstring("TRUE") : tstring("FALSE");
        }
        else if (inValue.type() == XLValueType::Integer)
        {
            return std::to_string(inValue.get<long long>());
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

#pragma region ExcelFileLoader
    int ExcelFileLoader::LoadFile(const tstring& inFileName, TableDataPtr outTableDataPtr)
    {
        try {
            _LOG_FUNCTION_START;

            string path = ConfigJsonParser::Get()->GetLoadPath();
            path += inFileName;

            XLDocument doc(path);
            if (!doc.isOpen())
            {
				throw runtime_error("failed to open the file");
			}

            auto wks = doc.workbook().worksheet("Sheet1");

            i32 colIndex = 0;
            i32 colCount = 0;

            ColumnInfoVec& columnInfoVec = outTableDataPtr->GetColumnInfoVec();
            RowDataVec& rowDataVec  = outTableDataPtr->GetRowDataVec();
            for (auto& row : wks.rows()) 
            {
                colIndex = -2; // �ε��� ����� ���Ǹ� ���� -2�� �ʱ�ȭ �մϴ�.
                colCount = row.cellCount();
                if (row.rowNumber() == 1) // Type 
                {
                    for (auto& value : std::vector<XLCellValue>(row.values())) 
                    {
                        if (++colIndex < 0) // ù���� �÷��� ���������� ����
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
                        if (++colIndex < 0) // ù���� �÷��� ���������� ����
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
                        if (++colIndex < 0) // ù���� �÷��� ���������� ����
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
            _GDC_ASSERT(e.what());
            return -1;
        }
    }

    int ExcelFileLoader::LoadFiles(DataCoordinator& outDataCoordinator)
    {
        try {
            _LOG_FUNCTION_START;

            string path = ConfigJsonParser::Get()->GetLoadPath();
            fs::path p(path);

            std::cout << "�� ���� ��� : " << fs::current_path() << std::endl;
            std::cout << "��� ��� : " << p.relative_path() << std::endl;
            std::cout << "���� ��� : " << fs::absolute(p) << std::endl;
            std::cout << "�������� ���� ��� : " << fs::canonical(p) << std::endl;

            fs::directory_iterator itr(p);
            while (itr != fs::end(itr)) 
            {
                const fs::directory_entry& entry = *itr;
                const auto& ext = entry.path().extension();

                const tstring filename = entry.path().filename().string();
                const tstring tableName = filename.substr(0, filename.find_last_of("."));

                if (ext.string() != ".xlsx")    // Ȯ���ڰ� xlsx�� �ƴϸ� ����
                {
                    // �α� ��� �ʿ�
                    itr++;
                    continue;
                }

                auto tableDataPtr = outDataCoordinator.AddTableData(tableName);
                if (tableDataPtr == nullptr)
                {
                    throw runtime_error("failed to insert the file");   // �̸� �ߺ� Ȥ�� �޸� �Ҵ� ����
                }

                if (-1 == LoadFile(filename, tableDataPtr))
                {
					throw runtime_error("failed to load the file");
				}
                //std::cout << entry.path() << "---" << filename << "---" << tableName << std::endl;
                itr++;
            }

            _LOG_FUNCTION_END;
            return 0;
        }
        catch (std::exception& e) {
            //std::cerr << "Error: " << e.what() << std::endl;
            _GDC_ASSERT(e.what());
            return -1;
        }

        return 0;
    }
#pragma endregion // ExcelFileLoader
} // namespace GDC