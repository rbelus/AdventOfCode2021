#pragma once

#include <array>
#include <filesystem>
#include <cassert>

class Bingo
{
	// One single 5x5 bingo board containing integers
	struct BingoBoard
	{
		BingoBoard() { matrix_.fill({ 0, false }); }

		bool HasWon();

		uint16_t& at(uint16_t x, uint16_t y) { assert(x < 5 && y < 5); return matrix_.at(x + 5 * y).first; }
		void markNumber(uint16_t nb) { auto it = std::find(matrix_.begin(), matrix_.end(), nb); if (it != matrix_.end()) it->second = true; }

		// Proper matrix logic is in fact a array of 5*5 elements, stored in a x + y*5 fashion.
		std::array<std::pair<uint16_t, bool>, 25> matrix_;
	};

public:
	Bingo(const std::filesystem::path& path);

	uint32_t Play();

private:
	std::vector<BingoBoard> bingoBoards_;
	std::vector<uint16_t> bingoNumbers_;
};
