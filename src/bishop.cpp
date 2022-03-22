#include "bishop.h"

Bishop::Bishop(Chessfield *myF, bool myC)
{
    myField = myF;
    color = myC;
    whiteImageName = "bishop_w.png";
    blackImageName = "bishop_b.png";
    range = 7;
}

void Bishop::possiableMoves(Chessboard *board){
    setPosMovesFalse();
    diaCheck(board);
}
