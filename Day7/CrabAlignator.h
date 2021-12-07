#pragma once

#include <filesystem>

class CrabAlignator
{
public:
	CrabAlignator(const std::filesystem::path& path);

	uint64_t FindLowestFuel(bool part1);

private:
	std::vector<uint16_t> crabPos_;
};