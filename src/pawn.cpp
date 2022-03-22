#include "pawn.h"
#include "chessboard.h"

Pawn::Pawn(Chessfield *myF, bool myC)
{
    myField = myF;
    color = myC;
    whiteImageName = "pawn_w.png";
    blackImageName = "pawn_b.png";
    canTransform = true;
}

void Pawn::possiableMoves(Chessboard *board){
    setPosMovesFalse();
    int direction = 0;
    if(color == 0) direction = 1; else direction = -1;
    int myHorizon = myField->getNumber() / 8;
    int myVert = myField->getNumber() % 8;
    Piece* nextPiece = nullptr;
    int nextField;
    if((myHorizon < 7) && (myHorizon > 0)){
        nextField = myField->getNumber() + 8*direction;
        if(board->getPieceFromField(nextField) == nullptr) posMoves[nextField] = 1;
    }
    if(((myHorizon == 1)&&(direction == 1)) || ((myHorizon == 6)&&(direction == -1))) {
        nextField = myField->getNumber() + 16*direction;
        if(board->getPieceFromField(nextField) == nullptr) posMoves[nextField] = 1;
    }
    if(myVert > 0){
        nextField = myField->getNumber() + 8*direction - 1;
        nextPiece = board->getPieceFromField(nextField);
        if(nextPiece != nullptr)
            if(nextPiece->getColor() != color)
                posMoves[nextField] = 2;
    }
    if(myVert < 7){
        nextField = myField->getNumber() + 8*direction + 1;
        nextPiece = board->getPieceFromField(nextField);
        if(nextPiece != nullptr)
            if(nextPiece->getColor() != color)
                posMoves[nextField] = 2;
    }
}
