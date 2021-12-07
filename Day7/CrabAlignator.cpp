#include "CrabAlignator.h"
#include "CrabAlignator.h"

#include <Tools/Tools.h>
#include <algorithm>
#include <numeric>
#include <Eigen/Core>

CrabAlignator::CrabAlignator(const std::filesystem::path& path)
{
	auto crabLoader = [&](const std::string& str) {
		std::string crabToken;
		std::stringstream ss(str);

		while (std::getline(ss, crabToken, ','))
		{
			crabPos_.push_back(std::stoi(crabToken));
		}
	};

	ParseLinesInFile(path, crabLoader);
}

uint64_t CrabAlignator::FindLowestFuel(bool part1)
{
	// naive quick solution
	auto bounds = std::minmax_element(crabPos_.begin(), crabPos_.end());
	std::vector<uint64_t> totalFuelCost;
	if (part1)
	{
		for (int i = *bounds.first; i <= *bounds.second; ++i)
		{
			uint64_t fuelCost = 0;
			for (auto crab : crabPos_)
			{
				fuelCost += abs(crab - i);
			}
			totalFuelCost.push_back(fuelCost);
		}
	}
	else
	{
		for (uint16_t i = *bounds.first; i <= *bounds.second; ++i)
		{
			uint64_t fuelCost = 0;
			for (auto crab : crabPos_)
			{
				std::vector<uint64_t> seq(abs(crab - i));
				std::iota(seq.begin(), seq.end(), 1);
				fuelCost += std::accumulate(seq.begin(), seq.end(), (uint64_t)0);
			}
			totalFuelCost.push_back(fuelCost);
		}
	}

	return *std::min_element(totalFuelCost.begin(), totalFuelCost.end());
}


