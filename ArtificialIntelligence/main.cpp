#include <iostream>
#include <stdio.h>
#include "State.h"
#include "SearchAlgorithms.h"
using namespace std;

int main(){

    std::string start, goal;
    int ncolumns, nrows;

    while(std::cin >> start >> goal >> ncolumns >> nrows){

        SearchAlgorithms program(start, goal, ncolumns, nrows);

        std::cout<<"A* Search:"<<std::endl;
        strMethodStats astar = program.astar();
        program.printStats(astar, true);

        std::cout<<"IDA* Search:"<<std::endl;
        strMethodStats ida = program.ida();
        program.printStats(ida, true);

        std::cout<<"Greedy Search:"<<std::endl;
        strMethodStats greedy = program.greedy();
        program.printStats(greedy, true);


        std::cout<<"Depth Search:"<<std::endl;
        strMethodStats depth = program.depthSearch();
        program.printStats(depth, true);

        std::cout<<"Backtracking:"<<std::endl;
        strMethodStats bt = program.backtracking();
        program.printStats(bt, true);

        std::cout<<"Breadth Search:"<<std::endl;
        strMethodStats breadth = program.breadthSearch();
        program.printStats(breadth, true);

        std::cout<<"Ordered Search:"<<std::endl;
        strMethodStats ordered = program.orderedSearch();
        program.printStats(ordered, true);

    }

    return 0;
}
