#include "rook.h"

Rook::Rook(Chessfield *myF, bool myC)
{
    myField = myF;
    color = myC;
    whiteImageName = "rook_w.png";
    blackImageName = "rook_b.png";
    range = 7;
}

void Rook::possiableMoves(Chessboard *board){
    setPosMovesFalse();
    hvCheck(board);
}
