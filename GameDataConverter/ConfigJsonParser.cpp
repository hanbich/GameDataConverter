#include <iostream>
#include <fstream>

#include "GameDataType.h" 

#include "ConfigJsonParser.h"

using namespace std;
using namespace rapidjson;

namespace GDC
{
#pragma region ConfigJsonParser
	ConfigJsonParser::ConfigJsonParser()
	{
	}

	int ConfigJsonParser::LoadFile(string inPath)
	{
        try {
            _LOG_FUNCTION_START;

            // JSON ������ �б� ���� ����
            ifstream ifs("config.json");
            if (!ifs.is_open()) {
                throw runtime_error("failed to open the file");
            }
            // ���� ������ ���ڿ��� �б�
            string json((istreambuf_iterator<char>(ifs)), (istreambuf_iterator<char>()));

            // JSON ���ڿ� �Ľ�
            Document doc;
            doc.Parse(json.c_str());

            // JSON ��ü �б�
            _loadPath = doc["LoadPath"].GetString();
            _writeDataPath = doc["WriteDataPath"].GetString();
            _writeDataFileName = doc["WriteDataFileName"].GetString();
            _writeSrcPath = doc["WriteSrcPath"].GetString();
            _writeSrcFileName = doc["WriteSrcFileName"].GetString();

            _LOG_FUNCTION_END;
            return 0;
        }
        catch (std::exception& e) {
            //std::cerr << "Error: " << e.what() << std::endl;
            _GDC_ASSERT(e.what());
            return -1;
        }
	}
#pragma endregion // ConfigJsonParser
} // namespace GDC
