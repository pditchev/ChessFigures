#pragma once
#include <vector>
#include <memory>
#include <stack>
//#include <type_traits>
#include <typeinfo>
#include "Figure.h"
#include "FigureFactory.h"
#include "Occupator.h"
#include "Solution.h"



class WorkHorse {

private:

    Board* board;
    FigureFactory* figFactory;
    Solution                solution;
    struct SnapShotStruct {

        FieldPointer fieldPtr;
        std::shared_ptr<Figure> figure;
        int stage = 0;

        SnapShotStruct(std::shared_ptr<Figure> figure, FieldPointer passedField);

        //SnapShotStruct(const SnapShotStruct& other);

        //SnapShotStruct& operator=(const SnapShotStruct& other);
    };


    bool setFigure(const Occupator& occupator);   // function name may be inappropriate!!!

    void cleanFigure(const SnapShotStruct snapshotStruct);

    bool walkingOnTheBoard(SnapShotStruct& currentSnapShot);

public:


    std::vector<Solution>   distinctSolutions;

    WorkHorse(std::vector<std::stack<std::shared_ptr<Figure>>> piecesForThread);

    ~WorkHorse();

    void start();

    void place(std::shared_ptr<Figure> figure, FieldPointer passedField);

    void startIter();

    std::vector<Solution> getDistinctSolutions();
};