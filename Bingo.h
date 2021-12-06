#pragma once

#include <array>
#include <filesystem>
#include <cassert>

class Bingo
{
	// One single 5x5 bingo board containing integers
	struct BingoBoard
	{
		// One single token, a number and if it has been marked
		struct BingoToken
		{
			bool operator==(BingoToken b) { return number_ == b.number_ && isMarked == b.isMarked; }

			uint16_t number_ = 0;
			bool isMarked = false;
		};

		BingoBoard() { matrix_.fill({ 0, false }); }

		bool HasWon();

		uint16_t& at(uint16_t x, uint16_t y) { assert(x < 5 && y < 5); return matrix_.at(x + 5 * y).number_; }
		bool IsMarked(uint16_t x, uint16_t y) { assert(x < 5 && y < 5); return matrix_.at(x + 5 * y).isMarked; }

		void MarkNumber(uint16_t nb) { auto it = std::find(matrix_.begin(), matrix_.end(), BingoToken({ nb, false })); if (it != matrix_.end()) it->isMarked = true; }

		// Proper matrix logic is in fact a array of 5*5 elements, stored in a x + y*5 fashion.
		std::array<BingoToken, 25> matrix_;
		uint16_t winningNumber_;
	};

	const Bingo::BingoBoard& PlayMainLoop();

public:
	Bingo(const std::filesystem::path& path);

	uint32_t Play();

private:
	std::vector<BingoBoard> bingoBoards_;
	std::vector<uint16_t> bingoNumbers_;
};
