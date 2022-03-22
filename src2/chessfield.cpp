#include "chessfield.h"

Chessfield::Chessfield(int num, bool em, int col): number(num), empty(em), color(col)
{

}

bool Chessfield::isEmpty(){
    return empty;
}
void Chessfield::setEmpty(bool status){
    empty = status;
}
bool Chessfield::getColor(){
    return color;
}
void Chessfield::setColor(bool newColor){
    color = newColor;
}
int Chessfield::getNumber(){
    return number;
}
void Chessfield::setNumber(int num){
    number = num;
}
