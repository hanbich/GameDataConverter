#pragma once
//! @date   2024/02/28
//! @file   JsonFileWriter.h
//! @author chsoo82
//! @brief  
//!         rapidjson 라이브러리 사용(https://github.com/Tencent/rapidjson)

#ifndef __GDC_CONFIG_JSON_PARSER_H__
#define __GDC_CONFIG_JSON_PARSER_H__

namespace GDC
{
	class ConfigJsonParser : public Singleton<ConfigJsonParser>
	{
		friend class Singleton;

	public:
		ConfigJsonParser();
		~ConfigJsonParser(){}

		int LoadFile(std::string inPath);

		const std::string& GetLoadPath() const { return _loadPath; }
		const std::string& GetWriteDataPath() const { return _writeDataPath; }
		const std::string& GetWriteDataFileName() const { return _writeDataFileName; }
		const std::string  GetWriteDataFullPath() const { return (_writeDataPath + _writeDataFileName); }
		const std::string& GetWriteSrcPath() const { return _writeSrcPath; }
		const std::string& GetWriteSrcFileName() const { return _writeSrcFileName; }

	private:
		std::string _loadPath;
		std::string _writeDataPath;
		std::string _writeDataFileName;
		std::string _writeSrcPath;
		std::string _writeSrcFileName;
	};

} // namespace GDC

#endif // __GDC_CONFIG_JSON_PARSER_H__


