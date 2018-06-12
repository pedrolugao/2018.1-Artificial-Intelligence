#include "SearchAlgorithms.h"
#include <vector>
#include <string>
#include <list>
#include <stdio.h>
#include <iostream>
#include<chrono>
#define INFINITY 9999
#define MAX_LEVEL 40

int level(State *s){
    State* pai = s->getParent();
    if(pai == NULL) return 0;
    int contador = 1;
    while(pai!=NULL){
        pai = pai->getParent();
        contador++;
    }
    return contador;
}

void SearchAlgorithms::freeLists(){
    for(int i = 0; i<closedNodes.size();i++)
        if(goal != closedNodes.at(i) && initial != closedNodes.at(i))
            delete closedNodes.at(i);


    for(int i = 0; i<openNodes.size();i++)
        if(goal!= openNodes.at(i) && initial != openNodes.at(i))
            delete openNodes.at(i);



    openNodes.clear();
    closedNodes.clear();
}

/*
    Constructor of SearchAlgorithm class
	*@param std::string initialString:	specifies the initial state
            std::string goalString:     specifies the goal state
	*@return -
*********************************************************/
SearchAlgorithms::SearchAlgorithms(std::string initialString,std::string goalString, int width, int heigth){
    //ctor
    initial = new State(initialString,width,heigth);
    goal = new State(goalString,width,heigth);
    //initial->print();
    //goal->print();
}

SearchAlgorithms::~SearchAlgorithms(){
    //dtor
}


/*
	Runs the backtracking search method
	*@param -
	*@return void: -
*********************************************************/
strMethodStats SearchAlgorithms::backtracking(){

    //Start measuring time:
    auto start = std::chrono::system_clock::now();

    std::vector<State*> solution;

    bool success = backtrackingAux(initial, 0, solution);

    //Get time elapsed in milliseconds
    auto end = std::chrono::system_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    float time = (float)elapsed.count();

    return buildStats(!success, solution.front(),0, (int) solution.size(), time);
}

/*
	Recursive auxiliar function for the backtracking search method
	ORDER: left, right, top, bottom
	*@param State *s:           indicates the state from where the path begins
            int cost:           indicates the cost from the path
			std::vector<State*>	stores the current solution
	*@return bool:              1 if the goal was found, 0 otherwise
*********************************************************/
bool SearchAlgorithms::backtrackingAux(State *s, int cost, std::vector<State*> &solution){
    printf("\rNivel: %d",level(s));
    if(level(s)> MAX_LEVEL) return false;

    if(compare(s, goal)){
        solution.push_back(s);
        return true;
    }else{
        State * next = s->getLeft();
        if(next != NULL){
            if(!onPath(s, next) && backtrackingAux(next, cost + 1, solution)){
                solution.push_back(s);
                return true;
            }
        }
        next = s->getRight();
        if(next != NULL){
            if(!onPath(s, next) && backtrackingAux(next, cost + 1, solution)){
                solution.push_back(s);
                return true;
            }
        }
        next = s->getTop();
        if(next != NULL){
            if(!onPath(s, next) && backtrackingAux(next, cost + 1, solution)){
                solution.push_back(s);
                return true;
            }
        }
        next = s->getBottom();
        if(next != NULL){
            if(!onPath(s, next) && backtrackingAux(next, cost + 1, solution)){
                solution.push_back(s);
                return true;
            }
        }
    }
    return false;
}

void SearchAlgorithms::printStats(strMethodStats stats, bool flag){
    if(flag)
        std::cout << "notFound, depth, cost, openNodesSize, closedNodesSize, ramification, time" << std::endl;
    std::cout << stats.notFound << ", " << stats.depth << ", " << stats.cost << ", " << stats.openNodesSize << ", " << stats.closedNodesSize << ", " << stats.ramification << ", " << stats.time << std::endl;
    freeLists();
}

/*
	Runs the breadth search method
	*@param -
	*@return void: -
*********************************************************/
strMethodStats SearchAlgorithms::breadthSearch(){
    //Start measuring time:
    auto start = std::chrono::system_clock::now();


    //std::list<State*> openNodes;
    //std::vector<State*> closedNodes;
    openNodes.push_back(initial);
    State * current;
    bool solutionFound = false;
    while(!openNodes.empty()){
        current = openNodes.front();

        printf("\rFechados:%d, Abertos:%d, Nivel:%d\t\t\t\t\t\t",openNodes.size(),closedNodes.size(),level(current));

        openNodes.erase(openNodes.begin());

        State* left = current->getLeft();
        State* right = current->getRight();
        State* top = current->getTop();
        State* bottom = current->getBottom();
        if(left != NULL && !onPath(current,left)) openNodes.push_back(left);
        if(right != NULL && !onPath(current,right)) openNodes.push_back(right);
        if(top != NULL && !onPath(current,top)) openNodes.push_back(top);
        if(bottom != NULL && !onPath(current,bottom)) openNodes.push_back(bottom);

        closedNodes.push_back(current);
        if(compare(current,goal)){
            solutionFound = true;
            break;
        }
    }

    //Get time elapsed in milliseconds
    auto end = std::chrono::system_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    float time = (float)elapsed.count();

    return buildStats(!solutionFound, current, (int) openNodes.size(), (int) closedNodes.size(), time);
}

/*
	Runs the depth search method
	*@param -
	*@return void: -
*********************************************************/
strMethodStats SearchAlgorithms::depthSearch(){
    //Start measuring time:
    auto start = std::chrono::system_clock::now();
    printf("%d",openNodes.size());
    //std::list<State*> openNodes;
    //std::vector<State*> closedNodes;
    openNodes.push_back(initial);
    State * current;
    bool solutionFound = false;
    while(!openNodes.empty()){
        current = openNodes.back();

        printf("\rFechados:%d, Abertos:%d, Nivel:%d\t\t\t\t\t\t",openNodes.size(),closedNodes.size(),level(current));
        if(level(current)> MAX_LEVEL){ //Busca em profundidade limtada: simula fila quando passo do nivel maximo
            current = openNodes.front();
            openNodes.erase(openNodes.begin());
        }else{
            openNodes.pop_back();
        }
        State* left = current->getLeft();
        State* right = current->getRight();
        State* top = current->getTop();
        State* bottom = current->getBottom();
        if(bottom != NULL && !onPath(current,bottom)) openNodes.push_back(bottom);
        if(top != NULL && !onPath(current,top)) openNodes.push_back(top);
        if(right != NULL && !onPath(current,right)) openNodes.push_back(right);
        if(left != NULL && !onPath(current,left)) openNodes.push_back(left);

        closedNodes.push_back(current);
        if(compare(current,goal)){
            solutionFound = true;
            break;
        }
    }

    //Get time elapsed in milliseconds
    auto end = std::chrono::system_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    float time = (float)elapsed.count();

    return buildStats(!solutionFound, current, (int) openNodes.size(), (int) closedNodes.size(), time);


}

/*
	Runs the greedy search method
	*@param -
	*@return void: -
*********************************************************/
strMethodStats SearchAlgorithms::greedy(){

    //Start measuring time:
    auto start = std::chrono::system_clock::now();

    //std::vector<State*> openNodes;
    std::vector<int> openNodesCosts;
    //std::vector<State*> closedNodes;
    openNodes.push_back(initial);
    openNodesCosts.push_back(h1(initial));
    State * current;
    int currentCost;
    bool solutionFound = false;
    while(!openNodes.empty()){
        //Find min element in costs
        int minIndex = 0;
        for(unsigned int j=0;j<openNodesCosts.size();j++){
            if(openNodesCosts[j]<openNodesCosts[minIndex]){
                minIndex = j;
            }
        }

        //Get min element from open nodes and erase from list
        current = openNodes[minIndex];

        printf("\rFechados:%d, Abertos:%d, Nivel:%d\t\t\t\t\t\t",openNodes.size(),closedNodes.size(),level(current));

        currentCost = openNodesCosts[minIndex];
        openNodes.erase(openNodes.begin() + minIndex);
        openNodesCosts.erase(openNodesCosts.begin() + minIndex);

        State* left = current->getLeft();
        State* right = current->getRight();
        State* top = current->getTop();
        State* bottom = current->getBottom();

        if(bottom != NULL && !onPath(current,bottom)){
            openNodes.push_back(bottom);
            openNodesCosts.push_back(h1(bottom));
        }
        if(top != NULL && !onPath(current,top)){
            openNodes.push_back(top);
            openNodesCosts.push_back(h1(top));
        }
        if(left != NULL && !onPath(current,left)){
            openNodes.push_back(left);
            openNodesCosts.push_back(h1(left));
        }
        if(right != NULL && !onPath(current,right)){
            openNodes.push_back(right);
            openNodesCosts.push_back(h1(right));
        }

        closedNodes.push_back(current);
        if(compare(current,goal)){
            solutionFound = true;
            break;
        }
    }

    //Get time elapsed in milliseconds
    auto end = std::chrono::system_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    float time = (float)elapsed.count();

    return buildStats(!solutionFound, current, (int) openNodes.size(), (int) closedNodes.size(), time);
}

/*
	Runs the A* search method
	*@param -
	*@return void: -
*********************************************************/
strMethodStats SearchAlgorithms::astar(){

    //Start measuring time:
    auto start = std::chrono::system_clock::now();

    //std::vector<State*> openNodes;
    std::vector<int> openNodesCosts;
    //std::vector<State*> closedNodes;
    openNodes.push_back(initial);
    openNodesCosts.push_back(0 + h1(initial));
    State * current;
    int currentCost;
    bool solutionFound = false;
    while(!openNodes.empty()){
        //Find min element in costs
        int minIndex = 0;
        for(unsigned int j=0;j<openNodesCosts.size();j++){
            if(openNodesCosts[j]<openNodesCosts[minIndex]){
                minIndex = j;
            }
        }

        //Get min element from open nodes and erase from list
        current = openNodes[minIndex];

        printf("\rFechados:%d, Abertos:%d, Nivel:%d\t\t\t\t\t\t",openNodes.size(),closedNodes.size(),level(current));

        currentCost = openNodesCosts[minIndex];
        openNodes.erase(openNodes.begin() + minIndex);
        openNodesCosts.erase(openNodesCosts.begin() + minIndex);

        State* left = current->getLeft();
        State* right = current->getRight();
        State* top = current->getTop();
        State* bottom = current->getBottom();

        if(bottom != NULL && !onPath(current,bottom)){
            openNodes.push_back(bottom);
            openNodesCosts.push_back(currentCost - h1(current) + 1 + h1(bottom));
        }
        if(top != NULL && !onPath(current,top)){
            openNodes.push_back(top);
            openNodesCosts.push_back(currentCost - h1(current) + 1 + h1(top));
        }
        if(left != NULL && !onPath(current,left)){
            openNodes.push_back(left);
            openNodesCosts.push_back(currentCost - h1(current) + 1 + h1(left));
        }
        if(right != NULL && !onPath(current,right)){
            openNodes.push_back(right);
            openNodesCosts.push_back(currentCost - h1(current) + 1 + h1(right));
        }

        closedNodes.push_back(current);
        if(compare(current,goal)){
            solutionFound = true;
            break;
        }
    }

    //Get time elapsed in milliseconds
    auto end = std::chrono::system_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    float time = (float)elapsed.count();

    return buildStats(!solutionFound, current, (int) openNodes.size(), (int) closedNodes.size(), time);

}

/*
	Runs the ordered search method
	*@param -
	*@return void: -
*********************************************************/
strMethodStats SearchAlgorithms::orderedSearch(){

    //Start measuring time:
    auto start = std::chrono::system_clock::now();

    //std::vector<State*> openNodes;
    std::vector<int> openNodesCosts;
    //std::vector<State*> closedNodes;
    openNodes.push_back(initial);
    openNodesCosts.push_back(0);
    State * current;
    int currentCost;
    bool solutionFound = false;
    while(!openNodes.empty()){
        //Find min element in costs
        int minIndex = 0;
        for(unsigned int j=0;j<openNodesCosts.size();j++){
            if(openNodesCosts[j]<openNodesCosts[minIndex]){
                minIndex = j;
            }
        }

        //Get min element from open nodes and erase from list
        current = openNodes[minIndex];

        printf("\rFechados:%d, Abertos:%d, Nivel:%d\t\t\t\t\t\t",openNodes.size(),closedNodes.size(),level(current));

        currentCost = openNodesCosts[minIndex];
        openNodes.erase(openNodes.begin() + minIndex);
        openNodesCosts.erase(openNodesCosts.begin() + minIndex);

        State* left = current->getLeft();
        State* right = current->getRight();
        State* top = current->getTop();
        State* bottom = current->getBottom();

        if(bottom != NULL && !onPath(current,bottom)){
            openNodes.push_back(bottom);
            openNodesCosts.push_back(currentCost +1);
        }
        if(top != NULL && !onPath(current,top)){
            openNodes.push_back(top);
            openNodesCosts.push_back(currentCost +1);
        }
        if(left != NULL && !onPath(current,left)){
            openNodes.push_back(left);
            openNodesCosts.push_back(currentCost +1);
        }
        if(right != NULL && !onPath(current,right)){
            openNodes.push_back(right);
            openNodesCosts.push_back(currentCost +1);
        }

        closedNodes.push_back(current);
        if(compare(current,goal)){
            solutionFound = true;
            break;
        }
    }

    //Get time elapsed in milliseconds
    auto end = std::chrono::system_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    float time = (float)elapsed.count();

    return buildStats(!solutionFound, current, (int) openNodes.size(), (int) closedNodes.size(), time);
}

/*
	Runs the IDA* search method
	*@param -
	*@return void: -
*********************************************************/
strMethodStats SearchAlgorithms::ida(){

    //Start measuring time:
    auto start = std::chrono::system_clock::now();

    std::vector<State*> solution;
    int step = h1(initial);
    int old_step = -1;
    bool success = false;
    int * minThrow = new int(INFINITY);
    while (old_step!=step && !success){
        if(idaAux(initial,step,0,minThrow,solution)){
            success = true;
        }else{
            old_step = step;
            step = *minThrow;
            *minThrow = INFINITY;
            //printf("New step is equal to %d",step);
        }
    }

    //Get time elapsed in milliseconds
    auto end = std::chrono::system_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    float time = (float)elapsed.count();

    return buildStats(!success, solution.front(),0, (int) solution.size(), time);

}

/*
	Recursive auxiliar function for the IDA* search method
	ORDER: left, right, top, bottom
	*@param State *s:           indicates the state from where the path begins
            int step:           stores the maximun step for a specific run
            int cost:           indicates the cost from the path
			std::vector<State*>	stores the current solution
	*@return bool:              1 if the goal was found, 0 otherwise
*********************************************************/
bool SearchAlgorithms::idaAux(State* s,int step, int cost,int *minThrow, std::vector<State*> &solution){

    printf("\rNivel: %d",level(s));

    int f = cost + h1(s);
    if(f>step){
        if(f < (*minThrow)){
            *minThrow = f;
        }
        //printf("Discarted solution:");
        //s->print();
        return false;
    }
    if(compare(s,goal)){
        solution.push_back(s);
        return true;
    }else{
        State* next = s->getLeft();
        if(next!= NULL && !onPath(s,next) && idaAux(next,step,cost+1,minThrow,solution)){
            solution.push_back(s);
            return true;
        }
        next = s->getRight();
        if(next!= NULL && !onPath(s,next) && idaAux(next,step,cost+1,minThrow,solution)){
            solution.push_back(s);
            return true;
        }
        next = s->getTop();
        if(next!= NULL && !onPath(s,next) && idaAux(next,step,cost+1,minThrow,solution)){
            solution.push_back(s);
            return true;
        }
        next = s->getBottom();
        if(next!= NULL && !onPath(s,next) && idaAux(next,step,cost+1,minThrow,solution)){
            solution.push_back(s);
            return true;
        }
        return false;
    }
}



/*
	Compares two states
	*@param State *s1:       stores state to be compared
            State *s2:       stores state to be compared
	*@return bool:           1 if both states are equal, 0 otherwise
*********************************************************/
bool SearchAlgorithms::compare(State *s1, State *s2){
    if(s1->getString() == s2->getString()){
        return true;
    }
    return false;
}


/*
	Checks if a state is already on the current path until the root
	*@param State *path:				indicates the state from where the path begins
			State *newState:			indicates the state to be inserted on the path
	*@return bool:                      0 if path until the root does not contain the newState, 1 otherwise
*********************************************************/
bool SearchAlgorithms::onPath(State *path, State *newState){
    if(path == NULL) // if path equals NULL, the search has found the root, therefore returning false
        return false;
    else{
        if(path->getString() == newState->getString())
            return true;
        else
            return onPath(path->getParent(), newState);
    }
}

strMethodStats SearchAlgorithms::buildStats(bool notFound, State * solution, int openNodesSize, int closedNodesSize, float time){
    strMethodStats answer;
    answer.notFound = notFound;

    answer.solution = solution;
    answer.openNodesSize = openNodesSize;
    answer.closedNodesSize = closedNodesSize;
    answer.time = time;

    answer.ramification = ((float) (openNodesSize + closedNodesSize)/(float) closedNodesSize);
    State * parent = solution->getParent();
    int counter = 1;
    while(parent != NULL){
        counter += 1;
        parent = parent->getParent();
    }
    answer.cost = counter;
    answer.depth = counter;

    return answer;
}

/*
	Print solution
	*@param State *path:     stores state to be printed and ancestors
	*@return void:           -
*********************************************************/
void SearchAlgorithms::printSolution(State* path){
    if(path->getParent()!=NULL)
        printSolution(path->getParent());
    path->print();
}

/*
	Heuristic function for a specific state (piecesOutOfPlace)
	*@param State *s:       contains the state to have its heuristic value calculated
	*@return int:           the heuristic value for a specific state
*********************************************************/
int SearchAlgorithms::h2(State* s){
    std::string stateString = s->getString();
    std::string goalString = goal->getString();
    int piecesOutOfPlace = 0;
    for(unsigned int i = 0 ; i<goalString.size();i++){
        if(stateString[i] != goalString[i]){
            piecesOutOfPlace++;
        }
    }
    return piecesOutOfPlace;
}

/*
	Heuristic function for a specific state (manhattanDistance)
	*@param State *s:       contains the state to have its heuristic value calculated
	*@return int:           the heuristic value for a specific state
*********************************************************/
int SearchAlgorithms::h1(State* s){
    int width = s->getWidth();
    std::string stateString = s->getString();
    std::string goalString = goal->getString();
    int manhattanDistance = 0;
    for(unsigned int i = 0 ; i<goalString.size();i++){
        for(unsigned int j = 0;j<stateString.size();j++){
            if(goalString[i]==stateString[j]){
                int iGoal,jGoal,iState,jState;
                iGoal = i/width;
                jGoal = i%width;
                iState = j/width;
                jState = j%width;
                manhattanDistance += abs(iGoal - iState)+abs(jGoal - jState);
                break;
            }
        }
    }
    return manhattanDistance;
}
