#ifndef SEARCHALGORITHMS_H
#define SEARCHALGORITHMS_H
#include "State.h"
#include<string>
#include<vector>

class SearchAlgorithms{
    public:
        SearchAlgorithms(std::string initial,std::string goal);
        virtual ~SearchAlgorithms();
        void ida();
        void backtracking();

    protected:

    private:
        State* initial;
        State* goal;
        //Ida aux:
        bool idaAux(State* s,int step, int cost,int* minThrow, std::vector<State*> &solution);

        bool backtrackingAux(State *s, int cost, std::vector<State *> &solution);
        //Compare states:
        bool compare(State *s1, State *s2);

        bool onPath(State *s, State *nS);
        //Heuristic:
        int h1(State* s);
};

#endif // SEARCHALGORITHMS_H
