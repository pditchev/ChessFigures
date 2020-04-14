#pragma once
#include <vector>
#include <memory>
#include <stack>
#include <typeinfo>
#include "Figure.h"
#include "FigureFactory.h"
#include "Occupator.h"
#include "Solution.h"

class WorkHorse {

    Board* board;
    FigureFactory* figFactory;
    Solution                solution;
    struct SnapShotStruct
    {
        FieldPointer fieldPtr;
        std::shared_ptr<Figure> figure;
        int stage = 0;

        SnapShotStruct(std::shared_ptr<Figure> figure, FieldPointer passedField);
    };

    void cleanFigure(const SnapShotStruct snapshotStruct);

    bool walkingOnTheBoard(SnapShotStruct& currentSnapShot);

public:

    std::vector<Solution>   distinctSolutions;

    WorkHorse(std::vector<std::stack<std::shared_ptr<Figure>>> piecesForThread);

    ~WorkHorse();

    void startIter();

    std::vector<Solution> getDistinctSolutions();
};