#include "Manager.h"

Manager::Manager()
{
	noOfThreads = std::thread::hardware_concurrency() - 1;
}

Manager::~Manager(){}

void Manager::work() {

	initializer.getInput();
	initializer.start();

	permPerThread = initializer.piecesRepo.size() / noOfThreads + 1;

	std::vector<std::thread> threads(noOfThreads);
	std::vector<WorkHorse*> horses(noOfThreads);

	auto piecesBegin = initializer.piecesRepo.begin();

	for (size_t i = 0; i < noOfThreads; i++)
	{
		std::vector<std::stack<std::unique_ptr<FigureBase>
			, std::vector<std::unique_ptr<FigureBase>>>> piecesForThread;
		auto piecesEnd = std::next(piecesBegin, permPerThread);
		if (i == noOfThreads - 1) piecesEnd = initializer.piecesRepo.end();
//		piecesForThread.assign(piecesBegin, piecesEnd);
		std::move(piecesBegin, piecesEnd, std::back_inserter(piecesForThread));
		if (piecesForThread.empty()) break;

		horses[i] = new WorkHorse(std::move(piecesForThread));

		threads[i] = std::thread(&WorkHorse::startIter, horses[i]);

		if (piecesEnd >= initializer.piecesRepo.end()) break;
		piecesBegin = piecesEnd;
	}

	std::cout << "number of threads: " << noOfThreads << std::endl;

	for (size_t i = 0; i < noOfThreads; i++) {

		if (threads[i].joinable()) {
			threads[i].join();
			distinctSolutions.insert(distinctSolutions.end()
				, horses[i]->distinctSolutions.begin()
				, horses[i]->distinctSolutions.end());

			delete horses[i];
		}
	}
}

std::vector<Solution> Manager::getDistinctSolutions()
{
	return distinctSolutions;
}

int Manager::rows()
{
	return initializer.boardDimensions.first;
}

int Manager::cols()
{
	return initializer.boardDimensions.second;
}