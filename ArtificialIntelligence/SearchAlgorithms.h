#ifndef SEARCHALGORITHMS_H
#define SEARCHALGORITHMS_H
#include "State.h"
#include <time.h>
#include <string>
#include <vector>

typedef struct{
    bool notFound;
    State * solution;
    int depth;
    int cost;
    int openNodesSize;
    int closedNodesSize;
    float ramification;
    float time;
}strMethodStats;


class SearchAlgorithms{
    public:
        SearchAlgorithms(std::string initial,std::string goal, int width, int heigth);
        virtual ~SearchAlgorithms();
        strMethodStats greedy();
        strMethodStats astar();
        strMethodStats backtracking();
        strMethodStats depthSearch();
        strMethodStats breadthSearch();
        strMethodStats orderedSearch();
        strMethodStats ida();

        void printSolution(State* path);
        void printStats(strMethodStats stats, bool flag = false);
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
        bool onPath(State *s, State *nS);
        strMethodStats buildStats(bool notFound, State * solution, int openNodesSize, int closedNodesSize, float time);

        //Heuristics:
        int h1(State* s); //piecesOutOfPlace
        int h2(State* s); //manhattanDistance


};

#endif // SEARCHALGORITHMS_H
