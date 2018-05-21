#ifndef STATE_H
#define STATE_H
#include <string>
#include <vector>

class State{
    public:
        State(std::string info, int width, int heigth);
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

        int getWidth();
        int getHeigth();

    protected:

    private:
        int width,heigth;
        char **matrix;
        int i, j;
        State * parent;


};

#endif // STATE_H
