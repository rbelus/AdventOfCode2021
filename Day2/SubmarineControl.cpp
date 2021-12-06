#include "SubmarineControl.h"
#include <Tools/Tools.h>

#include <fstream>
#include <iostream>
#include <string>
#include <cassert>

SubmarineControl::SubmarineControl(const std::filesystem::path& path) :
	x(0),
	y(0),
	aim(0)
{
	auto computeCourse = [&](std::stringstream& stream)
	{
		std::string dirStr;
		int force;
		stream >> dirStr >> force;

		DIR dir = StringToDir(dirStr);
		chartCourse_.push_back({ dir, force });
	};

	ParseLinesInFile(path, computeCourse);
}

void SubmarineControl::Navigate()
{
	for (auto instructions : chartCourse_)
	{
		switch (instructions.first)
		{
		case DIR::UP:
			aim -= instructions.second;
			break;
		case DIR::FORWARD:
			x += instructions.second;
			y += aim * instructions.second;
			break;
		case DIR::DOWN:
			aim += instructions.second;
			break;
		case DIR::UNKNOWN:
			assert(false);
			return;
		}
	}
}