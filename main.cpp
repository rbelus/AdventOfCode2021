#include <iostream>

#include "Day1/Sonar.h"
#include "Day2/SubmarineControl.h"
#include "Day3/BitDiagnostic.h"
#include "Day4/Bingo.h"
#include "Day5/HydroVents.h"

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

	uint32_t oxygen, co2;
	bitDiag.ComputeOxygenCO2Levels(oxygen, co2);

	std::cout << "Oxygen : " << oxygen << " Carbon Dioxide : " << co2 << std::endl;
	std::cout << "Result for Day3 part2 : " << oxygen * co2 << std::endl;

	// Day 4 we play bingo
	inputFile = std::string(AOC_INPUT_DIR) + "/day4.txt";
	inputFile.make_preferred();

	Bingo bingo(inputFile);
	auto scoreWin = bingo.Play(true);
	std::cout << "Day4 part1 :" << scoreWin << std::endl;

	auto scoreLose = bingo.Play(false);
	std::cout << "Day4 part2 :" << scoreLose << std::endl;

	// Day 5
	inputFile = std::string(AOC_INPUT_DIR) + "/day5.txt";
	inputFile.make_preferred();

	HydroVentComputer hydro(inputFile, false);
	int hydroOverlaps = hydro.CountOverlaps();

	std::cout << "Day5 part1 : " << hydroOverlaps << std::endl;

	hydro = HydroVentComputer(inputFile, true);
	hydroOverlaps = hydro.CountOverlaps();

	std::cout << "Day5 part2 : " << hydroOverlaps << std::endl;


	return 0;
}