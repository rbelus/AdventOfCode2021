#include <iostream>

#include "Sonar.h"
#include "SubmarineControl.h"
#include "BitDiagnostic.h"

#define AOC_INPUT_DIR AOC_INPUT_DIR_CMAKE

int main()
{
	// Day 1 Sonar Sweep
	std::filesystem::path inputFile(std::string(AOC_INPUT_DIR) + "/day1.txt");
	inputFile = inputFile.make_preferred();
	Sonar sonar(inputFile);

	std::cout << "Sonar depth increases : " << sonar.GetDepthIncreases(sonar.GetMeasures()) << std::endl;
	std::cout << "Sum Sonar depth increases : " << sonar.GetSlidingDepthIncreases(sonar.GetMeasures()) << std::endl;

	// Day 2 course
	inputFile = std::string(AOC_INPUT_DIR) + "/day2.txt";
	inputFile.make_preferred();
	SubmarineControl subControl(inputFile);
	subControl.Navigate();

	int x = subControl.GetHorizontalPosition(), y = subControl.GetDepth();
	std::cout << "New Horizontal position : " << x << std::endl;
	std::cout << "New Depth : " << y << std::endl;
	std::cout << "Result for Day2 part2 : " << x * y << std::endl;

	// Day 3 diagnostic
	inputFile = std::string(AOC_INPUT_DIR) + "/day3.txt";
	inputFile.make_preferred();

	uint32_t gamma, epsilon;
	BitDiagnostic<12> bitDiag(inputFile);
	bitDiag.ComputeGammaEpsilonRate(gamma, epsilon);

	std::cout << "Gamma Rate : " << gamma << " Epsilon Rate : " << epsilon << std::endl;
	std::cout << "Result for Day3 part1 : " << gamma * epsilon << std::endl;

	return 0;
}