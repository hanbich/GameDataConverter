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

            // DOM 객체 생성.
            Document doc;
            Document::AllocatorType& alloc = doc.GetAllocator();
            doc.SetObject();

            // DOM 객체 편집 (데이터 기록).
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

            // Json 파일 생성 및 데이터 저장.
            StringBuffer buffer;
            Writer<StringBuffer> writer(buffer);
            doc.Accept(writer);

            // 파일에 JSON 문자열 쓰기
            const string&& fullPath = ConfigJsonParser::Get()->GetWriteDataFullPath();

            ofstream ofs(fullPath);
            ofs << buffer.GetString();

            ofs << endl;

            _LOG_FUNCTION_END;
            return 0;
        }
        catch (std::exception& e) {
            // 예외 처리
            std::cerr << "Error: " << e.what() << std::endl;
            return -1;
        }
    }
} // namespace GDC