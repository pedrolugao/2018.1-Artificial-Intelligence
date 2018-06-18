#include <iostream>
#include <stdio.h>
#include "State.h"
#include "SearchAlgorithms.h"
using namespace std;

int main(){
    //SearchAlgorithms program("123456078","123456780",3,3); //possivel
    //SearchAlgorithms program("123506478","123456780",3,3); //possivel
    //SearchAlgorithms program("012356478","123456780",3,3);// possivel
    SearchAlgorithms program("867205314","123456780",3,3);// possivel
    //SearchAlgorithms program("123405","123450",2,3);
    //SearchAlgorithms program("1234560897AB","123456789AB0",3,4);
    //SearchAlgorithms program("867254301","123456780",3,3);// MUITO DIFICIL http://w01fe.com/blog/2009/01/the-hardest-eight-puzzle-instances-take-31-moves-to-solve/
    //SearchAlgorithms program("123406785","123456780"); //impossivel
   // SearchAlgorithms program("123506478","123560478",3,3); //possível, p/ backtracking
    //SearchAlgorithms program("FE8CAB9D26513740","123456789ABCDEF0",4,4);//80 movimentos (https://puzzling.stackexchange.com/questions/24265/what-is-the-superflip-on-15-puzzle)

    std::cout<<"Breadth Search:"<<std::endl;
    strMethodStats breadth = program.breadthSearch();
    program.printStats(breadth, true);

    std::cout<<"Depth Search:"<<std::endl;
    strMethodStats depth = program.depthSearch();
    program.printStats(depth, true);

    //std::cout<<"Ordered Search:"<<std::endl;
    //strMethodStats ordered = program.orderedSearch();
    //program.printStats(ordered, true);

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

    return 0;
}
