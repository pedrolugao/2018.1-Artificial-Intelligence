#include "SearchAlgorithms.h"
#include<vector>
#include<string>
#include <stdio.h>

#define INFINITY 9999

/*
    Constructor of SearchAlgorithm class
	*@param std::string initialString:	specifies the initial state
            std::string goalString:     specifies the goal state
	*@return -
*********************************************************/
SearchAlgorithms::SearchAlgorithms(std::string initialString,std::string goalString){
    //ctor
    initial = new State(initialString);
    goal = new State(goalString);
    //initial->print();
    //goal->print();
}

SearchAlgorithms::~SearchAlgorithms(){
    //dtor
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

/*
	Runs the backtracking search method
	*@param -
	*@return void: -
*********************************************************/
void SearchAlgorithms::backtracking(){
    std::vector<State*> solution;
    if(backtrackingAux(initial, 0, solution)){
        printf("Solution found!\n");
        for(int i = (solution.size()-1);i>=0;i--){
            solution[i]->print();
        }
    }else{
        printf("Solution not found!\n");
    }
}

/*
	Recursive auxiliar function for the backtracking search method
	ORDER: left, rigth, top, bottom
	*@param State *s:           indicates the state from where the path begins
            int cost:           indicates the cost from the path
			std::vector<State*>	stores the current solution
	*@return bool:              1 if the goal was found, 0 otherwise
*********************************************************/
bool SearchAlgorithms::backtrackingAux(State *s, int cost, std::vector<State*> &solution){
    if(compare(s, goal)){
        solution.push_back(s);
        return true;
    }else{
        State * next = s->getLeft();
        if(next != NULL){
            next->setParent(s);
            if(!onPath(s, next) && backtrackingAux(next, cost + 1, solution)){
                solution.push_back(s);
                return true;
            }
        }
        next = s->getRight();
        if(next != NULL){
            next->setParent(s);
            if(!onPath(s, next) && backtrackingAux(next, cost + 1, solution)){
                solution.push_back(s);
                return true;
            }
        }
        next = s->getTop();
        if(next != NULL){
            next->setParent(s);
            if(!onPath(s, next) && backtrackingAux(next, cost + 1, solution)){
                solution.push_back(s);
                return true;
            }
        }
        next = s->getBottom();
        if(next != NULL){
            next->setParent(s);
            if(!onPath(s, next) && backtrackingAux(next, cost + 1, solution)){
                solution.push_back(s);
                return true;
            }
        }
    }
    return false;
}

/*
	Runs the IDA* search method
	*@param -
	*@return void: -
*********************************************************/
void SearchAlgorithms::ida(){
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
    if(success){
        printf("Solution found!\n");
        int i;
        for(i = (solution.size()-1);i>=0;i--){
            solution[i]->print();
        }
        //Print solution backwards
    }else{
        printf("Solution not found!");
    }

}

/*
	Recursive auxiliar function for the IDA* search method
	ORDER: left, rigth, top, bottom
	*@param State *s:           indicates the state from where the path begins
            int step:           stores the maximun step for a specific run
            int cost:           indicates the cost from the path
			std::vector<State*>	stores the current solution
	*@return bool:              1 if the goal was found, 0 otherwise
*********************************************************/
bool SearchAlgorithms::idaAux(State* s,int step, int cost,int *minThrow, std::vector<State*> &solution){
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
        if(next!= NULL && idaAux(next,step,cost+1,minThrow,solution)){
            solution.push_back(s);
            return true;
        }
        next = s->getRight();
        if(next!= NULL && idaAux(next,step,cost+1,minThrow,solution)){
            solution.push_back(s);
            return true;
        }
        next = s->getTop();
        if(next!= NULL && idaAux(next,step,cost+1,minThrow,solution)){
            solution.push_back(s);
            return true;
        }
        next = s->getBottom();
        if(next!= NULL && idaAux(next,step,cost+1,minThrow,solution)){
            solution.push_back(s);
            return true;
        }
        return false;
    }
}

/*
	Heuristic function for a specific state
	*@param State *s:       contains the state to have its heuristic value calculated
	*@return int:           the heuristic value for a specific state
*********************************************************/
int SearchAlgorithms::h1(State* s){
    if(compare(s,goal)){
        return 0;
    }
    return 1;
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
