#include "FundamentalSolutions.h"

bool FundamentalSolutions::isUnique(Solution& solution) {
	auto it = fundamentals.insert(solution);
	if (!it.second) return false;
	fundamentals.erase(it.first);
	return true;
}

//void FundamentalSolutions::rotate(Solution& solution) {
//	for (auto& occ : solution) {
//		size_t temp = occ.position.first;
//		occ.position.first = occ.position.second;
//		occ.position.second = board.getRows() - temp - 1;
//	}
//	std::sort(solution.begin(), solution.end());
//}

void FundamentalSolutions::rotate(Solution& solution) {
	for (auto& occ : solution) {
		size_t temp = occ.fieldPtr.getX();
		occ.fieldPtr.setX(occ.fieldPtr.getY());
		occ.fieldPtr.setY(boardDimensions.first - temp - 1);
	}
	//	std::swap(boardDimensions.first, boardDimensions.second);
	std::sort(solution.begin(), solution.end());
}

//void FundamentalSolutions::flipHorizontally(Solution& solution) {
//	for (auto& occupator : solution) {
//		occupator.position.first = board.getCols() - occupator.position.first - 1;
//	}
//	std::sort(solution.begin(), solution.end());
//}

void FundamentalSolutions::flipHorizontally(Solution& solution) {
	for (auto& occupator : solution) {
		occupator.fieldPtr.setX(boardDimensions.first - occupator.fieldPtr.getX() - 1);
	}
	std::sort(solution.begin(), solution.end());
}

//void FundamentalSolutions::flipVertically(Solution& solution) {
//	for (auto& occupator : solution) {
//		occupator.position.second = board.getRows() - occupator.position.second - 1;
//	}
//	std::sort(solution.begin(), solution.end());
//}

void FundamentalSolutions::flipVertically(Solution& solution) {
	for (auto& occupator : solution) {
		occupator.fieldPtr.setY(boardDimensions.second - occupator.fieldPtr.getY() - 1);
	}
	std::sort(solution.begin(), solution.end());
}

bool FundamentalSolutions::isFundamentalSolution(Solution& solution, bool rotated) {

	std::sort(solution.begin(), solution.end());

	if (fundamentals.size() == 0) return true;

	//for (size_t i = 0; i < 4; i++)
	//{
	//	rotate(solution);
	//	if (!isUnique(solution)) return false;
	//	flipHorizontally(solution);
	//	if (!isUnique(solution)) return false;
	//	flipVertically(solution);
	//	if (!isUnique(solution)) return false;
	//	flipHorizontally(solution);
	//	flipVertically(solution);
	//}

	if (!isUnique(solution)) return false;
	flipHorizontally(solution);
	if (!isUnique(solution)) return false;
	flipVertically(solution);
	if (!isUnique(solution)) return false;
	flipHorizontally(solution);
	if (!isUnique(solution)) return false;
	flipVertically(solution);

	if (boardDimensions.first == boardDimensions.second && !rotated) {
		rotate(solution);
		return FundamentalSolutions::isFundamentalSolution(solution, true);
	}

	return true;
}

void FundamentalSolutions::buildFundamentals(std::vector<Solution>& distincts) {

	for (auto& solution : distincts) {
		if (isFundamentalSolution(solution)) {
			fundamentals.insert(solution);
		}
	}
}

//FundamentalSolutions::FundamentalSolutions(Board* board, std::vector<Solution>& distincts)
//	: distincts(distincts), board(board) {
//
//	buildFundamentals(distincts);
//}

FundamentalSolutions::FundamentalSolutions(std::pair<int, int> boardDimensions
	, std::vector<Solution>& distincts)
	: boardDimensions(boardDimensions), distincts(distincts)
{
	buildFundamentals(distincts);
}

int FundamentalSolutions::getFundamentalSolutions() {
	return fundamentals.size();
}
