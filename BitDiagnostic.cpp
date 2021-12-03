#include "BitDiagnostic.h"

#include <array>

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

// Explicit instantiation
template class BitDiagnostic<12>;