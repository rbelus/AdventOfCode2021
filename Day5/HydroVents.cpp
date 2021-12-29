#include "HydroVents.h"
#include <Tools/Tools.h>

#include <regex>

HydroVentComputer::HydroVentComputer(const std::filesystem::path& path, bool withDiags)
{
	ventMatrix_.resize(1000, 1000);
	ventMatrix_.fill(0);

	auto hydroVentGenerator = [&](const std::string& line)
	{
		std::regex hydroRegex("(\\d*),(\\d*) -> (\\d*),(\\d*)");
		std::smatch coords;

		assert(std::regex_match(line, coords, hydroRegex));

		int x1 = std::stoi(coords[1].str()), 
			y1 = std::stoi(coords[2].str()),
			x2 = std::stoi(coords[3].str()),
			y2 = std::stoi(coords[4].str());

		// horizontal/vertical lines only
		if (x1 == x2)
		{
			int yMax = std::max(y1, y2);
			int yMin = std::min(y1, y2);
			for (int y = yMin; y <= yMax; y++)
				ventMatrix_(x1, y)++;
		}
		if (y1 == y2)
		{
			int xMax = std::max(x1, x2);
			int xMin = std::min(x1, x2);
			for (int x = xMin; x <= xMax; x++)
				ventMatrix_(x, y1)++;
		}
		// consider diagonal lines !
		if (withDiags && abs(x1 - x2) == abs(y1 - y2))
		{
			// Figure out the diag sense... can't be bothered making something more usable in cpp for now...
			if (y2 > y1 && x2 > x1)
				for (int i = 0; i < abs(x1 - x2) + 1; ++i)
					ventMatrix_(x1 + i, y1 + i)++;
			if (y2 < y1 && x2 > x1)
				for (int i = 0; i < abs(x1 - x2) + 1; ++i)
					ventMatrix_(x1 + i, y1 - i)++;
			if (y2 > y1 && x2 < x1)
				for (int i = 0; i < abs(x1 - x2) + 1; ++i)
					ventMatrix_(x1 - i, y1 + i)++;
			if (y2 < y1 && x2 < x1)
				for (int i = 0; i < abs(x1 - x2) + 1; ++i)
					ventMatrix_(x1 - i, y1 - i)++;
		}
    };

	ParseLinesInFile(path, hydroVentGenerator);
}

int HydroVentComputer::CountOverlaps()
{
	int count = 0;

	for (int j = 0; j < ventMatrix_.cols(); j++)
	{
		for (int i = 0; i < ventMatrix_.rows(); i++)
		{
			if (ventMatrix_(i, j) > 1)
				count++;
		}
	}

	return count;
}
