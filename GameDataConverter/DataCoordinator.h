#pragma once
//! @date   2024/03/04
//! @file   DataCoordinator.h
//! @author chsoo82
//! @brief  
//!   

#ifndef __GDC_DATA_COORDINATOR_H__
#define __GDC_DATA_COORDINATOR_H__

namespace GDC
{
	struct ColumnInfo
	{
		tstring _name;			// 엑셀 파일의 컬럼 이름
		tstring _type;			// 엑셀 파일의 컬럼 타입	
		tstring _defaultValue;	// 엑셀 파일의 컬럼 디폴트 값
	};

	typedef std::vector<ColumnInfo>  ColumnInfoVec;
	typedef std::vector<tstring>	 RowData;
	typedef std::vector<RowData>	 RowDataVec;

	class TableData
	{
	public:
		TableData();
		~TableData() = default;

		void SetName(const tstring& inName) { _name = inName; }
		void AddColumnInfo(const tstring& inName, const tstring& inType, const tstring& inDefaultValue);
		void AddColumnInfo(const ColumnInfo& inColumnInfo) { _columnInfoVec.push_back(inColumnInfo); }
		void AddRowData(const RowData& inRowData) { _rowDataVec.push_back(inRowData); }

		RowDataVec& GetRowDataVec() { return _rowDataVec; }

		const tstring& GetName() const { return _name; }
		const ColumnInfoVec& GetColumnInfoVec() const { return _columnInfoVec; }
		const RowDataVec& GetRowDataVec() const { return _rowDataVec; }

	private:
		tstring			_name;			// 엑셀 파일의 테이블 이름
		ColumnInfoVec	_columnInfoVec; // 엑셀 파일의 컬럼 정보
		RowDataVec		_rowDataVec;	// 엑셀 파일의 데이터
	};

	class DataCoordinator
	{
	public:
		DataCoordinator() {}
		~DataCoordinator() {}

	};
}// namespace GDC

#endif // __GDC_DATA_COORDINATOR_H__



