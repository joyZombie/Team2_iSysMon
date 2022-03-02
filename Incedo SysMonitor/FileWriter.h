#include "SystemInformation.h"
#include <string>

#pragma once

class FileWriter
{
private:
public:
	FileWriter() = delete;
	static std::string putInFile(SystemInformation si);
	static void deleteFile(std::string FileName);
};