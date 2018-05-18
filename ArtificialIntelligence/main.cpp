#include <iostream>
#include "State.h"
#include "SearchAlgorithms.h"
using namespace std;

int main(){
    //SearchAlgorithms program("123456078","123456780"); //possivel
    //SearchAlgorithms program("123506478","123456780"); //possivel
    SearchAlgorithms program("012356478","123456780");// possivel
    //SearchAlgorithms program("123406785","123456780"); //impossivel
    //SearchAlgorithms program("123506478","123560478"); //possível, p/ backtracking
    //program.ida();
    //program.backtracking();

    std::cout<<"Breadth Search:"<<std::endl;
    strMethodStats breadth = program.breadthSearch();
    program.printStats(breadth, true);

    //std::cout<<"Depth Search:"<<std::endl;
    //strMethodStats depth = program.depthSearch();
    //program.printStats(depth, true);

    std::cout<<"Ordered Search:"<<std::endl;
    strMethodStats ordered = program.orderedSearch();
    program.printStats(ordered, true);


    //std::cout<<"Greedy Search:"<<std::endl;
    //strMethodStats greedy = program.greedy();
    //program.printStats(greedy, true);

    std::cout<<"A* Search:"<<std::endl;
    strMethodStats astar = program.astar();
    program.printStats(astar, true);




    return 0;
}
