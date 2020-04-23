#include <iostream>
#include "Manager.h"
#include "FundamentalSolutions.h"


int main()
{
    Manager manager;
    manager.work();

    auto solutions = manager.getDistinctSolutions();
    std::cout << "size of allSolutions is : " << solutions.size() << std::endl;

    //for (auto sol : solutions)
    //{
    //    std::cout << sol;
    //}

    //FundamentalSolutions fundaments(std::make_pair(manager.rows(), manager.cols()), solutions);
    //std::cout << "number of fundamental solutions: " << fundaments.getFundamentalSolutions() << std::endl;

    return 0;
}

