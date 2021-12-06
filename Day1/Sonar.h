#include <filesystem>

class Sonar
{
public:
	/* @param path an input file(radar sweep from the aoc day), each line only a depth number as an unsigned int.
	*		This won't test the existence of the path, it must be valid !
	*/
	Sonar(const std::filesystem::path& path);

	size_t GetDepthIncreases(const std::vector<size_t>& depthList) const;
	size_t GetSlidingDepthIncreases(const std::vector<size_t>& depthList) const; // same as above but counts sum of 3 depths.

	// Getters
	const auto& GetMeasures() { return depthMeasurements_; }

private:
	// Normally read from input file (by constructor)
	std::vector<size_t> depthMeasurements_;
};