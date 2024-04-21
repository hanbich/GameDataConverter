// GameDataLoadTest.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//
#include <fstream>

#include "GameDataType.h"

#include "GameDataTable_generated.h"

using namespace rapidjson;
using namespace std;

int main()
{
    // JSON 파일을 읽기 모드로 열기
    ifstream ifs("D:\\Work\\GameDataConverter\\OutGameDataFiles\\new_example.json");
    if (!ifs.is_open()) {
        throw runtime_error("failed to open the file");
    }

    // 파일 내용을 문자열로 읽기
    string json((istreambuf_iterator<char>(ifs)), (istreambuf_iterator<char>()));

    // JSON 문자열 파싱
    Document doc;
    doc.Parse(json.c_str());

    {
        BaseType_Table baseTypeTable;
        baseTypeTable.Initialize(doc["BaseType"]);
        baseTypeTable.WriteLog();

        BaseType_temp_Table baseTypeTempTable;
        baseTypeTempTable.Initialize(doc["BaseType_temp"]);
        baseTypeTempTable.WriteLog();
    }

    return 0;
}