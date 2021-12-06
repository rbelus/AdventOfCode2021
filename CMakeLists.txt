cmake_minimum_required(VERSION 3.12)

project(AdventOfCode2021)

# Source list
set (sourceList
	main.cpp
	Tools.cpp
	Sonar.cpp
	SubmarineControl.cpp
	BitDiagnostic.cpp
	Bingo.cpp)

set (headerList
	Tools.h
	Sonar.h
	SubmarineControl.h
	BitDiagnostic.h
	Bingo.h)


add_executable(AdventOfCode2021 ${sourceList})

target_compile_features(AdventOfCode2021 PUBLIC cxx_std_20)

set(AOC_INPUT_DIR_CMAKE "${CMAKE_SOURCE_DIR}/../Input" CACHE PATH "path of directory containing input from aoc website")
add_definitions( -DAOC_INPUT_DIR_CMAKE="${AOC_INPUT_DIR_CMAKE}" )