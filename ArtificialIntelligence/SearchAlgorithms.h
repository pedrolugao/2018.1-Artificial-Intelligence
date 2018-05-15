#ifndef SEARCHALGORITHMS_H
#define SEARCHALGORITHMS_H
#include "State.h"
#include<string>
#include<vector>

class SearchAlgorithms{
    public:
        SearchAlgorithms(std::string initial,std::string goal);
        virtual ~SearchAlgorithms();
        void backtracking();
        void depthSearch();
        void orderedSearch();
        void ida();

    protected:

    private:
        State* initial;
        State* goal;

        //Search functions auxiliar:
        bool idaAux(State* s,int step, int cost,int* minThrow, std::vector<State*> &solution);
        bool backtrackingAux(State *s, int cost, std::vector<State *> &solution);

        //Compare states:
        bool compare(State *s1, State *s2);

        //Auxiliar functions
        void printSolution(State* path);
        bool onPath(State *s, State *nS);

        //Heuristics:
        int h1(State* s); //piecesOutOfPlace
};

#endif // SEARCHALGORITHMS_H
