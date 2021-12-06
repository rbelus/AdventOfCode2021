#include "Bingo.h"

#include <functional>
#include <fstream>
#include <iostream>
#include <string>

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

uint32_t Bingo::Play()
{
	for (auto nb : bingoNumbers_)
	{
		for (auto& bingoBoard : bingoBoards_)
		{
			bingoBoard.markNumber(nb);
			if (bingoBoard.HasWon())
				return;
		}
	}
}

bool Bingo::BingoBoard::HasWon()
{


	return false;
}
