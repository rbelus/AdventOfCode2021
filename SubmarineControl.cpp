#include "SubmarineControl.h"
#include <fstream>
#include <iostream>
#include <string>
#include <cassert>

SubmarineControl::SubmarineControl(const std::filesystem::path& path) :
	x(0),
	y(0)
{
	std::ifstream file(path.c_str(), std::ifstream::in);
	if (file.good())
	{
		while (file.peek() != EOF)
		{
			std::string curLine;
			std::getline(file, curLine);

			std::stringstream stream(curLine);
			std::string dirStr;
			int force;
			stream >> dirStr >> force;

			DIR dir = StringToDir(dirStr);
			chartCourse_.push_back({ dir, force });
		}
	}
}

void SubmarineControl::Navigate()
{
	for (auto instructions : chartCourse_)
	{
		switch (instructions.first)
		{
		case DIR::UP:
			y -= instructions.second;
			break;
		case DIR::FORWARD:
			x += instructions.second;
			break;
		case DIR::DOWN:
			y += instructions.second;
			break;
		case DIR::UNKNOWN:
			assert(false);
			return;
		}
	}
}