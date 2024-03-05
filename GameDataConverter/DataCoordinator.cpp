#include "Type.h"

#include "DataCoordinator.h"

using namespace std;

namespace GDC
{
	TableData::TableData()
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

} // namespace GDC
