#pragma once

#ifndef NDEBUG
#define IS_DEBUG true
#else
#define IS_DEBUG false
#endif



class Macros
{
public:
	static std::string GetDirectory()
	{
		char buffer[MAX_PATH];
		GetModuleFileName(NULL, buffer, MAX_PATH);
		std::string::size_type pos = std::string(buffer).find_last_of("\\/");
		std::string exeDirectory = std::string(buffer).substr(0, pos) + "\\";
		return exeDirectory;
	}
};

#define cwd Macros::GetDirectory()