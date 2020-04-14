#include "Initializer.h"
#include "Board.h"

void Initializer::getInput()
{
	std::cout << "Please, insert the number of rows of the board: ";
	int rows;
	while (!(std::cin >> rows) || rows < 1 || rows > MAX_ROWS) {
		std::cout << "Please, try again! Insert a number between 1 and "
			<< MAX_ROWS << " inclusive!" << std::endl;
	}
	boardDimensions.first = rows;

	std::cout << "Please, insert the number of columns of the board: ";
	int cols;
	while (!(std::cin >> cols) || cols < 1 || cols > MAX_COLS) {
		std::cout << "Please, try again! Insert a number between 1 and "
			<< MAX_COLS << " inclusive!" << std::endl;
	}
	boardDimensions.second = cols;

	for (auto& i : init) {
		auto fig = FigureFactory::produceFigure(i.first);
		int numberFig = 0;
		std::cout << "Please, insert number of " << fig->name << "s: ";
		while (!(std::cin >> numberFig) || numberFig < 0 || numberFig > MAX_FIGURES)
		{
			std::cout << "Please, try again! Insert a number between 0 and "
				<< MAX_FIGURES << " inclusive!" << std::endl;
		}
		i.second = numberFig;
	}

}

void Initializer::start()
{
	Board::init(boardDimensions);
	makeInitial(init);
	noPermute();
	//permute(0);
	std::cout << "permutations: " << piecesRepo.size() << std::endl;
}

void Initializer::makeInitial(std::vector<std::pair<Piece, int>>& pieces) {

	std::sort(pieces.begin(), pieces.end()
		, [](std::pair<Piece, int>& lhs, std::pair<Piece, int>& rhs)
		{ return lhs.second > rhs.second;  });

	for (auto p : pieces) {
		for (size_t i = 0; i < p.second; i++)
		{
			initial.push_back(p.first);
		}
	}
}

void Initializer::permute(int index) {
	if (index >= initial.size()) {
		std::stack<std::shared_ptr<Figure>> help_stack;
		for (const auto& p : initial)
		{
			help_stack.push(FigureFactory::produceFigure(p));
		}
		piecesRepo.push_back(help_stack);
	}
	else {

		std::set<Piece> swapped;

		for (size_t i = index; i < initial.size(); i++)
		{
			if (swapped.count(initial[i]))   continue;

			std::swap(initial[index], initial[i]);

			permute(index + 1);

			std::swap(initial[index], initial[i]);

			swapped.insert(initial[i]);
		}
	}
}

void Initializer::noPermute() {

	std::stack<std::shared_ptr<Figure>> help_stack;

	for (const auto& p : initial)
	{
		help_stack.push(FigureFactory::produceFigure(p));
	}
	piecesRepo.push_back(help_stack);
}