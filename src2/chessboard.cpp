#include "chessboard.h"
#include <iostream>
Chessboard::Chessboard()
{
    for(int i=0; i<64; ++i){
        field[i] = new Chessfield(i, true, (i+i/8)%2);
    }
    for(int i=0; i<MAX_PIECES; ++i)
        placedPieces[i] = nullptr;
}

bool Chessboard::getFieldColor(int fieldNum){
    return field[fieldNum]->getColor();
}

int Chessboard::setPiece(Piece **pieceSlot, Piece *piecePlaced, Chessfield fieldPlaced){
    if(fieldPlaced.isEmpty() != true) return 1;
    *pieceSlot = piecePlaced;
    fieldPlaced.setEmpty(false);
    return 0;
}

void Chessboard::clearBoard(){
    for(int i=0; i<MAX_PIECES; ++i){
        deletePiece(i);
        placedPieces[i] = nullptr;
    }
}
void Chessboard::setInintPosition(){
    clearBoard();    
    placedPieces[0] = new Rook(field[0], 0);
    placedPieces[1] = new Knight(field[1], 0);
    placedPieces[2] = new Bishop(field[2], 0);
    placedPieces[3] = new Queen(field[3], 0);
    placedPieces[4] = new King(field[4], 0); whiteKingSlot = 4;
    placedPieces[5] = new Bishop(field[5], 0);
    placedPieces[6] = new Knight(field[6], 0);
    placedPieces[7] = new Rook(field[7], 0);
    for(int i = 8;i<16;++i) placedPieces[i] = new Pawn(field[i], 0);
    for(int i = 16;i<24;++i) placedPieces[i] = new Pawn(field[i+32], 1);
    placedPieces[24] = new Rook(field[56], 1);
    placedPieces[25] = new Knight(field[57], 1);
    placedPieces[26] = new Bishop(field[58], 1);
    placedPieces[27] = new Queen(field[59], 1);
    placedPieces[28] = new King(field[60], 1); blackKingSlot = 28;
    placedPieces[29] = new Bishop(field[61], 1);
    placedPieces[30] = new Knight(field[62], 1);
    placedPieces[31] = new Rook(field[63], 1);
}
void Chessboard::deletePiece(int slot){
    if((slot < 0)||(slot >= MAX_PIECES)) return;
    if(placedPieces[slot] != nullptr) placedPieces[slot]->~Piece();
    placedPieces[slot] = nullptr;
}
void Chessboard::deletePiece(Piece *delPiece){
    int slot = MAX_PIECES;
    for(int i=0; i<MAX_PIECES; ++i) if(placedPieces[i] == delPiece) slot = i;
    if(slot == MAX_PIECES) return;
    delPiece->~Piece();
    placedPieces[slot] = nullptr;
}
void Chessboard::transformPiece(Piece *transPiece){
    bool color = transPiece->getColor();                                                 // 0 - white, 1 - black
    Chessfield* myField = transPiece->getMyField();
    int slot = MAX_PIECES;
    for(int i=0; i<MAX_PIECES; ++i) if(placedPieces[i] == transPiece) slot = i;
    if(slot == MAX_PIECES) return;
    transPiece->~Piece();
    placedPieces[slot] = new Queen(myField, color);
}


Piece* Chessboard::getPieceFromField(int aimField){
    for(int i=0; i<MAX_PIECES; ++i){
        if(placedPieces[i] == nullptr) continue;
        if(placedPieces[i]->getMyField() == field[aimField]) return placedPieces[i];
    }
    return nullptr;
}
bool Chessboard::isChosenPiece(){ return PieceChosen;}

void Chessboard::setChosenPiece(bool status, Piece* actPiece = nullptr){
    chosenPiece = actPiece;
    if(!status) chosenPiece = nullptr;
    PieceChosen = status;
}

Piece* Chessboard::getChosenPiece(){
    return chosenPiece;
}

void Chessboard::setMoveOrder(bool order){moveOrder = order;}

bool Chessboard::getMoveOrder(){return moveOrder;}

Chessfield* Chessboard::getField(int fieldNum){
    if((fieldNum < 0)||(fieldNum > 63)) return nullptr;
    return field[fieldNum];
}

bool Chessboard::isBlackCK(){ return BlackCK;}
bool Chessboard::isBlackCQ(){ return BlackCQ;}
bool Chessboard::isWhiteCK(){ return WhiteCK;}
bool Chessboard::isWhiteCQ(){ return WhiteCQ;}

void Chessboard::checkCastle(){
    if(getPieceFromField(4)==nullptr) {WhiteCK = false; WhiteCQ = false;}
    if(getPieceFromField(0)==nullptr) WhiteCQ = false; else if(getPieceFromField(0)->getColor()!=0) WhiteCQ = false;
    if(getPieceFromField(7)==nullptr) WhiteCK = false; else if(getPieceFromField(7)->getColor()!=0) WhiteCK = false;
    if(getPieceFromField(56)==nullptr) {BlackCK = false; BlackCQ = false;}
    if(getPieceFromField(60)==nullptr) BlackCQ = false; else if(getPieceFromField(60)->getColor()!=1) BlackCQ = false;
    if(getPieceFromField(63)==nullptr) BlackCK = false; else if(getPieceFromField(63)->getColor()!=1) BlackCK = false;
}
void Chessboard::lockBlackCastle(){
    BlackCK = false;
    BlackCQ = false;
}
void Chessboard::lockWhiteCastle(){
    WhiteCK = false;
    WhiteCQ = false;
}

void Chessboard::makeMove(int field){
    Piece* chosenPiece = getChosenPiece();
    Piece* activePiece = getPieceFromField(field);
    if(chosenPiece->checkPossibleMove(field) == 2){         // if takes
        deletePiece(activePiece);
    }
    if(chosenPiece->checkPossibleMove(field) != 3) {        // if regular move
        chosenPiece->setMyField(getField(field));
        bool whiteAt7 = (chosenPiece->getMyField()->getNumber()/8 == 7)&&(chosenPiece->getColor()==0);
        bool blackAt0 = (chosenPiece->getMyField()->getNumber()/8 == 0)&&(chosenPiece->getColor()==1);
        if((chosenPiece->getCanTrnsform() == true)&&(whiteAt7 || blackAt0)){    // transform pawn into queen
            transformPiece(chosenPiece);
        }
        setChosenPiece(false, nullptr);
    }
    if(chosenPiece->checkPossibleMove(field) == 3){         // if castle
        chosenPiece->setMyField(getField(field));
        if(field == 62){            // black CK
            getPieceFromField(63)->setMyField(getField(61));
            lockBlackCastle();
        }
        if(field == 58){            // black CQ
            getPieceFromField(56)->setMyField(getField(59));
            lockBlackCastle();
        }
        if(field == 6){            // white CK
            getPieceFromField(7)->setMyField(getField(5));
            lockWhiteCastle();
        }
        if(field == 2){            // white CQ
            getPieceFromField(0)->setMyField(getField(3));
            lockWhiteCastle();
        }
        setChosenPiece(false, nullptr);
    }
    setMoveOrder(!getMoveOrder());
    checkCastle();
}

void Chessboard::checkWin(){
    if(placedPieces[whiteKingSlot] == nullptr) win =  2;
    if(placedPieces[blackKingSlot] == nullptr) win =  1;
}
int Chessboard::getWin(){
    return win;
}


void Chessboard::setTestPos_1(){
    clearBoard();
    placedPieces[0] = new Rook(field[0], 0);
    placedPieces[1] = new Knight(field[1], 0);
    placedPieces[2] = new Bishop(field[2], 0);
    placedPieces[3] = new Queen(field[3], 0);
    placedPieces[4] = new King(field[4], 0); whiteKingSlot = 4;
    //placedPieces[5] = new Bishop(field[5], 0);
    //placedPieces[6] = new Knight(field[6], 0);
    placedPieces[7] = new Rook(field[7], 0);
    //for(int i = 8;i<16;++i) placedPieces[i] = new Pawn(field[i], 0);
    for(int i = 16;i<24;++i) placedPieces[i] = new Pawn(field[i+6], 1);
    //placedPieces[24] = new Rook(field[56], 1);
    placedPieces[25] = new Knight(field[57], 1);
    placedPieces[26] = new Bishop(field[58], 1);
    placedPieces[27] = new Queen(field[59], 1);
    placedPieces[28] = new King(field[60], 1); blackKingSlot = 28;
    //placedPieces[29] = new Bishop(field[61], 1);
    //placedPieces[30] = new Knight(field[62], 1);
    //placedPieces[31] = new Rook(field[63], 1);
}
void Chessboard::setTestPos_2(){
    clearBoard();
    //placedPieces[0] = new Rook(field[0], 0);
    //placedPieces[1] = new Knight(field[1], 0);
    //placedPieces[2] = new Bishop(field[2], 0);
    placedPieces[3] = new Queen(field[23], 0);
    placedPieces[4] = new King(field[4], 0); whiteKingSlot = 4;
    placedPieces[5] = new Bishop(field[25], 0);
    placedPieces[6] = new Knight(field[26], 0);
    placedPieces[7] = new Rook(field[27], 0);
    for(int i = 8;i<16;++i) placedPieces[i] = new Pawn(field[i], 0);
    for(int i = 16;i<24;++i) placedPieces[i] = new Pawn(field[i+32], 1);
    //placedPieces[24] = new Rook(field[56], 1);
    //placedPieces[25] = new Knight(field[57], 1);
    //placedPieces[26] = new Bishop(field[58], 1);
    placedPieces[27] = new Queen(field[39], 1);
    placedPieces[28] = new King(field[60], 1); blackKingSlot = 28;
    placedPieces[29] = new Bishop(field[31], 1);
    placedPieces[30] = new Knight(field[32], 1);
    placedPieces[31] = new Rook(field[33], 1);
}

