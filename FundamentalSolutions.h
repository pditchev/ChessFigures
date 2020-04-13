#pragma once
#include <vector>
#include <unordered_set>
#include "Occupator.h"
#include "Solution.h"

class FundamentalSolutions
{
private:
	//Board* board;
	std::pair<int, int> boardDimensions;

	std::vector<Solution>& distincts;
	std::unordered_set<Solution> fundamentals;

	bool isUnique(Solution& solution);

	void rotate(Solution& solution);

	void flipHorizontally(Solution& solution);

	void flipVertically(Solution& solution);

	bool isFundamentalSolution(Solution& solution, bool rotated = false);

	void buildFundamentals(std::vector<Solution>& distincts);

public:

	FundamentalSolutions(std::pair<int, int> boardDimensions, std::vector<Solution>& distincts);

	int getFundamentalSolutions();
};