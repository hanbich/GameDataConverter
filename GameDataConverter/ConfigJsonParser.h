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
		const std::string& GetWritePath() const { return _writePath; }

	private:
		std::string _loadPath;
		std::string _writePath;
	};

} // namespace GDC

#endif // __GDC_CONFIG_JSON_PARSER_H__


