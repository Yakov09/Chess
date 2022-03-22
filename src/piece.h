#ifndef PIECE_H
#define PIECE_H
#include "chessfield.h"
#include <string>
#include <iostream>

class Chessboard;
class Piece
{
protected:
    std::string path = "/home/yakov/Chess001/images";
    std::string whiteImageName = "";
    std::string blackImageName = "";
    bool color;                                                 // 0 - white, 1 - black
    Chessfield* myField;
    bool canJump = false;
    bool canTransform = false;
    int posMoves[64];                           // 0 - no move, 1 - can move, 2 - can take, 3 - make castle
    int range;
    void hvCheck(Chessboard* board);     // horizontal & vertical possible moves check
    void diaCheck(Chessboard* board);    // diagonal possible moves check
public:
    Piece();    
    virtual void possiableMoves(Chessboard* board) = 0;   // 0 - no move, 1 - can move, 2 - can take
    int checkPossibleMove(int field);
    void getPosMoves(int posM[64]);
    void setPosMovesFalse();
    Chessfield* getMyField();
    void setMyField(Chessfield* field);
    std::string getImagePath();
    void printPosMoves();
    bool getColor();
    void setCanTransform(bool status);
    bool getCanTrnsform();
};

#endif // PIECE_H
