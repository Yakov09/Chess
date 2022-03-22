#include "queen.h"

Queen::Queen(Chessfield *myF, bool myC)
{
    myField = myF;
    color = myC;
    whiteImageName = "queen_w.png";
    blackImageName = "queen_b.png";
    range = 7;
}

void Queen::possiableMoves(Chessboard *board){
    setPosMovesFalse();
    hvCheck(board);
    diaCheck(board);
}
