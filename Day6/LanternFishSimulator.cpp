#include "LanternFishSimulator.h"
#include "LanternFishSimulator.h"
#include "LanternFishSimulator.h"

#include <functional>
#include <fstream>
#include <iostream>
#include <string>
#include <array>
#include <algorithm>
#include <numeric>

LanternFishSimulator::LanternFishSimulator(const std::filesystem::path& path)
{
	std::ifstream file(path.c_str(), std::ifstream::in);
	if (file.good())
	{
		std::string curLine;
		std::getline(file, curLine);
		std::string lanternFish;
		std::stringstream ss(curLine);
		while (std::getline(ss, lanternFish, ','))
		{
			lanternFishes_.push_back(std::stoi(lanternFish));
		}
	}
}

uint64_t LanternFishSimulator::Simulate(int nbDays)
{
	std::array<uint64_t, 9> nbFishes_;
	nbFishes_.fill(0);

	// Fill with the original fishes
	for (auto fish : lanternFishes_)
	{
		nbFishes_[fish]++;
	}

	// Simulate
	for (int day = 0; day < nbDays; ++day)
	{
		// Treat new fishes
		auto nbSpawningFishes = nbFishes_[0];
		std::rotate(nbFishes_.begin(), nbFishes_.begin() + 1, nbFishes_.end());
		nbFishes_[6] += nbSpawningFishes;
	}

 	return std::accumulate(nbFishes_.begin(), nbFishes_.end(), (uint64_t)0);
}
