#pragma once
#include <Tools/Tools.h>

#include <filesystem>
#include <bitset>
#include <iostream>

template<int BitSize>
class BitDiagnostic
{
public:
	BitDiagnostic<BitSize>(const std::filesystem::path& path)
	{
		auto bitFill = [&](std::string& line)
		{
			std::stringstream stream(line);
			std::string bitLine;
			stream >> bitLine;

			bitPrompt_.push_back(std::bitset<BitSize>(bitLine));
		};

		ParseLinesInFile(path, bitFill);
	}

	void ComputeGammaEpsilonRate(uint32_t& gamma, uint32_t& epsilon);
	void ComputeOxygenCO2Levels(uint32_t& oxygen, uint32_t& co2);

private:
	std::vector<std::bitset<BitSize>> bitPrompt_;
};
