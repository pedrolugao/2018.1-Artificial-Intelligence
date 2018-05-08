#ifndef SEARCHALGORITHMS_H
#define SEARCHALGORITHMS_H
#include "State.h"


class SearchAlgorithms{
    public:
        SearchAlgorithms();
        virtual ~SearchAlgorithms();

    protected:

    private:
        State initial;
        State goal;
};

#endif // SEARCHALGORITHMS_H
