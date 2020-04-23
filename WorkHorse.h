#pragma once
#include <vector>
#include <memory>
#include <stack>
//#include <typeinfo>
#include "Figure.h"
#include "FigureFactory.h"
#include "Occupator.h"
#include "Solution.h"

class WorkHorse {

    Board* board;
    std::vector<Field>& fields;


    FigureFactory* figFactory;
    Solution                solution;
    struct SnapShotStruct
    {
        FieldPointer fieldPtr;
        std::unique_ptr<FigureBase> figure;
        int stage = 0;

        SnapShotStruct(std::unique_ptr<FigureBase> figure, FieldPointer passedField);

        SnapShotStruct(SnapShotStruct&& other) noexcept;

        SnapShotStruct& operator=(SnapShotStruct&& other) noexcept;

    };

    void unboardFigure(SnapShotStruct& snapshotStruct);

    bool tryToPlace(SnapShotStruct& currentSnapShot);

    bool possiblePlacement(const FigureBase& figure, FieldPointer where);

public:

    std::vector<Solution>   distinctSolutions;

    WorkHorse(std::vector<std::stack<std::unique_ptr<FigureBase>
        , std::vector<std::unique_ptr<FigureBase>>>> piecesForThread);

    ~WorkHorse();

    void startIter();

    std::vector<Solution> getDistinctSolutions();
};