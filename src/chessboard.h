#ifndef CHESSBOARD_H
#define CHESSBOARD_H
#include "chessfield.h"
#include "piece.h"
#include "bishop.h"
#include "king.h"
#include "knight.h"
#include "pawn.h"
#include "queen.h"
#include "rook.h"

class Chessboard
{
    static const int MAX_PIECES = 32;
    Chessfield *field[64];
    Piece *placedPieces[MAX_PIECES];
    bool moveOrder = 0; // 0 - white, 1 - black
    bool BlackCK = true;
    bool BlackCQ = true;
    bool WhiteCK = true;
    bool WhiteCQ = true;
    bool PieceChosen = false;
    Piece* chosenPiece = nullptr;
    int whiteKingSlot;
    int blackKingSlot;
    int win = 0;
public:    
    Chessboard();    
    void makeMove(int field);
    int setPiece(Piece** pieceSlot, Piece* piecePlaced, Chessfield fieldPlaced);  // 0 - Ok, 1 - field is not empty, 2 - other fails
    void deletePiece(int slot);
    void deletePiece(Piece* delPiece);
    void transformPiece(Piece* transPiece);
    void clearBoard();
    void setInintPosition();
    Piece* getPieceFromField(int aimField);
    void setMoveOrder(bool order);
    bool getMoveOrder();
    bool getFieldColor(int fieldNum);
    ~Chessboard();
    bool isChosenPiece();
    void setChosenPiece(bool status, Piece* actPiece);
    Piece* getChosenPiece();
    Chessfield* getField(int fieldNum);

    bool isBlackCK();   // CK - castle kingside
    bool isBlackCQ();   // CQ - castle queenside
    bool isWhiteCK();
    bool isWhiteCQ();
    void checkCastle();
    void lockBlackCastle();
    void lockWhiteCastle();
    int getWin();       // 0 - no win, 1 - white wins, 2 - black wins
    void checkWin();

    // positions for tests
    void setTestPos_1();
    void setTestPos_2();

};

#endif // CHESSBOARD_H
