#include <iostream>
#include <fstream>
#include <string>

#include "rapidjson/prettywriter.h"

#include "GameDataType.h"
#include "ConfigJsonParser.h"
#include "DataCoordinator.h"

#include "JsonFileWriter.h"

using namespace rapidjson;
using namespace std;

namespace GDC
{
    int JsonFileWriter::LoadFile()
    {
        try {
            // JSON 파일을 읽기 모드로 열기
            ifstream ifs("example.json");
            if (!ifs.is_open()) {
                throw runtime_error("failed to open the file");
            }

            // 파일 내용을 문자열로 읽기
            string json((istreambuf_iterator<char>(ifs)), (istreambuf_iterator<char>()));

            // JSON 문자열 파싱
            Document doc;
            doc.Parse(json.c_str());

            // JSON 객체 편집
            Value& title = doc["title"];
            title.SetString("New Title");

            Value& email = doc["authors"][0]["email"];
            email.SetString("newemail@example.com");

            // JSON 문자열 생성
            StringBuffer buffer;
            PrettyWriter<StringBuffer> writer(buffer);
            doc.Accept(writer);

            // 파일에 JSON 문자열 쓰기
            ofstream ofs("new_example.json");
            ofs << buffer.GetString();

            ofs << endl;

            return 0;
        }
        catch (std::exception& e) {
            // 예외 처리
            std::cerr << "Error: " << e.what() << std::endl;
            return -1;
        }
    }

    //int JsonFileWriter::WriteFile(DataCoordinator& refDataCoordinator)
    //{
    //    try {

    //        // 1. Parse a JSON string into DOM.
    //        const char* json = "{\"project\":\"rapidjson\",\"stars\":10}";
    //        Document d;
    //        d.Parse(json);

    //        // 2. Modify it by DOM.
    //        Value& s = d["stars"];
    //        s.SetInt(s.GetInt() + 1);

    //        // 3. Stringify the DOM
    //        StringBuffer buffer;
    //        Writer<StringBuffer> writer(buffer);
    //        d.Accept(writer);

    //        // 파일에 JSON 문자열 쓰기
    //        string path = ConfigJsonParser::Get()->GetWritePath();
    //        path += "new_example.json";

    //        ofstream ofs(path);
    //        ofs << buffer.GetString();

    //        ofs << endl;

    //        // Output {"project":"rapidjson","stars":11}
    //        std::cout << buffer.GetString() << std::endl;

    //        return 0;
    //    }
    //    catch (std::exception& e) {
    //        // 예외 처리
    //        std::cerr << "Error: " << e.what() << std::endl;
    //        return -1;
    //    }
    //}

    int JsonFileWriter::WriteFile(DataCoordinator& refDataCoordinator)
    {
        try {

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
            string path = ConfigJsonParser::Get()->GetWritePath();
            path += "new_example.json";

            ofstream ofs(path);
            ofs << buffer.GetString();

            ofs << endl;

            // Output {"project":"rapidjson","stars":11}
            //std::cout << buffer.GetString() << std::endl;

            return 0;
        }
        catch (std::exception& e) {
            // 예외 처리
            std::cerr << "Error: " << e.what() << std::endl;
            return -1;
        }
    }
} // namespace GDC