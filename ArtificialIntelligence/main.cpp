#include <iostream>
#include "State.h"
#include "SearchAlgorithms.h"
using namespace std;

int main(){
    //SearchAlgorithms program("123456078","123456780"); //possivel
    //SearchAlgorithms program("123506478","123456780"); //possivel
    //SearchAlgorithms program("012356478","123456780");// possivel
    //SearchAlgorithms program("123406785","123456780"); //impossivel
    SearchAlgorithms program("123506478","123560478"); //possível, p/ backtracking
    //program.ida();
    //program.backtracking();
    program.breadthSearch();
    //program.orderedSearch();
    return 0;
}
