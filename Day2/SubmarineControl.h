#pragma once

#include <filesystem>

class SubmarineControl
{
	enum class DIR : int
	{
		UP = 0,
		FORWARD = 1,
		DOWN = 2,
		UNKNOWN = -1
	};

	DIR StringToDir(std::string str) const
	{
		if (str == "up")
			return DIR::UP;
		if (str == "forward")
			return DIR::FORWARD;
		if (str == "down")
			return DIR::DOWN;
		return DIR::UNKNOWN;
	}

public:
	/* @param path an input file(chart course from the aoc day), each line a string (forward, up or down) and an integer.
	*		This won't test the existence of the path, it must be valid !
	*/	
	SubmarineControl(const std::filesystem::path& path);

	void Navigate();
	int GetDepth() const { return y; }
	int GetHorizontalPosition() const { return x; }

private:
	std::vector < std::pair<DIR, int> > chartCourse_;
	int x, y, aim;
};