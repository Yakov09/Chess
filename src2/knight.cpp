#include "knight.h"
#include "chessboard.h"

Knight::Knight(Chessfield *myF, bool myC)
{
    myField = myF;
    color = myC;
    canJump = true;
    whiteImageName = "knight_w.png";
    blackImageName = "knight_b.png";
}

void Knight::changePosMove(Chessboard* board, int nextField){
    Piece* nextPiece = board->getPieceFromField(nextField);
    if(nextPiece == nullptr) posMoves[nextField] = 1; else
        if(board->getPieceFromField(nextField)->getColor() != color) posMoves[nextField] = 2;
}

void Knight::possiableMoves(Chessboard *board){
    setPosMovesFalse();
    if(board == nullptr) return;
    int myHorizon = myField->getNumber() / 8;
    int myVert = myField->getNumber() % 8;
    int nextField;
    if(myHorizon >= 2){
        if(myVert >=1){ nextField = myField->getNumber() - 17; changePosMove(board, nextField); }
        if(myVert <=6){ nextField = myField->getNumber() - 15;  changePosMove(board, nextField);  }
    }
    if(myHorizon >= 1){
        if(myVert >=2){ nextField = myField->getNumber() - 10;  changePosMove(board, nextField);}
        if(myVert <=5){ nextField = myField->getNumber() - 6;  changePosMove(board, nextField);}
    }
    if(myHorizon <= 6){
        if(myVert >=2){ nextField = myField->getNumber() + 6;  changePosMove(board, nextField); }
        if(myVert <=5){ nextField = myField->getNumber() + 10; changePosMove(board, nextField); }
    }
    if(myHorizon <= 5){
        if(myVert >=1){ nextField = myField->getNumber() + 15; changePosMove(board, nextField); }
        if(myVert <=6){  nextField = myField->getNumber() + 17;  changePosMove(board, nextField); }
    }
}
