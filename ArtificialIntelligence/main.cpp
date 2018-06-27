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
        //SearchAlgorithms program("123456078","123456780",3,3); //possivel 2
        //SearchAlgorithms program("123506478","123456780",3,3); //possivel 4
        //SearchAlgorithms program("012356478","123456780",3,3);// possivel 12
        //SearchAlgorithms program("032871456","123456780",3,3);// possivel 24
        //SearchAlgorithms program("867205314","123456780",3,3);// possivel 29
        //SearchAlgorithms program("123405","123450",2,3); //2x3
        //SearchAlgorithms program("1234560897AB","123456789AB0",3,4); //3x4
        //SearchAlgorithms program("867254301","123456780",3,3);// 31 MUITO DIFICIL http://w01fe.com/blog/2009/01/the-hardest-eight-puzzle-instances-take-31-moves-to-solve/
        //SearchAlgorithms program("FE8CAB9D26513740","123456789ABCDEF0",4,4);//80 movimentos (https://puzzling.stackexchange.com/questions/24265/what-is-the-superflip-on-15-puzzle)

        std::cout<<"Depth Search:"<<std::endl;
        strMethodStats depth = program.depthSearch();
        program.printStats(depth, true);

        std::cout<<"Greedy Search:"<<std::endl;
        strMethodStats greedy = program.greedy();
        program.printStats(greedy, true);

        std::cout<<"A* Search:"<<std::endl;
        strMethodStats astar = program.astar();
        program.printStats(astar, true);

        std::cout<<"IDA* Search:"<<std::endl;
        strMethodStats ida = program.ida();
        printf("\n");
        program.printStats(ida, true);

        std::cout<<"Backtracking:"<<std::endl;
        strMethodStats bt = program.backtracking();
        printf("\n");
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
