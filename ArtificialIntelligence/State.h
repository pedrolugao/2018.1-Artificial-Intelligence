#ifndef STATE_H
#define STATE_H
#include <string>
#include <vector>

class State{
    public:
        State(std::string info);
        virtual ~State();
        void print();

        State * getLeft();
        State * getRight();
        State * getTop();
        State * getBottom();

        void changeLeft();
        void changeRight();
        void changeTop();
        void changeBottom();

    protected:

    private:
        int matrix[3][3];
        int i, j;
        std::string getString();

};

#endif // STATE_H
