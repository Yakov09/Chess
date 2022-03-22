#include "king.h"
#include "chessboard.h"

King::King(Chessfield *myF, bool myC)
{
    myField = myF;
    color = myC;
    whiteImageName = "king_w.png";
    blackImageName = "king_b.png";
    range = 1;
}

void King::possiableMoves(Chessboard *board){
    setPosMovesFalse();
    hvCheck(board);
    diaCheck(board);

    if(color == 0)
    {
        if((board->isWhiteCK())&&(board->getPieceFromField(5)==nullptr)&&(board->getPieceFromField(6)==nullptr))posMoves[6] = 3;
        if((board->isWhiteCQ())&&(board->getPieceFromField(1)==nullptr)&&(board->getPieceFromField(2)==nullptr)&&
                (board->getPieceFromField(3)==nullptr))posMoves[2] = 3;
    }
    if(color == 1)
    {
        if((board->isBlackCK())&&(board->getPieceFromField(61)==nullptr)&&(board->getPieceFromField(62)==nullptr))posMoves[62] = 3;
        if((board->isBlackCQ())&&(board->getPieceFromField(59)==nullptr)&&(board->getPieceFromField(58)==nullptr)&&
                (board->getPieceFromField(57)==nullptr))posMoves[58] = 3;
    }
}
