#include "State.h"
#include <stdlib.h>
#include <iostream>
#include <sstream>

State::State(std::string info){
    parent = NULL;
    for(int k = 0; k < info.size(); k++){
        const char buffer = info[k];
        matrix[k/3][k%3] = atoi(&buffer);
        if(buffer == '0'){
            i = k/3;
            j = k%3;
        }
    }
}

State::~State(){

}

void State::print(){
    std::cout << "Coordinate: (" << i << "," << j << ")" << std::endl;
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            std::cout << matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

State * State::getLeft(){
    if(j == 0){
        return NULL;
    }
    State * newState = new State(getString());
    newState->changeLeft();
    return newState;
}

void State::changeLeft(){
    int aux = matrix[i][j-1];
    matrix[i][j-1] = matrix[i][j];
    matrix[i][j] = aux;
    j = j - 1;
}

State * State::getRight(){
    if(j == 2){
        return NULL;
    }
    State * newState = new State(getString());
    newState->changeRight();
    return newState;

}

void State::changeRight(){
    int aux = matrix[i][j+1];
    matrix[i][j+1] = matrix[i][j];
    matrix[i][j] = aux;
    j = j + 1;
}

State * State::getTop(){
    if(i == 0){
        return NULL;
    }
    State * newState = new State(getString());
    newState->changeTop();
    return newState;
}

void State::changeTop(){
    int aux = matrix[i-1][j];
    matrix[i-1][j] = matrix[i][j];
    matrix[i][j] = aux;
    i = i - 1;
}

State * State::getBottom(){
    if(i == 2){
        return NULL;
    }
    State * newState = new State(getString());
    newState->changeBottom();
    return newState;

}

void State::changeBottom(){
    int aux = matrix[i+1][j];
    matrix[i+1][j] = matrix[i][j];
    matrix[i][j] = aux;
    i = i + 1;
}

std::string State::getString(){
    std::stringstream mstring;
    for(int a = 0; a < 3; a++){
        for(int b = 0; b < 3; b++){
            mstring << matrix[a][b];
        }
    }
    return mstring.str();
}

State * State::getParent(){
    return parent;
}

void State::setParent(State *nParent){
    parent = nParent;
}
