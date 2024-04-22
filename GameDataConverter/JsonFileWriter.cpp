#include <iostream>
#include <fstream>
#include <string>

#include "rapidjson/prettywriter.h"

#include "GameDataType.h"
#include "Singleton.h"
#include "ConfigJsonParser.h"
#include "DataCoordinator.h"

#include "JsonFileWriter.h"

using namespace std;
using namespace GDC;
using namespace rapidjson;

namespace GDC
{
    int JsonFileWriter::WriteFile(DataCoordinator& refDataCoordinator)
    {
        try {
            _LOG_FUNCTION_START;

            // DOM ��ü ����.
            Document doc;
            Document::AllocatorType& alloc = doc.GetAllocator();
            doc.SetObject();

            // DOM ��ü ���� (������ ���).
            for (const auto& tableDataPair : refDataCoordinator.GetTableDataPtrMap())
            {
                // table 
                Value tableValue(kArrayType);             
                for (const auto& lowData : tableDataPair.second->GetRowDataVec())
                {
                    // low
					Value lowValue(kArrayType);
                    for (const auto& cellData : lowData)
                    {
                        // cell
                        Value cellValue(cellData.c_str(), cellData.size(), alloc);
                        lowValue.PushBack(cellValue, alloc);
					}
    				tableValue.PushBack(lowValue, alloc);
				}
                Value tableName(tableDataPair.first.c_str(), tableDataPair.first.size(), alloc);
                doc.AddMember(tableName, tableValue, alloc);
            }

            // Json ���� ���� �� ������ ����.
            StringBuffer buffer;
            Writer<StringBuffer> writer(buffer);
            doc.Accept(writer);

            // ���Ͽ� JSON ���ڿ� ����
            const string&& fullPath = ConfigJsonParser::Get()->GetWriteDataFullPath();

            ofstream ofs(fullPath);
            ofs << buffer.GetString();

            ofs << endl;

            _LOG_FUNCTION_END;
            return 0;
        }
        catch (std::exception& e) {
            // ���� ó��
            std::cerr << "Error: " << e.what() << std::endl;
            return -1;
        }
    }
} // namespace GDC