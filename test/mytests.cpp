#include <stdlib.h>
#include "ctest.h"
#include "chessboard.h"


CTEST(testChessboard, clearBoard) {
    Chessboard* testChessboard = new Chessboard;
    testChessboard->setTestPos_1();
    testChessboard->clearBoard();
    int foundedPieces = 0;
    for(int i=0; i<64; ++i){
        if(testChessboard->getPieceFromField(i) != nullptr) foundedPieces++;
    }
    ASSERT_EQUAL(foundedPieces, 0);
    testChessboard->setTestPos_2();
    testChessboard->clearBoard();
    foundedPieces = 0;
    for(int i=0; i<64; ++i){
        if(testChessboard->getPieceFromField(i) != nullptr) foundedPieces++;
    }
    ASSERT_EQUAL(foundedPieces, 0);
}

CTEST(testChessboard, setInintPosition) {
    Chessboard* testChessboard = new Chessboard;
    testChessboard->setInintPosition();
    int wrongFieldEmptiness = 0;
    for(int i=0; i<16; ++i) if(testChessboard->getPieceFromField(i)==nullptr) wrongFieldEmptiness++;
    for(int i=16; i<48; ++i) if(testChessboard->getPieceFromField(i)!=nullptr) wrongFieldEmptiness++;
    for(int i=48; i<64; ++i) if(testChessboard->getPieceFromField(i)==nullptr) wrongFieldEmptiness++;
    ASSERT_EQUAL(wrongFieldEmptiness, 0);
}

CTEST(testChessboard, getPieceFromField) {
    Chessboard* testChessboard = new Chessboard;
    testChessboard->setInintPosition();
    Piece* Piece_6 = testChessboard->getPieceFromField(6);
    testChessboard->clearBoard();
    bool PieceToNull = (Piece_6 != nullptr)&&(testChessboard->getPieceFromField(6) == nullptr);
    ASSERT_EQUAL(PieceToNull, true);
}

CTEST(testChessboard, deletePiece) {
    Chessboard* testChessboard = new Chessboard;
    testChessboard->setInintPosition();
    testChessboard->deletePiece(3);
    bool eq = (testChessboard->getPieceFromField(3)==nullptr) ? true : false;
    ASSERT_EQUAL(eq, true);
}

CTEST(testBishop, possiableMoves) {
    Chessboard* testChessboard = new Chessboard;
    testChessboard->setTestPos_1();
    Piece* testPiece = testChessboard->getPieceFromField(2);
    if(testPiece == nullptr) return;
    int testAvMoves[64];
    int posMoves[64];
    int difAvMoves = 0;
    for(int i=0; i<64; ++i) testAvMoves[i] = 0;
    testAvMoves[9] = 1; testAvMoves[11] = 1; testAvMoves[16] = 1; testAvMoves[20] = 1;
    testAvMoves[29] = 2;
    testPiece->possiableMoves(testChessboard);
    testPiece->getPosMoves(posMoves);
    for(int i=0; i<64; ++i) if(posMoves[i] != testAvMoves[i]) difAvMoves++;
    ASSERT_EQUAL(difAvMoves, 0);
    testChessboard->setTestPos_2();
    testPiece = testChessboard->getPieceFromField(25);
    if(testPiece == nullptr) return;
    for(int i=0; i<64; ++i) testAvMoves[i] = 0;
    testAvMoves[16] = 1; testAvMoves[18] = 1; testAvMoves[32] = 2; testAvMoves[34] = 1;
    testAvMoves[43] = 1; testAvMoves[52] = 2;
    difAvMoves = 0;
    testPiece->possiableMoves(testChessboard);
    testPiece->getPosMoves(posMoves);
    for(int i=0; i<64; ++i) if(posMoves[i] != testAvMoves[i]) difAvMoves++;
    ASSERT_EQUAL(difAvMoves, 0);
}

CTEST(testKing, possiableMoves) {
    Chessboard* testChessboard = new Chessboard;
    testChessboard->setTestPos_1();
    Piece* testPiece = testChessboard->getPieceFromField(4);
    if(testPiece == nullptr) return;
    int testAvMoves[64];
    int posMoves[64];
    int difAvMoves = 0;
    for(int i=0; i<64; ++i) testAvMoves[i] = 0;
    testAvMoves[5] = 1; testAvMoves[6] = 3; testAvMoves[11] = 1; testAvMoves[12] = 1;
    //testAvMoves[13] = 1;
    testPiece->possiableMoves(testChessboard);
    testPiece->getPosMoves(posMoves);
    for(int i=0; i<64; ++i) if(posMoves[i] != testAvMoves[i]) difAvMoves++;
    ASSERT_EQUAL(difAvMoves, 0);

    testChessboard->setTestPos_2();
    testChessboard->lockBlackCastle();
    testChessboard->lockWhiteCastle();
    testPiece = testChessboard->getPieceFromField(4);
    if(testPiece == nullptr) return;
    for(int i=0; i<64; ++i) testAvMoves[i] = 0;
    testAvMoves[3] = 1; testAvMoves[5] = 1;
    difAvMoves = 0;
    testPiece->possiableMoves(testChessboard);
    testPiece->getPosMoves(posMoves);
    for(int i=0; i<64; ++i) if(posMoves[i] != testAvMoves[i]) difAvMoves++;
    ASSERT_EQUAL(difAvMoves, 0);
}

CTEST(testKnight, possiableMoves) {
    Chessboard* testChessboard = new Chessboard;
    testChessboard->setTestPos_1();
    Piece* testPiece = testChessboard->getPieceFromField(1);
    if(testPiece == nullptr) return;
    int testAvMoves[64];
    int posMoves[64];
    int difAvMoves = 0;
    for(int i=0; i<64; ++i) testAvMoves[i] = 0;
    testAvMoves[11] = 1; testAvMoves[16] = 1; testAvMoves[18] = 1;
    testPiece->possiableMoves(testChessboard);
    testPiece->getPosMoves(posMoves);
    for(int i=0; i<64; ++i) if(posMoves[i] != testAvMoves[i]) difAvMoves++;
    ASSERT_EQUAL(difAvMoves, 0);

    testChessboard->setTestPos_2();
    testPiece = testChessboard->getPieceFromField(26);
    if(testPiece == nullptr) return;
    for(int i=0; i<64; ++i) testAvMoves[i] = 0;
    testAvMoves[16] = 1; testAvMoves[20] = 1; testAvMoves[32] = 2; testAvMoves[36] = 1;
    testAvMoves[41] = 1; testAvMoves[43] = 1;
    difAvMoves = 0;
    testPiece->possiableMoves(testChessboard);
    testPiece->getPosMoves(posMoves);
    for(int i=0; i<64; ++i) if(posMoves[i] != testAvMoves[i]) difAvMoves++;
    ASSERT_EQUAL(difAvMoves, 0);

}

CTEST(testPawn, possiableMoves) {
    Chessboard* testChessboard = new Chessboard;
    testChessboard->setTestPos_1();
    testChessboard->setMoveOrder(!testChessboard->getMoveOrder());
    Piece* testPiece = testChessboard->getPieceFromField(26);
    if(testPiece == nullptr) return;
    int testAvMoves[64];
    int posMoves[64];
    int difAvMoves = 0;
    for(int i=0; i<64; ++i) testAvMoves[i] = 0;
    testAvMoves[18] = 1;
    testPiece->possiableMoves(testChessboard);
    testPiece->getPosMoves(posMoves);
    for(int i=0; i<64; ++i) if(posMoves[i] != testAvMoves[i]) difAvMoves++;
    ASSERT_EQUAL(difAvMoves, 0);

    testChessboard->setTestPos_2();
    testPiece = testChessboard->getPieceFromField(12);
    if(testPiece == nullptr) return;
    for(int i=0; i<64; ++i) testAvMoves[i] = 0;
    testAvMoves[20] = 1; testAvMoves[28] = 1;
    difAvMoves = 0;
    testPiece->possiableMoves(testChessboard);
    testPiece->getPosMoves(posMoves);
    for(int i=0; i<64; ++i) if(posMoves[i] != testAvMoves[i]) difAvMoves++;
    ASSERT_EQUAL(difAvMoves, 0);
}

CTEST(testQueen, possiableMoves) {
    Chessboard* testChessboard = new Chessboard;
    testChessboard->setTestPos_1();
    Piece* testPiece = testChessboard->getPieceFromField(3);
    if(testPiece == nullptr) return;
    int testAvMoves[64];
    int posMoves[64];
    int difAvMoves = 0;
    for(int i=0; i<64; ++i) testAvMoves[i] = 0;
    testAvMoves[10] = 1; testAvMoves[11] = 1; testAvMoves[12] = 1; testAvMoves[17] = 1;
    testAvMoves[19] = 1; testAvMoves[21] = 1; testAvMoves[24] = 2; testAvMoves[27] = 2;
    testAvMoves[30] = 1; testAvMoves[39] = 1;
    testPiece->possiableMoves(testChessboard);
    testPiece->getPosMoves(posMoves);
    for(int i=0; i<64; ++i) if(posMoves[i] != testAvMoves[i]) difAvMoves++;
    ASSERT_EQUAL(difAvMoves, 0);

    testChessboard->setTestPos_2();
    testPiece = testChessboard->getPieceFromField(23);
    if(testPiece == nullptr) return;
    for(int i=0; i<64; ++i) testAvMoves[i] = 0;
    testAvMoves[22] = 1; testAvMoves[21] = 1; testAvMoves[20] = 1; testAvMoves[19] = 1;
    testAvMoves[18] = 1; testAvMoves[17] = 1; testAvMoves[16] = 1; testAvMoves[30] = 1;
    testAvMoves[31] = 2; testAvMoves[37] = 1; testAvMoves[44] = 1; testAvMoves[51] = 2;
    difAvMoves = 0;
    testPiece->possiableMoves(testChessboard);
    testPiece->getPosMoves(posMoves);
    for(int i=0; i<64; ++i) if(posMoves[i] != testAvMoves[i]) difAvMoves++;
    ASSERT_EQUAL(difAvMoves, 0);

}

CTEST(testRook, possiableMoves) {
    Chessboard* testChessboard = new Chessboard;
    testChessboard->setTestPos_1();
    Piece* testPiece = testChessboard->getPieceFromField(0);
    if(testPiece == nullptr) return;
    int testAvMoves[64];
    int posMoves[64];
    for(int i=0; i<64; ++i) testAvMoves[i] = 0;
    testAvMoves[8] = 1; testAvMoves[16] = 1; testAvMoves[24] = 2;
    int difAvMoves = 0;
    testPiece->possiableMoves(testChessboard);
    testPiece->getPosMoves(posMoves);
    for(int i=0; i<64; ++i) if(posMoves[i] != testAvMoves[i]) difAvMoves++;
    ASSERT_EQUAL(difAvMoves, 0);

    testChessboard->setTestPos_2();
    testPiece = testChessboard->getPieceFromField(27);
    if(testPiece == nullptr) return;
    for(int i=0; i<64; ++i) testAvMoves[i] = 0;
    testAvMoves[28] = 1; testAvMoves[29] = 1; testAvMoves[30] = 1; testAvMoves[31] = 2;
    testAvMoves[35] = 1; testAvMoves[43] = 1; testAvMoves[51] = 2; testAvMoves[19] = 1;
    difAvMoves = 0;
    testPiece->possiableMoves(testChessboard);
    testPiece->getPosMoves(posMoves);
    for(int i=0; i<64; ++i) if(posMoves[i] != testAvMoves[i]) difAvMoves++;
    ASSERT_EQUAL(difAvMoves, 0);
}


