#include "HydroVents.h"
#include "HydroVents.h"
#include <Tools/Tools.h>

#include <regex>

HydroVentComputer::HydroVentComputer(const std::filesystem::path& path)
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
			for(int y = yMin; y <= yMax; y++)
				ventMatrix_(x1,y) += 1;
		}
		if (y1 == y2)
		{
			int xMax = std::max(x1, x2);
			int xMin = std::min(x1, x2);
			for (int x = xMin; x <= xMax; x++)
				ventMatrix_(x, y1) += 1;
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
