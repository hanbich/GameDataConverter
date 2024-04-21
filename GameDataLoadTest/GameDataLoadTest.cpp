//! @date   2024/04/21
//! @file   GameDataLoadTest
//! @author chsoo82
//! @brief  생성된 Json 파일을 읽어서 데이터 테이블을 로드하는 테스트 프로젝트

#include <fstream>

#include "GameDataType.h"
#include "ConfigJsonParser.h"
#include "GameDataTable_generated.h"

using namespace rapidjson;
using namespace std;

int main()
{
    try {

        ConfigJsonParser::Get()->LoadFile("config.json");

        {
            // JSON 파일을 읽기 모드로 열기
            const string&& fullPath = ConfigJsonParser::Get()->GetWriteDataFullPath();
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

        ConfigJsonParser::Delete();
	}
    catch (const exception& e) {
        _GDC_ASSERT(e.what());
		return -1;
	}

    return 0;
}