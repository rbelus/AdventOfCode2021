#include "Bingo.h"

#include <functional>
#include <fstream>
#include <iostream>
#include <string>
#include <numeric>

Bingo::Bingo(const std::filesystem::path& path)
{
	std::ifstream file(path.c_str(), std::ifstream::in);
	if (file.good())
	{
		// first retrieve the number sequence.
		std::string curLine;
		std::getline(file, curLine);
		std::string token;
		std::stringstream ss(curLine);

		while (std::getline(ss, token, ','))
		{
			bingoNumbers_.push_back(std::stoi(token));
		}

		// Retrieve 5x5 matrixes.
		int bingoIdx = 0;
		while (file.peek() != EOF)
		{
			// Empty line expected.
			std::getline(file, curLine);
			
			BingoBoard bingoBoard;

			for (int y = 0; y < 5; ++y)
			{
				int x = 0;
				std::getline(file, curLine);
				std::stringstream lineStream(curLine);
				for (int x = 0; x < 5; ++x)
				{
					lineStream >> bingoBoard.at(x, y);
				}

				x++;
			}

			bingoBoards_.push_back(std::move(bingoBoard));
			bingoIdx++;
		}
	}
}

const Bingo::BingoBoard& Bingo::PlayMainLoop()
{
	for (auto nb : bingoNumbers_)
	{
		for (auto& bingoBoard : bingoBoards_)
		{
			bingoBoard.MarkNumber(nb);
			if (bingoBoard.HasWon())
			{
				bingoBoard.winningNumber_ = nb;
				return bingoBoard;
			}
		}
	}

	assert(false);
	return Bingo::BingoBoard();
}

uint32_t Bingo::Play()
{
	const auto& winningBoard = PlayMainLoop();

	// Compute Score
	uint32_t score = 0;
	for (int i = 0; i < winningBoard.matrix_.size(); ++i)
	{
		if (!winningBoard.matrix_[i].isMarked)
			score += winningBoard.matrix_[i].number_;
	}
	score *= winningBoard.winningNumber_;

	return score;
}


bool Bingo::BingoBoard::HasWon()
{
	// Check all the lines
	for (int y = 0; y < 5; ++y)
	{
		bool line = true;
		for (int x = 0; x < 5; ++x)
		{
			line &= IsMarked(x, y);
		}

		if (line)
			return true;
	}

	// Check the columns
	for (int x = 0; x < 5; ++x)
	{
		bool column = true;
		for (int y = 0; y < 5; ++y)
		{
			column &= IsMarked(x, y);
		}

		if (column)
			return true;
	}

	// Check the diags --> no don't
	// Leaving this here for posterity (15 min of stupid debug)
	//bool diag1 = true, diag2 = true;
	//for (int y = 0; y < 5; ++y)
	//{
	//	int x = y;
	//	diag1 &= IsMarked(x, y);

	//	x = 4 - y;
	//	diag2 &= IsMarked(x, y);
	//}
	//if (diag1 || diag2)
	//	return true;

	return false;
}
