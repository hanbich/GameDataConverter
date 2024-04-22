//! @date   2024/04/21
//! @file   GameDataLoadTest
//! @author chsoo82
//! @brief  생성된 Json 파일을 읽어서 데이터 테이블을 로드하는 테스트 프로젝트

#include <fstream>
#include <iostream>
#include <string>
#include <map>

#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/filereadstream.h"

#include "GameDataTable_generated.h"

using namespace rapidjson;
using namespace std;
using namespace GDC;

int main()
{
    try {
        const string fullPath = "D:\\Work\\GameDataConverter\\OutGameDataFiles\\GameData.json";
        ifstream ifs(fullPath);
        if (!ifs.is_open()) {
            throw runtime_error("failed to open the file");
        }

        // 파일 내용을 문자열로 읽기
        string json((istreambuf_iterator<char>(ifs)), (istreambuf_iterator<char>()));

        // JSON 문자열 파싱
        Document doc;
        doc.Parse(json.c_str());

        {
            // 데이터 테이블 로드 및 출력
            BaseType_Table baseTypeTable;
            baseTypeTable.Initialize(doc["BaseType"]);
            baseTypeTable.WriteLog();

            BaseType_temp_Table baseTypeTempTable;
            baseTypeTempTable.Initialize(doc["BaseType_temp"]);
            baseTypeTempTable.WriteLog();
        }
	}
    catch (const exception& e) {
        cout << "Assert - Message : " << e.what() << "\n";
        assert(false);
		return -1;
	}

    return 0;
}
