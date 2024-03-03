#include <iostream>
#include <fstream>
#include <string>

#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/prettywriter.h"

#include "Type.h"
#include "ConfigJsonParser.h"

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

    int JsonFileWriter::WriteFile()
    {
        try {

            // 1. Parse a JSON string into DOM.
            const char* json = "{\"project\":\"rapidjson\",\"stars\":10}";
            Document d;
            d.Parse(json);

            // 2. Modify it by DOM.
            Value& s = d["stars"];
            s.SetInt(s.GetInt() + 1);

            // 3. Stringify the DOM
            StringBuffer buffer;
            Writer<StringBuffer> writer(buffer);
            d.Accept(writer);

            // ���Ͽ� JSON ���ڿ� ����
            string path = ConfigJsonParser::Get()->GetWritePath();
            path += "new_example.json";

            ofstream ofs(path);
            ofs << buffer.GetString();

            ofs << endl;

            // Output {"project":"rapidjson","stars":11}
            std::cout << buffer.GetString() << std::endl;

            return 0;
        }
        catch (std::exception& e) {
            // ���� ó��
            std::cerr << "Error: " << e.what() << std::endl;
            return -1;
        }
    }
} // namespace GDC