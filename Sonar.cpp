#include "Sonar.h"
#include <fstream>
#include <iostream>
#include <string>
#include <cassert>

Sonar::Sonar(const std::filesystem::path& path)
{
	std::ifstream file(path.c_str(), std::ifstream::in);
	if (file.good())
	{
		while (file.peek() != EOF)
		{
			std::string curLine;
			std::getline(file, curLine);
			depthMeasurements_.push_back(std::stoul(curLine));
		}
	}
}

size_t Sonar::GetDepthIncreases(const std::vector<size_t>& depthList) const
{
	size_t increased = 0;
	assert(depthList.size() > 2);
	for (size_t i = 1; i < depthList.size(); ++i)
		if (depthList[i] > depthList[i - 1])
			++increased;
	return increased;
}

size_t Sonar::GetSlidingDepthIncreases(const std::vector<size_t>& depthList) const
{
	// First create an intermediary list made of the sum of 3 consecutive measures.
	std::vector<size_t> sumMeasurements;
	assert(depthList.size() > 3);
	for (size_t i = 2; i < depthList.size(); ++i)
	{
		sumMeasurements.push_back(depthList[i - 2] + depthList[i - 1] + depthList[i]);
	}

	return GetDepthIncreases(sumMeasurements);
}
