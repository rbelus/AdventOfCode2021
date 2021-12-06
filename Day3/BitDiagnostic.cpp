#include "BitDiagnostic.h"

#include <array>
#include <cassert>

template<int BitSize>
void BitDiagnostic<BitSize>::ComputeGammaEpsilonRate(uint32_t& gamma, uint32_t& epsilon)
{
	std::array<uint16_t, BitSize> nbOccurences({ 0 });

	// Count bits...
	for (const auto& bitSet : bitPrompt_)
	{
		for (uint16_t i = 0; i < BitSize; ++i)
		{
			nbOccurences[i] += (uint16_t) bitSet.test(i);
		}
	}

	// Fill final bits
	std::bitset<BitSize> gammaBit, epsilonBit;
	for (uint16_t i = 0; i < BitSize; ++i)
	{
		gammaBit[i] = nbOccurences[i] > (bitPrompt_.size() / 2);
	}

	gamma = gammaBit.to_ulong();
	epsilonBit = gammaBit.flip();
	epsilon = epsilonBit.to_ulong();
}

template<int BitSize>
void BitDiagnostic<BitSize>::ComputeOxygenCO2Levels(uint32_t& oxygen, uint32_t& co2)
{
	auto bitPromptCopy = bitPrompt_;

	// Oxygen (most element in current column with 1 priority)
	int curColumn = BitSize - 1;
	while (bitPromptCopy.size() > 1 && curColumn >= 0)
	{
		// Parse all bits, and separate the '1' from the '0' in the current column.
		std::vector<std::bitset<BitSize>> oneBits;
		for (auto currentBit = bitPromptCopy.begin(); currentBit < bitPromptCopy.end();)
		{
			if (currentBit->test(curColumn))
			{
				oneBits.push_back(*currentBit);
				currentBit = bitPromptCopy.erase(currentBit);
			}
			else
			{
				currentBit++;
			}
		}

		// Remove the smallest container or the zeros if they are equal sized.
		if (oneBits.size() >= bitPromptCopy.size())
		{
			bitPromptCopy.clear();
			bitPromptCopy = std::move(oneBits);
		}

		curColumn--;
	}

	assert(bitPromptCopy.size() == 1);

	oxygen = bitPromptCopy[0].to_ulong();


	// Carbon Dioxide (fewest element in cur column with 0 priority)
	bitPromptCopy = bitPrompt_;
	curColumn = BitSize - 1;
	while (bitPromptCopy.size() > 1 && curColumn >= 0)
	{
		// Parse all bits, and separate the '1' from the '0' in the current column.
		std::vector<std::bitset<BitSize>> zeroBits;
		for (auto currentBit = bitPromptCopy.begin(); currentBit < bitPromptCopy.end();)
		{
			if (!currentBit->test(curColumn))
			{
				zeroBits.push_back(*currentBit);
				currentBit = bitPromptCopy.erase(currentBit);
			}
			else
			{
				currentBit++;
			}
		}

		// Remove the smallest container or the zeros if they are equal sized.
		if (zeroBits.size() <= bitPromptCopy.size())
		{
			bitPromptCopy.clear();
			bitPromptCopy = std::move(zeroBits);
		}

		curColumn--;
	}

	assert(bitPromptCopy.size() == 1);

	co2 = bitPromptCopy[0].to_ulong();
}

// Explicit instantiation
template class BitDiagnostic<12>;
template class BitDiagnostic<5>;