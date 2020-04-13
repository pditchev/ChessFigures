#pragma once
#include <thread>
#include "Initializer.h"
#include "WorkHorse.h"


class Manager
{
	int noOfThreads = 3;
	int permPerThread;
	Initializer initializer;

	std::vector<Solution>   distinctSolutions;



public:
	Manager();
	~Manager();

	void work();

	std::vector<Solution> getDistinctSolutions();

	int rows();
	int cols();
};

