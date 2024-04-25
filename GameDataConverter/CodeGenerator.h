//! @date   2024/04/16
//! @file   CodeGenerator.h
//! @author chsoo82
//! @brief  타 프로젝트에서 json 파일을 쉽게 로드하기 위한 인터페이스에 대한 소스코드 생성

#pragma once

#ifndef __GDC_CODE_GENERATOR_H__
#define __GDC_CODE_GENERATOR_H__

namespace GDC
{
	// 코드 생성기 Base 클래스
    class CodeGenerator
    {
	public:
		typedef std::shared_ptr<std::ofstream> OfstreamPtr;

    public:
		CodeGenerator(const tstring& inFileName);
		virtual ~CodeGenerator();

		CodeGenerator(CodeGenerator const&) = delete;	// 복사 생성자 삭제
		void operator=(CodeGenerator const&) = delete;	// 대입 연산자 삭제

		virtual void Generate(const DataCoordinator& inDataCoordinator) = 0;

		tstring GetFileName() const { return _fileName; }

	protected:
		OfstreamPtr		GetOfstreamPtr() const { return _ofStreamPtr; }
		std::ofstream&	GetOfstream() const { return *_ofStreamPtr; }

		void AddTeb(int inTabCount);
		void AddLineBase(const tstring& inLine);
		void AddLine(const tstring& inLine, int inTabCount = 0);

	protected:
		tstring GetRowClassName(const tstring& inTableName) const;
		tstring GetTableClassName(const tstring& inTableName) const;
		tstring GetMemberValueName(const ColumnInfo& inColumnInfo) const;
		tstring GetValueType(const ColumnInfo& inColumnInfo) const;

	private:
		const tstring _fileName;

		std::shared_ptr<std::ofstream> _ofStreamPtr = nullptr;
	};

	// .h 파일 생성
	class HeaderFileGenerator : public CodeGenerator
	{
	public:
		HeaderFileGenerator(const tstring& inFileName);
		virtual ~HeaderFileGenerator();

		HeaderFileGenerator(HeaderFileGenerator const&) = delete;	// 복사 생성자 삭제
		void operator=(HeaderFileGenerator const&) = delete;	// 대입 연산자 삭제

		virtual void Generate(const DataCoordinator& inDataCoordinator) override;

	private:
		void StartStream();
		void EndStream();
		void BaseClassStream();

		tstring GetDefaultValue(const ColumnInfo& inColumnInfo) const;

		void RawClassMemberStream(const ColumnInfo& inColumnInfo, const i32 inTabCount);
		void RawClassStream(const tstring& inTableName, const TableDataPtr inTableDataPtr);
		void TableClassStream(const tstring& inTableName, const TableDataPtr inTableDataPtr);

	private:
		tstring _defFileName;	// 디파인 정의용 파일명
	};

	// .cpp 파일 생성
	class SourceFileGenerator : public CodeGenerator
	{
	public:
		SourceFileGenerator(const tstring& inFileName);
		virtual ~SourceFileGenerator();

		SourceFileGenerator(SourceFileGenerator const&) = delete;	// 복사 생성자 삭제
		void operator=(SourceFileGenerator const&) = delete;	// 대입 연산자 삭제

		virtual void Generate(const DataCoordinator& inDataCoordinator) override;

	private:
		void StartStream();
		void EndStream();

		void RawClassMemberInitialize(const i32 inIndex, const ColumnInfo& inColumnInfo, const i32 inTabCount);
		void RawClassMemberWriteLog(const ColumnInfo& inColumnInfo, const i32 inTabCount);

		void RawClassInitializeFuncStream(const tstring inRowClassName, const TableDataPtr inTableDataPtr, const i32 inTabCount);
		void RawClassWriteLogFuncStream(const tstring inRowClassName, const TableDataPtr inTableDataPtr, const i32 inTabCount);

		void TableClassInitializeFuncStream(const tstring inRowClassName, const tstring inTableName, const TableDataPtr inTableDataPtr, const i32 inTabCount);

		void RawClassStream(const tstring& inTableName, const TableDataPtr inTableDataPtr);
		void TableClassStream(const tstring& inTableName, const TableDataPtr inTableDataPtr);

	private:
			tstring _headerFileName;	// 헤더 파일명
	};

} // namespace GDC

#endif // __GDC_CODE_GENERATOR_H__