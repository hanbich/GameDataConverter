#include "GameDataType.h"

#include "DataCoordinator.h"

using namespace std;
using namespace GDC;

namespace GDC
{
#pragma region TableData
	TableData::TableData(const tstring& inName)
		: _name(inName)
	{
	}

	void TableData::AddColumnInfo(const tstring& inName, const tstring& inType, const tstring& inDefaultValue)
	{
		ColumnInfo columnInfo;
		columnInfo._name = inName;
		columnInfo._type = inType;
		columnInfo._defaultValue = inDefaultValue;

		_columnInfoVec.push_back(columnInfo);
	}
#pragma endregion // TableData

#pragma region DataCoordinator
	TableDataPtr DataCoordinator::AddTableData(const tstring& inName)
	{
		auto retPair = _tableDataPtrMap.insert(make_pair(inName, make_shared<TableData>(inName)));
		if (retPair.second == false)
			return nullptr;

		return retPair.first->second;
	}
#pragma endregion // DataCoordinator


} // namespace GDC
