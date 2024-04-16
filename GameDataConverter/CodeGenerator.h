//! @date   2024/04/16
//! @file   CodeGenerator.h
//! @author chsoo82
//! @brief  Ÿ ������Ʈ���� json ������ ���� �Ľ��ϱ� ���� �������̽��� ���� �ҽ��ڵ� ����

#pragma once

#ifndef __GDC_CODE_GENERATOR_H__
#define __GDC_CODE_GENERATOR_H__

namespace GDC
{
    class CodeGenerator
    {
	public:
		typedef std::shared_ptr<std::ofstream> OfstreamPtr;

    public:
		CodeGenerator(const tstring& inFileName);
		virtual ~CodeGenerator();

		virtual void Generate() = 0;

		OfstreamPtr		GetOfstreamPtr() const { return _ofStreamPtr; }
		std::ofstream&	GetOfstream() const { return *_ofStreamPtr; }

		tstring GetFileName() const { return _fileName; }

	protected:
		void AddTeb(int inTabCount);
		void AddLineBase(const tstring& inLine);
		void AddLine(const tstring& inLine, int inTabCount = 0);

	private:
		const tstring _fileName;
		std::shared_ptr<std::ofstream> _ofStreamPtr = nullptr;
	};

	class HeaderFileGenerator : public CodeGenerator
	{
	public:
		HeaderFileGenerator(const tstring inFileName);
		virtual ~HeaderFileGenerator();

		virtual void Generate() override;

	private:
		void StartStream();
		void EndStream();
		void BaseClassStream();

	private:
		tstring _defFileName;	// ������ ���ǿ� ���ϸ�
	};

	class SourceFileGenerator : public CodeGenerator
	{
	public:
		SourceFileGenerator(const tstring inFileName);
		virtual ~SourceFileGenerator();

		virtual void Generate() override;

	private:
		void StartStream();
		void EndStream();
	};

} // namespace GDC

#endif // __GDC_CODE_GENERATOR_H__