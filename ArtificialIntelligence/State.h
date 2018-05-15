#ifndef STATE_H
#define STATE_H
#include <string>
#include <vector>

class State{
    public:
        State(std::string info);
        virtual ~State();
        void print();
        std::string getString();

        State * getLeft();
        State * getRight();
        State * getTop();
        State * getBottom();

        void changeLeft();
        void changeRight();
        void changeTop();
        void changeBottom();

        State * getParent();
        void setParent(State *nParent);


    protected:

    private:
        int matrix[3][3];
        int i, j;
        State * parent;


};

#endif // STATE_H
