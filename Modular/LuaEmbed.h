#pragma once
#include "Win.h"
#include <string>
#include "DirectException.h"
#include <sstream>
#include <lua.hpp>
#include <luajit.h>

class LuaEmbed
{
public:
	class Exception : public DirectException
	{
		using DirectException::DirectException;
	};
	class LuaException : public Exception
	{
	public:
		LuaException(int line, const char* file, std::string errMsg);
		const char* what() const noexcept override;
		const char* GetType() const noexcept override;
		std::string GetErrorDescription() const noexcept;
	private:
		std::string errMsg;
	};
public:
	LuaEmbed();
	~LuaEmbed();
	lua_State* GetVirtualMachine();
	int LoadFile(std::string fileName);
	int LoadFileAndRun(std::string fileName);
	int CompileFile(std::string fileName);
	int CompileAndRunBytecode(std::string fileName);
	int RunFile(std::string fileName);
	LuaEmbed* GetClass();
private:
	lua_State* lua_vm;
};