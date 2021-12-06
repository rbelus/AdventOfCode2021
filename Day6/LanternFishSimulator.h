#pragma once

#include <filesystem>

class LanternFishSimulator
{
public:
	LanternFishSimulator(const std::filesystem::path& path);

	// naive
	uint64_t Simulate(int nbDays);

private:
	std::vector<uint16_t> lanternFishes_;
	uint64_t nbTotalFish_;
};