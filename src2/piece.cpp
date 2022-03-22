#include "piece.h"
#include "chessboard.h"

Piece::Piece()
{
//    for(int i=0; i<15; ++i)
//        for(int j=0; j<15; ++j)
//            moveMatrix[i][j] = 0;
    setPosMovesFalse();
    range = 0;
}
void Piece::setPosMovesFalse(){
    for(int i=0; i<64; ++i) posMoves[i] = 0;
}

Chessfield* Piece::getMyField(){
    return myField;
}
std::string Piece::getImagePath(){
    std::string actualImage = (color == 0) ? whiteImageName : blackImageName;
    return path + "/" + actualImage;
}

void Piece::hvCheck(Chessboard* board = nullptr){
    if(board == nullptr) return;
    int myHorizon = myField->getNumber() / 8;
    int myVert = myField->getNumber() % 8;
    for(int i=myHorizon+1; i<8; ++i){
        if(i - myHorizon > range) break;
        int nextFieldNum = myVert + 8*i;
        Piece *nextPiece = board->getPieceFromField(nextFieldNum);
        if(nextPiece != nullptr)
            if(nextPiece->color != color) {posMoves[nextFieldNum] = 2; break;} else {posMoves[nextFieldNum] = 0; break;}
        else
            posMoves[nextFieldNum] = 1;
    }
    for(int i=myHorizon-1; i>=0; --i){
        if(myHorizon - i > range) break;
        int nextFieldNum = myVert + 8*i;
        Piece *nextPiece = board->getPieceFromField(nextFieldNum);
        if(nextPiece != nullptr)
            if(nextPiece->color != color) {posMoves[nextFieldNum] = 2; break;} else {posMoves[nextFieldNum] = 0; break;}
        else
            posMoves[nextFieldNum] = 1;
    }
    for(int i=myVert+1; i<8; ++i){
        if(i - myVert > range) break;
        int nextFieldNum = myHorizon*8 + i;
        Piece *nextPiece = board->getPieceFromField(nextFieldNum);
        if(nextPiece != nullptr)
            if(nextPiece->color != color) {posMoves[nextFieldNum] = 2; break;} else {posMoves[nextFieldNum] = 0; break;}
        else
            posMoves[nextFieldNum] = 1;
    }
    for(int i=myVert-1; i>=0; --i){
        if(myVert - i > range) break;
        int nextFieldNum = myHorizon*8 + i;
        Piece *nextPiece = board->getPieceFromField(nextFieldNum);
        if(nextPiece != nullptr)
            if(nextPiece->color != color) {posMoves[nextFieldNum] = 2; break;} else {posMoves[nextFieldNum] = 0; break;}
        else
            posMoves[nextFieldNum] = 1;
    }
}
void Piece::diaCheck(Chessboard* board = nullptr){
    if(board == nullptr) return;
    int myHorizon = myField->getNumber() / 8;
    int myVert = myField->getNumber() % 8;
    for(int i=1; (i+myHorizon<8)&&(i+myVert<8); ++i){
        if(i>range)break;
        int nextFieldNum = myField->getNumber() + 9*i;
        Piece *nextPiece = board->getPieceFromField(nextFieldNum);
        if(nextPiece != nullptr)
            if(nextPiece->color != color) {posMoves[nextFieldNum] = 2; break;} else {posMoves[nextFieldNum] = 0; break;}
        else
            posMoves[nextFieldNum] = 1;
    }

    for(int i=1; (myHorizon-i>=0)&&(myVert-i>=0); ++i){
        if(i>range)break;
        int nextFieldNum = myField->getNumber() - 9*i;
        Piece *nextPiece = board->getPieceFromField(nextFieldNum);
        if(nextPiece != nullptr)
            if(nextPiece->color != color) {posMoves[nextFieldNum] = 2; break;} else {posMoves[nextFieldNum] = 0; break;}
        else
            posMoves[nextFieldNum] = 1;
    }

    for(int i=1; (i+myHorizon<8)&&(myVert-i>=0); ++i){
        if(i>range)break;
        int nextFieldNum = myField->getNumber() + 7*i;
        Piece *nextPiece = board->getPieceFromField(nextFieldNum);
        if(nextPiece != nullptr)
            if(nextPiece->color != color) {posMoves[nextFieldNum] = 2; break;} else {posMoves[nextFieldNum] = 0; break;}
        else
            posMoves[nextFieldNum] = 1;
    }

    for(int i=1; (myHorizon-i>=0)&&(i+myVert<8); ++i){
        if(i>range)break;
        int nextFieldNum = myField->getNumber() - 7*i;
        Piece *nextPiece = board->getPieceFromField(nextFieldNum);
        if(nextPiece != nullptr)
            if(nextPiece->color != color) {posMoves[nextFieldNum] = 2; break;} else {posMoves[nextFieldNum] = 0; break;}
        else
            posMoves[nextFieldNum] = 1;
    }
}

void Piece::printPosMoves(){
    std::cout << "\n My position: " << getMyField()->getNumber() << "\n";
    for(int i=7; i>=0; --i){
        for(int j=0; j<8; ++j){
            std::cout << posMoves[i*8 + j] << " ";
        }
        std::cout << "\n";
    }
}

void Piece::getPosMoves(int *posM){
    for(int i=0; i<64; ++i) posM[i] = posMoves[i];
}

bool Piece::getColor(){
    return color;
}

int Piece::checkPossibleMove(int field){
    if((field < 0)||(field > 63)) return 0;
    return posMoves[field];
}

void Piece::setMyField(Chessfield* field){
    if((field->getNumber() < 0)||(field->getNumber() > 63)) return;
    myField = field;
}

void Piece::setCanTransform(bool status){
    canTransform = status;
}

bool Piece::getCanTrnsform(){
    return canTransform;
}
