# GameDataConverter

## 1. 기능 정의
- 정의된 형식의 EXCEL 파일들을 분석 후 데이터 사용에 필요한 인터페이스 코드와 데이터 파일을 분리해서 생성합니다.
- C++ 에서 다수의 데이터 파일을 로딩해 사용해야 할 경우, 데이터 파일을 로딩하기 위한 개별 코드를 작성해야 합니다. 그리고 데이터 파일의 수가 많아질수록 추가 작업이 많아짐니다.
- 하지만 GameDataConverter 를 사용하면, 필요 코드를 자동으로 생성함에 따라 데이터 관리가 단순해지며, 데이터들을 하나의 파일로 구성할 수 있어, 데이터 관리의 효율성을 높일 수 있습니다.

>```mermaid
>flowchart LR
>    A[EXECEL_FILES]
>    B[GameDataConverter]
>    C[GameDataTable_generated.h]
>    D[GameDataTable_generated.cpp]
>    E[GameData.json]
>    A-->|분석|B
>    B-->|.h 생성|C
>    B-->|.cpp 생성|D
>    B-->|DataFile 생성|E
>```


## 2. 사용 방법
### A. 설정 파일 생성 (config.json)
```json
{
    "LoadPath": "D:\\Work\\GameDataConverter\\GameDataFiles\\",
    "WriteDataPath": "D:\\Work\\GameDataConverter\\OutGameDataFiles\\",
    "WriteDataFileName": "GameData.json",
    "WriteSrcPath": "D:\\Work\\GameDataConverter\\GameDataLoadTest\\",
    "WriteSrcFileName": "GameDataTable_generated"
}
```
- LoadPath : 데이터 및 코드를 생성할 EXCEL 파일들 위치
- WriteDataPath : 데이터 파일 생성 경로
- WriteDataFileName : 데이터 파일 이름 (확장자 포함)
- WriteSrcPath : 소스 파일 생성 경로
- WriteSrcFileName : 소스파일 명칭 (확장제 제외)

### B. EXCEL 파일 생성 규칙
- 설정 파일에 등록된 경로에 데이터 EXCEL 파일들 생성해야 합니다.
- 데이터 파일은 영문과 숫자로 생성되어야하며, 중복 사용이 불가능 합니다.
- Type : 컬럼에 사용할 변수의 타입 정의
- DefaultValue : 컬럼의 기본값 정의
    - 지원 타입 : bool, char, uchar, short, ushort, int, uint, int64, uint64, long, ulong, longlong, ulonglong, string, float, double
- Name : 컬럼의 변수명 정의 ('영문', '숫자', '_' 만 사용 가능)
  - ID 컬럼은 필수 사항이며, 값이 중복 되어서는 않됨니다. (기본 키 값으로 사용)
- Data : 실제 데이터들

#### ※ BaseType.xlsx 의 일부분 예시
<img align="left" src="./BaseType_xlsx.png"> </img>
.

### C. 실행 파일 실행
- 실행 파일과 동일한 위치에 설정 파일 생성(config.json)
- 아래와 같이 실행 파일을 실행합니다.
  - 데이터와 소스 파일 모두 생성 : "GameDataConverter.exe" or "GameDataConverter.exe all"
  - 데이터 만 생성 : "GameDataConverter.exe data"
  - 소스 파일 만 생성 : "GameDataConverter.exe src"

### D. 생성된 파일 사용법
  1. 프로젝트에 rapidjson 추가
  2. 프로젝트에 GameDataType.h, GameDataUtil.h/.cpp 추가
  3. 프로젝트에 GameDataTable_generated.h/.cpp 추가
  4. 샘플 코드
``` cpp
#include <fstream>

#include "GameDataType.h"
#include "GameDataTable_generated.h"

using namespace rapidjson;
using namespace std;
```
``` cpp
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

    // 데이터 테이블 로드 및 출력
    BaseType_Table baseTypeTable;
    baseTypeTable.Initialize(doc["BaseType"]);
    baseTypeTable.WriteLog();

    BaseType_temp_Table baseTypeTempTable;
    baseTypeTempTable.Initialize(doc["BaseType_temp"]);
    baseTypeTempTable.WriteLog();
}
catch (const exception& e) {
    _GDC_ASSERT(e.what());
    return -1;
}
```

## 3. 프로젝트 구성
- GameDataConverter - GDC 기본 프로젝트
    - ConfigJsonParser.h/.cpp : 설정 데이터 관리
    - CommandCoordinator.h/.cpp : 실행 옵션 관리
    - ExcelFileLoader.h/.cpp : EXECEL_FILES 을 읽어들여, DataCoordinator에 데이터 분리
    - DataCoordinator.h/.cpp : EXECEL_FILES의 데이터 파일들의 정보를 테이블 형태와 데이터로 분리해 테이블 정보 생성 후 관리    
    - CodeGenerator.h/.cpp : DataCoordinator에 정리된 테이블의 형테 정보를 이용해 코드 생성(.h, .cpp)
    - JsonFileWriter.h/.cpp : DataCoordinator에 정리된 데이터 부분을 .json 파일로 저장

- GameDataLoadTest - GDC 테스트 프로젝트
    - GameDataTable_generated.h/.cpp   : 데이터 테이블 템플릿 (자동 생성)
    - GameDataUtil.h/.cpp : 데이터 파일 로딩에 필요한 도구

- GameDataFiles - 데이터 파일 위치 (EXECEL_FILES)
    - BaseType.xlsx
    - BaseType_temp.xlsx
     
- OutGameDataFiles - 생성된 결과물 위치
    - GameData.json : 생성된 Data 파일
  
- Vender - 사용한 외부 라이브러리
    - OpenXLSX 
      - xlsx 파일 로드에 사용
      - https://github.com/troldal/OpenXLSX
    - rapidjson 
      -  json 파일 로드 및 생성에 사용
      -  https://github.com/Tencent/rapidjson

## 4.Copyright and Licensing

You can copy and paste the license summary from below.

```
Tencent is pleased to support the open source community by making RapidJSON available.

Copyright (C) 2015 THL A29 Limited, a Tencent company, and Milo Yip.

Licensed under the MIT License (the "License"); you may not use this file except
in compliance with the License. You may obtain a copy of the License at

http://opensource.org/licenses/MIT

Unless required by applicable law or agreed to in writing, software distributed 
under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR 
CONDITIONS OF ANY KIND, either express or implied. See the License for the 
specific language governing permissions and limitations under the License.