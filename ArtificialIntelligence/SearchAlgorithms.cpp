#include "SearchAlgorithms.h"
#include<vector>
#include<string>

#define INFINITY 9999

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

//IDA*
//Using order: left, rigth, top, bottom
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
//END IDA*


int SearchAlgorithms::h1(State* s){
    if(compare(s,goal)){
        return 0;
    }
    return 1;
}

bool SearchAlgorithms::compare(State *s1, State *s2){
    if(s1->getString() == s2->getString()){
        return true;
    }
    return false;
}
