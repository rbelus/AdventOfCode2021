#include "SmokeFlow.h"
#include <filesystem>
#include <functional>

#include <fstream>
#include <iostream>
#include <string>
#include <cassert>
#include <Tools/Tools.h>

SmokeFlow::SmokeFlow(const std::filesystem::path& path)
{
	{
		int width = 0, height = 0;
		std::ifstream file(path.c_str(), std::ifstream::in);
		if (file.good())
		{
			std::string dummy;
			std::getline(file, dummy);
			width = (int)dummy.length();
		}
		height = CountLinesInFile(path);
		heightMap_.resize(width, height);
	}

	std::ifstream file(path.c_str(), std::ifstream::in);
	if (file.good())
	{
		int j = 0;
		while (file.peek() != EOF)
		{
			std::string curLine;
			std::getline(file, curLine);
			for(int i = 0; i < (int)curLine.length(); ++i)
			{
				heightMap_(i, j) = { (uint16_t)(curLine.at(i) - 48), 0, false};
			}
			j++;
		}
	}
}

void SmokeFlow::FindLowPoints()
{
	for (int y = 0; y < heightMap_.cols(); y++)
	{
		for (int x = 0; x < heightMap_.rows(); x++)
		{
			// Check Neighbours
			bool lowPoint = true;
			if (x != 0)
				lowPoint &= heightMap_(x - 1, y).depth > heightMap_(x, y).depth;
			if (y != 0)
				lowPoint &= heightMap_(x, y - 1).depth > heightMap_(x, y).depth;
			if (x != heightMap_.rows() - 1)
				lowPoint &= heightMap_(x + 1, y).depth > heightMap_(x, y).depth;
			if( y != heightMap_.cols() - 1)
				lowPoint &= heightMap_(x, y + 1).depth > heightMap_(x, y).depth;

			heightMap_(x, y).lowPoint = lowPoint;
		}
	}
}

uint64_t SmokeFlow::ComputeRiskLevel()
{
	uint64_t totalRiskLevel = 0;

	for (int y = 0; y < heightMap_.cols(); y++)
	{
		for (int x = 0; x < heightMap_.rows(); x++)
		{
			if (heightMap_(x, y).lowPoint)
			{
				heightMap_(x, y).riskLevel = 1 + heightMap_(x, y).depth;
				totalRiskLevel += heightMap_(x, y).riskLevel;
			}
		}
	}

	return totalRiskLevel;
}
