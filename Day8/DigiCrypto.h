#pragma once

#include <filesystem>
#include <bitset>
#include <array>

class DigiCrypto
{
	struct SegmentDisplay
	{
		SegmentDisplay(std::string in);
		SegmentDisplay() { segments.reset(); }

		bool IsOne() const { return segments.count() == 2; }
		bool IsFour() const { return segments.count() == 4; }
		bool IsSeven() const { return segments.count() == 3; }
		bool IsEight() const { return segments.count() == 7; }
		bool IsEasyDigit() { return IsOne() || IsFour() || IsSeven() || IsEight(); }

		std::bitset<7> segments;

		bool operator== (SegmentDisplay b) { return segments == b.segments; }

		int knownNumber = -1;
	};

public:
	DigiCrypto(const std::filesystem::path& path);

	uint64_t CountEasyDigitsInOutput();

	uint64_t Decrypt();

private:
	// This is the "key". Each entry corresponds to the correct position of given segment  by index as per the following :
	/*
	----0----
	|		|
	1		2
	|		|
	----3----
	|		|
	4		5
	|		|
	----6----
	
	Thus, if key_[2] = 'c' this means 'c' is in fact the segment 2 in the diagram above
	*/
	std::array<char, 7> key_;

	std::vector<std::array<SegmentDisplay, 10>> inputs_;
	std::vector<std::array<SegmentDisplay, 4>> outputs_;
};