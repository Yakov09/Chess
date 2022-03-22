#ifndef KING_H
#define KING_H

#include "piece.h"

class King : public Piece
{
    bool movedAlready = false;
    bool checked = false;
public:
    King(Chessfield *myF, bool myC);
    void setMovedAlready(bool moved);
    bool getMovedAlready();    
    void possiableMoves(Chessboard* board);
};

#endif // KING_H
