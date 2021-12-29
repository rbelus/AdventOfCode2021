#include "DigiCrypto.h"
#include <Tools/Tools.h>


#include <functional>
#include <fstream>
#include <iostream>
#include <string>
#include <array>
#include <algorithm>
#include <numeric>
#include <cassert>
#include <regex>



DigiCrypto::SegmentDisplay::SegmentDisplay(std::string in)
{
	segments.reset();

	for (auto c : in)
	{
		segments[c - 97] = true;
	}
}


DigiCrypto::DigiCrypto(const std::filesystem::path& path)
{
	auto cryptoLoader = [&](const std::string& str) {
		std::regex digiRegex("(.*) \\| (.*)");
		std::smatch match;

		assert(std::regex_match(str, match, digiRegex));

		std::string input = match[1];
		std::string output = match[2];

		{
			std::stringstream ssInput(input);
			std::string digit;
			std::array<SegmentDisplay, 10> inputArray;
			for (size_t i = 0; i < inputArray.size(); ++i)
			{
				ssInput >> digit;
				inputArray[i] = digit;
			}

			inputs_.push_back(inputArray);
		}
		{
			std::stringstream ssOutput(output);
			std::string digit;
			std::array<SegmentDisplay, 4> outputArray;
			for (size_t i = 0; i < outputArray.size(); ++i)
			{
				ssOutput >> digit;
				outputArray[i] = digit;
			}

			outputs_.push_back(outputArray);
		}
	};

	ParseLinesInFile(path, cryptoLoader);
}

uint64_t DigiCrypto::CountEasyDigitsInOutput()
{
	uint64_t counter = 0;
	for (auto outputLine : outputs_)
		counter += std::count_if(outputLine.begin(), outputLine.end(), [](auto segment) { return segment.IsEasyDigit(); });

	return counter;
}

uint64_t DigiCrypto::Decrypt()
{
	uint64_t sum = 0;
	for (size_t i = 0; i < inputs_.size(); ++i)
	{
		std::array<SegmentDisplay, 10> decryptedNumbers;

		// First find known numbers
		decryptedNumbers[1] = *std::find_if(inputs_[i].begin(), inputs_[i].end(), [](auto& seg) {
			if (seg.IsOne())
			{
				seg.knownNumber = 1;
				return true;
			}
			return false;
			});
		decryptedNumbers[1].knownNumber = 1;
		decryptedNumbers[4] = *std::find_if(inputs_[i].begin(), inputs_[i].end(), [](auto& seg) {
			if (seg.IsFour())
			{
				seg.knownNumber = 4;
				return true;
			}
			return false;			
			});
		decryptedNumbers[4].knownNumber = 4;
		decryptedNumbers[7] = *std::find_if(inputs_[i].begin(), inputs_[i].end(), [](auto& seg) {
			if (seg.IsSeven())
			{
				seg.knownNumber = 7;
				return true;
			}
			return false;			
			});
		decryptedNumbers[7].knownNumber = 7;
		decryptedNumbers[8] = *std::find_if(inputs_[i].begin(), inputs_[i].end(), [](auto& seg) {
			if (seg.IsEight())
			{
				seg.knownNumber = 8;
				return true;
			}
			return false;			
			});
		decryptedNumbers[8].knownNumber = 8;


		// Next up find 9
		// It is the only not known number containing four
		for (auto& seg : inputs_[i])
		{
			if (seg.knownNumber < 0 && (seg.segments | decryptedNumbers[4].segments) == seg.segments)
			{
				seg.knownNumber = 9;
				decryptedNumbers[9] = seg;
			}
		}

		// Now find 6
		// It is the 6 segment number not containing one.
		for (auto& seg : inputs_[i])
		{
			if (seg.knownNumber < 0 && seg.segments.count() == 6 && (seg.segments | decryptedNumbers[1].segments) != seg.segments)
			{
				seg.knownNumber = 6;
				decryptedNumbers[6] = seg;
			}
		}

		// Now find 0
		// The last 6 segment number
		for (auto& seg : inputs_[i])
		{
			if (seg.knownNumber < 0 && seg.segments.count() == 6)
			{
				seg.knownNumber = 0;
				decryptedNumbers[0] = seg;
			}
		}

		// Now find 5
		// The 5 segment number contained in 6
		for (auto& seg : inputs_[i])
		{
			if (seg.knownNumber < 0 && seg.segments.count() == 5 && (seg.segments | decryptedNumbers[6].segments) == decryptedNumbers[6].segments)
			{
				seg.knownNumber = 5;
				decryptedNumbers[5] = seg;
			}
		}

		// Now find 3
		// The 5 segment number contained in 9
		for (auto& seg : inputs_[i])
		{
			if (seg.knownNumber < 0 && seg.segments.count() == 5 && (seg.segments | decryptedNumbers[9].segments) == decryptedNumbers[9].segments)
			{
				seg.knownNumber = 3;
				decryptedNumbers[3] = seg;
			}
		}

		// Finally find 2
		// The kast 5 segment number
		for (auto& seg : inputs_[i])
		{
			if (seg.knownNumber < 0 && seg.segments.count() == 5)
			{
				seg.knownNumber = 2;
				decryptedNumbers[2] = seg;
			}
		}


		// Last thing is to decrypt output !
		int currentPow = 3;
		for (auto outputSeg : outputs_[i])
		{
			// Find current value
			sum += (uint64_t) std::powl(10, currentPow) * std::find(decryptedNumbers.begin(), decryptedNumbers.end(), outputSeg)->knownNumber;
			currentPow--;
		}
	}

	return sum;
}

