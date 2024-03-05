#include <iostream>
#include <fstream>

#include "Type.h" 

#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/filereadstream.h"

#include "ConfigJsonParser.h"

using namespace std;
using namespace rapidjson;

namespace GDC
{
	ConfigJsonParser::ConfigJsonParser()
	{
	}

	int ConfigJsonParser::LoadFile(string inPath)
	{
        try {
            _LOG_FUNCTION_START;

            // JSON 파일을 읽기 모드로 열기
            ifstream ifs("config.json");
            if (!ifs.is_open()) {
                throw runtime_error("failed to open the file");
            }
            // 파일 내용을 문자열로 읽기
            string json((istreambuf_iterator<char>(ifs)), (istreambuf_iterator<char>()));

            // JSON 문자열 파싱
            Document doc;
            doc.Parse(json.c_str());

            // JSON 객체 읽기
            Value& loadPath = doc["LoadPath"];
            _loadPath = loadPath.GetString();

            Value& writePath = doc["WritePath"];
            _writePath = writePath.GetString();

            _LOG_FUNCTION_END;
            return 0;
        }
        catch (std::exception& e) {
            //std::cerr << "Error: " << e.what() << std::endl;
            _LA1_ASSERT(e.what());
            return -1;
        }
	}
} // namespace GDC
