//! @date   2024/04/16
//! @file   CodeGenerator.h
//! @author chsoo82
//! @brief  Ÿ ������Ʈ���� json ������ ���� �ε��ϱ� ���� �������̽��� ���� �ҽ��ڵ� ����

#pragma once

#ifndef __GDC_CODE_GENERATOR_H__
#define __GDC_CODE_GENERATOR_H__

namespace GDC
{
	// �ڵ� ������ Base Ŭ����
    class CodeGenerator
    {
	public:
		typedef std::shared_ptr<std::ofstream> OfstreamPtr;

    public:
		CodeGenerator(const tstring& inFileName);
		virtual ~CodeGenerator();

		CodeGenerator(CodeGenerator const&) = delete;	// ���� ������ ����
		void operator=(CodeGenerator const&) = delete;	// ���� ������ ����

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

	// .h ���� ����
	class HeaderFileGenerator : public CodeGenerator
	{
	public:
		HeaderFileGenerator(const tstring& inFileName);
		virtual ~HeaderFileGenerator();

		HeaderFileGenerator(HeaderFileGenerator const&) = delete;	// ���� ������ ����
		void operator=(HeaderFileGenerator const&) = delete;	// ���� ������ ����

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
		tstring _defFileName;	// ������ ���ǿ� ���ϸ�
	};

	// .cpp ���� ����
	class SourceFileGenerator : public CodeGenerator
	{
	public:
		SourceFileGenerator(const tstring& inFileName);
		virtual ~SourceFileGenerator();

		SourceFileGenerator(SourceFileGenerator const&) = delete;	// ���� ������ ����
		void operator=(SourceFileGenerator const&) = delete;	// ���� ������ ����

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
			tstring _headerFileName;	// ��� ���ϸ�
	};

} // namespace GDC

#endif // __GDC_CODE_GENERATOR_H__