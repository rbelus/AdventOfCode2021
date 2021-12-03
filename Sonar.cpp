#include "Sonar.h"
#include "Tools.h"

#include <fstream>
#include <iostream>
#include <string>
#include <cassert>

Sonar::Sonar(const std::filesystem::path& path)
{
	auto measureDepth = [&](std::stringstream& stream)
	{
		long depth;
		stream >> depth;

		depthMeasurements_.push_back(depth);
	};

	ParseLinesInFile(path, measureDepth);
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
