#include "State.h"
#include <stdlib.h>
#include <iostream>
#include <sstream>


State::State(std::string info, int width, int heigth){
    this->width = width;
    this->heigth = heigth;
    this->parent = NULL;
    matrix = new char* [heigth];
    for(unsigned int j = 0;j<heigth;j++){
        matrix[j] = new char [width];
    }
    for(int k = 0; k < info.size(); k++){
        char buffer = info[k];
        matrix[k/width][k%width] = buffer;
        if(buffer == '0'){
            i = k/width;
            j = k%width;
        }
    }
}

State::~State(){
    for(unsigned int j = 0;j<heigth;j++){
        delete[] matrix[j];
    }
    delete[] matrix;
}

void State::print(){
    std::cout << "Coordinate: (" << i << "," << j << ")" << std::endl;
    for(int i = 0; i < heigth; i++){
        for(int j = 0; j < width; j++){
            std::cout << matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

State * State::getLeft(){
    if(j == 0){
        return NULL;
    }
    State * newState = new State(getString(),this->width,this->heigth);
    newState->changeLeft();
    newState->setParent(this);
    return newState;
}

void State::changeLeft(){
    int aux = matrix[i][j-1];
    matrix[i][j-1] = matrix[i][j];
    matrix[i][j] = aux;
    j = j - 1;
}

State * State::getRight(){
    if(j == width-1){
        return NULL;
    }
    State * newState = new State(getString(),this->width,this->heigth);
    newState->changeRight();
    newState->setParent(this);
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
    State * newState = new State(getString(),this->width,this->heigth);
    newState->changeTop();
    newState->setParent(this);
    return newState;
}

void State::changeTop(){
    int aux = matrix[i-1][j];
    matrix[i-1][j] = matrix[i][j];
    matrix[i][j] = aux;
    i = i - 1;
}

State * State::getBottom(){
    if(i == heigth-1){
        return NULL;
    }
    State * newState = new State(getString(),this->width,this->heigth);
    newState->changeBottom();
    newState->setParent(this);
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
    for(int a = 0; a < heigth; a++){
        for(int b = 0; b < width; b++){
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

int State::getWidth(){
    return width;
}

int State::getHeigth(){
    return heigth;
}
