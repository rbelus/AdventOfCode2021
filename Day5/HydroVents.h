#pragma once

#include <filesystem>

#include <Eigen/Core>

class HydroVentComputer
{
public:
	HydroVentComputer(const std::filesystem::path& path);

	int CountOverlaps();

private:
	Eigen::Matrix<uint16_t, Eigen::Dynamic, Eigen::Dynamic> ventMatrix_;
};
