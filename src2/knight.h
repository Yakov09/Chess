#ifndef KNIGHT_H
#define KNIGHT_H

#include "piece.h"

class Knight : public Piece
{
    void changePosMove(Chessboard* board, int nextField);
public:
    Knight(Chessfield *myF, bool myC);
    void possiableMoves(Chessboard* board);
};

#endif // KNIGHT_H
