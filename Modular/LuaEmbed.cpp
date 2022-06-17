#include "LuaEmbed.h"

#define LUA_ERROR(errorMsg) throw LuaEmbed::LuaException::LuaException(__LINE__, __FILE__, errorMsg)

bool CheckLua(lua_State* L, int r)
{
	if (r == LUA_OK)
	{
		std::string errMsg = lua_tostring(L, -1);
		LUA_ERROR(errMsg);
		return false;
	}
	return true;
}

int lua_trace(lua_State* L) {
	std::string i = lua_tostring(L, 1);
	i += "\n";
	OutputDebugString(i.c_str());
	return 1;
}

LuaEmbed::LuaEmbed()
{
	lua_vm = luaL_newstate();
	luaL_openlibs(lua_vm);

	lua_register(lua_vm, "print", lua_trace);
}

LuaEmbed::~LuaEmbed()
{
	lua_close(lua_vm);
}

lua_State* LuaEmbed::GetVirtualMachine()
{
	return this->lua_vm;
}

int LuaEmbed::LoadFile(std::string fileName)
{
	//get cwd
	char buffer[MAX_PATH];
	GetModuleFileNameA(NULL, buffer, MAX_PATH);
	std::string::size_type pos = std::string(buffer).find_last_of("\\/");
	std::string cwd = std::string(buffer).substr(0, pos);
	cwd += "\\";

	std::ostringstream oss;
	oss << cwd << "Assets\\Scripts\\" << fileName;

	std::string os = oss.str();

	int s = luaL_loadfile(lua_vm, os.c_str());
	return s;
}

int LuaEmbed::LoadFileAndRun(std::string fileName)
{
	int s = LuaEmbed::LoadFile(fileName);
	if(s == LUA_OK)
	{
		//get cwd
		char buffer[MAX_PATH];
		GetModuleFileNameA(NULL, buffer, MAX_PATH);
		std::string::size_type pos = std::string(buffer).find_last_of("\\/");
		std::string cwd = std::string(buffer).substr(0, pos);
		cwd += "\\";

		std::ostringstream oss;
		oss << cwd << "Assets\\Scripts\\" << fileName;
		
		return luaL_dofile(lua_vm, oss.str().c_str());
	}
	else
	{
		return -1;
	}
	return LUA_OK;
}

int LuaEmbed::RunFile(std::string fileName)
{
	char buffer[MAX_PATH];
	GetModuleFileNameA(NULL, buffer, MAX_PATH);
	std::string::size_type pos = std::string(buffer).find_last_of("\\/");
	std::string cwd = std::string(buffer).substr(0, pos);
	cwd += "\\";

	std::ostringstream oss;
	oss << cwd << "Assets\\Scripts\\" << fileName;

	return luaL_dofile(lua_vm, oss.str().c_str());
}

LuaEmbed* LuaEmbed::GetClass()
{
	return this;
}

static int kpt_lua_Writer(lua_State* /*l*/, const void* p, size_t sz, void* u)
{
	return (fwrite(p, sz, 1, (FILE*)u) != 1) && (sz != 0);
}

int LuaEmbed::CompileFile(std::string fileName)
{
	//cwd
	char buffer[MAX_PATH];
	GetModuleFileNameA(NULL, buffer, MAX_PATH);
	std::string::size_type pos = std::string(buffer).find_last_of("\\/");
	std::string cwd = std::string(buffer).substr(0, pos);

	cwd += "\\";
	int status = 0;
	FILE* outfile;

	std::string outname = fileName;
	outname = outname.substr(0,fileName.find("."));
	outname += ".out";

	std::ostringstream out;
	out << cwd << "Assets\\Scripts\\Compiled\\" << outname;

	fopen_s(&outfile, out.str().c_str(), "wb+");
	if (!outfile) {
		perror("fopen");
		exit(1);
	}

	if (!lua_vm)
	{
		throw "Unhandled open state error";
		exit(-1);
	}

	std::ostringstream oss;
	oss << cwd << "Assets\\Scripts\\" << fileName;
	
	status = luaL_loadfile(lua_vm, oss.str().c_str());
	if (status)
	{
		goto exit;
	}
	status = lua_dump(lua_vm, kpt_lua_Writer, outfile);
	if (status) {
		goto exit;
	}

exit:
	fclose(outfile);
	return status;
}

int LuaEmbed::CompileAndRunBytecode(std::string fileName)
{
	//cwd
	char buffer[MAX_PATH];
	GetModuleFileNameA(NULL, buffer, MAX_PATH);
	std::string::size_type pos = std::string(buffer).find_last_of("\\/");
	std::string cwd = std::string(buffer).substr(0, pos);

	cwd += "\\";

	std::string cut = fileName;
	cut = cut.substr(0, cut.find("."));
	cut += ".lua";

	int status = LuaEmbed::CompileFile(cut);
	if (status == 0)
	{
		int s = LuaEmbed::LoadFileAndRun("Compiled\\"+fileName);
		if (s == 0)
		{
			return 0;
		}
		else {
			std::string errmsg = lua_tostring(lua_vm, -1);
			LUA_ERROR(errmsg);
			return s;
		}
	}
	else {
		return status;
	}
	return 0;
}

LuaEmbed::LuaException::LuaException(int line, const char* file, std::string errMsg) :
	Exception(line, file)
{
	LuaEmbed::LuaException::errMsg = errMsg;
}

const char* LuaEmbed::LuaException::what() const noexcept
{
	std::ostringstream oss;
	oss << GetType() << std::endl
		<< "[Description] " << GetErrorDescription() << std::endl
		<< GetOriginString();
	whatBuffer = oss.str();
	return whatBuffer.c_str();
	
}

const char* LuaEmbed::LuaException::GetType() const noexcept
{
	return "Lua Exception:";
}

std::string LuaEmbed::LuaException::GetErrorDescription() const noexcept
{
	return LuaEmbed::LuaException::errMsg;
}