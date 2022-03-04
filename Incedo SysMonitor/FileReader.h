#include <string>

#pragma once

class FileReader
{
private:
public:
	FileReader() = delete;
	static std::string  getFile(std::string FileName, bool containPath = false);
	static void sendRemainingData();
	static std::string DIR;
};
