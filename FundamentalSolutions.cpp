#include "FundamentalSolutions.h"

bool FundamentalSolutions::isUnique(Solution& solution)
{
	auto it = fundamentals.insert(solution);
	if (!it.second) return false;
	fundamentals.erase(it.first);
	return true;
}

void FundamentalSolutions::rotate(Solution& solution)
{
	for (auto& occ : solution)
	{
		size_t temp = occ.fieldPtr.getX();
		occ.fieldPtr.setX(occ.fieldPtr.getY());
		occ.fieldPtr.setY(boardDimensions.first - temp - 1);
	}
	std::sort(solution.begin(), solution.end());
}

void FundamentalSolutions::flipHorizontally(Solution& solution)
{
	for (auto& occupator : solution)
	{
		occupator.fieldPtr.setX(boardDimensions.first - occupator.fieldPtr.getX() - 1);
	}
	std::sort(solution.begin(), solution.end());
}

void FundamentalSolutions::flipVertically(Solution& solution)
{
	for (auto& occupator : solution)
	{
		occupator.fieldPtr.setY(boardDimensions.second - occupator.fieldPtr.getY() - 1);
	}
	std::sort(solution.begin(), solution.end());
}

bool FundamentalSolutions::isFundamentalSolution(Solution& solution, bool rotated)
{
	std::sort(solution.begin(), solution.end());

	if (fundamentals.size() == 0) return true;

	if (!isUnique(solution)) return false;
	flipHorizontally(solution);
	if (!isUnique(solution)) return false;
	flipVertically(solution);
	if (!isUnique(solution)) return false;
	flipHorizontally(solution);
	if (!isUnique(solution)) return false;
	flipVertically(solution);

	if (boardDimensions.first == boardDimensions.second && !rotated)
	{
		rotate(solution);
		return FundamentalSolutions::isFundamentalSolution(solution, true);
	}

	return true;
}

void FundamentalSolutions::buildFundamentals(std::vector<Solution>& distincts) {

	for (auto& solution : distincts)
	{
		if (isFundamentalSolution(solution))
		{
			fundamentals.insert(solution);
		}
	}
}

FundamentalSolutions::FundamentalSolutions(std::pair<int, int> boardDimensions
	, std::vector<Solution>& distincts)
	: boardDimensions(boardDimensions), distincts(distincts)
{
	buildFundamentals(distincts);
}

int FundamentalSolutions::getFundamentalSolutions()
{
	return fundamentals.size();
}
