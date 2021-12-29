#pragma once

#include <filesystem>
#include <bitset>
#include <array>

#include <Eigen/Core>

class SmokeFlow
{
	struct Pixel
	{
		uint16_t depth = 0;
		uint16_t riskLevel = 0;
		bool lowPoint = false;
	};
public:
	SmokeFlow(const std::filesystem::path& path);
	void FindLowPoints();
	uint64_t ComputeRiskLevel();

private:
	Eigen::Matrix<Pixel, Eigen::Dynamic, Eigen::Dynamic> heightMap_;
};