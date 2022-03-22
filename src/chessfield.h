#ifndef CHESSFIELD_H
#define CHESSFIELD_H

class Chessfield
{
    int number;
    bool empty;
    bool color;  // 0 - white, 1 - black
public:
    Chessfield(int num, bool em, int col);
    bool isEmpty();
    void setEmpty(bool status);
    bool getColor();
    void setColor(bool newColor);
    int getNumber();
    void setNumber(int num);
};

#endif // CHESSFIELD_H
