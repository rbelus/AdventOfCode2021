#include <filesystem>
#include <functional>

#include <fstream>
#include <iostream>
#include <string>
#include <cassert>

void ParseLinesInFile(const std::filesystem::path& path, const std::function<void(std::stringstream&)>& fnc)
{
	std::ifstream file(path.c_str(), std::ifstream::in);
	if (file.good())
	{
		while (file.peek() != EOF)
		{
			std::string curLine;
			std::getline(file, curLine);

			std::stringstream stream(curLine);
			fnc(stream);
		}
	}
}
