#pragma once
//! @date   2024/03/04
//! @file   DataCoordinator.h
//! @author chsoo82
//! @brief  Excel ���ϵ��� �ε� �� �����͸� �ɽ��մϴ�.
//!   

#ifndef __GDC_DATA_COORDINATOR_H__
#define __GDC_DATA_COORDINATOR_H__

namespace GDC
{
	struct ColumnInfo
	{
		tstring _name;			// ���� ������ �÷� �̸�
		tstring _type;			// ���� ������ �÷� Ÿ��	
		tstring _defaultValue;	// ���� ������ �÷� ����Ʈ ��
	};

	typedef std::vector<ColumnInfo>  ColumnInfoVec;
	typedef std::vector<tstring>	 RowData;
	typedef std::vector<RowData>	 RowDataVec;

	class TableData
	{
	public:
		TableData(const tstring& inName);
		~TableData() = default;

		void SetName(const tstring& inName) { _name = inName; }
		void AddColumnInfo(const tstring& inName, const tstring& inType, const tstring& inDefaultValue);
		void AddColumnInfo(const ColumnInfo& inColumnInfo) { _columnInfoVec.push_back(inColumnInfo); }
		void AddRowData(const RowData& inRowData) { _rowDataVec.push_back(inRowData); }

		ColumnInfoVec& GetColumnInfoVec() { return _columnInfoVec; }
		RowDataVec& GetRowDataVec() { return _rowDataVec; }

		const tstring& GetName() const { return _name; }
		const ColumnInfoVec& GetColumnInfoVec() const { return _columnInfoVec; }
		const RowDataVec& GetRowDataVec() const { return _rowDataVec; }

	private:
		tstring			_name;			// ���� ������ ���̺� �̸�
		ColumnInfoVec	_columnInfoVec; // ���� ������ �÷� ����
		RowDataVec		_rowDataVec;	// ���� ������ ������
	};

	typedef std::shared_ptr<TableData>		TableDataPtr;
	typedef std::map<tstring, TableDataPtr> TableDataPtrMap;

	class DataCoordinator
	{
	public:
		DataCoordinator() = default;
		~DataCoordinator() = default;

		TableDataPtr AddTableData(const tstring& inName);

	private:
		TableDataPtrMap _tableDataPtrMap;	// ���̺� ������ ��
	};
}// namespace GDC

#endif // __GDC_DATA_COORDINATOR_H__



