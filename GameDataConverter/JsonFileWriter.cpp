#include <iostream>
#include <fstream>
#include <string>

#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/prettywriter.h"

#include "JsonFileWriter.h"

using namespace rapidjson;
using namespace std;

namespace GDC
{
    int JsonFileWriter::LoadFile()
    {
        try {
            // JSON ������ �б� ���� ����
            ifstream ifs("example.json");
            if (!ifs.is_open()) {
                throw runtime_error("failed to open the file");
            }

            // ���� ������ ���ڿ��� �б�
            string json((istreambuf_iterator<char>(ifs)), (istreambuf_iterator<char>()));

            // JSON ���ڿ� �Ľ�
            Document doc;
            doc.Parse(json.c_str());

            // JSON ��ü ����
            Value& title = doc["title"];
            title.SetString("New Title");

            Value& email = doc["authors"][0]["email"];
            email.SetString("newemail@example.com");

            // JSON ���ڿ� ����
            StringBuffer buffer;
            PrettyWriter<StringBuffer> writer(buffer);
            doc.Accept(writer);

            // ���Ͽ� JSON ���ڿ� ����
            ofstream ofs("new_example.json");
            ofs << buffer.GetString();

            ofs << endl;

            return 0;
        }
        catch (std::exception& e) {
            // ���� ó��
            std::cerr << "Error: " << e.what() << std::endl;
            return -1;
        }
    }
} // namespace GDC