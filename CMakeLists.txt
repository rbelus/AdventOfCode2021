cmake_minimum_required(VERSION 3.12)

project(AdventOfCode2021)

# Source list
set (sourceList
	main.cpp
	Tools/Tools.cpp
	Day1/Sonar.cpp
	Day2/SubmarineControl.cpp
	Day3/BitDiagnostic.cpp
	Day4/Bingo.cpp
	Day5/HydroVents.cpp
	Day6/LanternFishSimulator.cpp
	Day7/CrabAlignator.cpp
	Day8/DigiCrypto.cpp)

set (headerList
	Tools/Tools.h
	Day1/Sonar.h
	Day2/SubmarineControl.h
	Day3/BitDiagnostic.h
	Day4/Bingo.h
	Day5/HydroVents.h
	Day6/LanternFishSimulator.h
	Day7/CrabAlignator.h
	Day8/DigiCrypto.h)


add_executable(AdventOfCode2021 ${sourceList})

target_compile_features(AdventOfCode2021 PUBLIC cxx_std_20)
target_include_directories(AdventOfCode2021 PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/include/eigen-3.4.0/ )

set(AOC_INPUT_DIR_CMAKE "${CMAKE_SOURCE_DIR}/../Input" CACHE PATH "path of directory containing input from aoc website")
add_definitions( -DAOC_INPUT_DIR_CMAKE="${AOC_INPUT_DIR_CMAKE}" )