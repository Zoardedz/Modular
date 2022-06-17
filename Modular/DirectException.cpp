#include "DirectException.h"
#include <sstream>


DirectException::DirectException(int line, const char* file) noexcept
	:
	line(line),
	file(file)
{}

const char* DirectException::what() const noexcept
{
	std::ostringstream oss;
	oss << GetType() << std::endl
		<< GetOriginString();
	whatBuffer = oss.str();
	return whatBuffer.c_str();
}

const char* DirectException::GetType() const noexcept
{
	return "DirectException";
}

int DirectException::GetLine() const noexcept
{
	return line;
}

const std::string& DirectException::GetFile() const noexcept
{
	return file;
}

std::string DirectException::GetOriginString() const noexcept
{
	std::ostringstream oss;
	oss << "[File] " << file << std::endl
		<< "[Line] " << line;
	return oss.str();
}