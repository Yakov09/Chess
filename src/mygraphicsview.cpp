#include "mygraphicsview.h"
#include <iostream>
MyGraphicsView::MyGraphicsView(QWidget *parent)
    :QGraphicsView(parent)
{
    /* Немного поднастроим отображение виджета и его содержимого */
    this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff); // Отключим скроллбар по горизонтали
    this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);   // Отключим скроллбар по вертикали
    this->setAlignment(Qt::AlignCenter);                        // Делаем привязку содержимого к центру
    this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);    // Растягиваем содержимое по виджету

    /* Также зададим минимальные размеры виджета */

    this->setMinimumHeight(size*8 + padding*2);
    this->setMinimumWidth(size*8 + padding*2);

    scene = new QGraphicsScene();   // Инициализируем сцену для отрисовки
    this->setScene(scene);          // Устанавливаем сцену в виджет

    myBoard = new Chessboard;

    myBoard->setInintPosition();
    //myBoard->setTestPos_1();
    drawBoard();
}

void MyGraphicsView::drawBoard(){
    scene->setSceneRect(0, 0, size*8 + padding*2, size*8 + padding*2);
    for(int i=0; i<64; ++i){
        QBrush color = (myBoard->getFieldColor(i) == 0) ?  Qt::gray : Qt::white;
        drawField(i, color);
        drawPiece(i);
    }
}

void MyGraphicsView::drawField(int fieldNum, QBrush color){
    QPen penBlack(Qt::black);
    int left = padding + (fieldNum % 8)*size;
    int top = padding + (7 - fieldNum/8)*size;
    QRect fieldRect(left, top, size, size);
    scene->addRect(fieldRect, penBlack, color);
}

void MyGraphicsView::drawPiece(int fieldNum){
    Piece* tempPiece = myBoard->getPieceFromField(fieldNum);
    QGraphicsPixmapItem *pm;
    if(tempPiece != nullptr){
        QString path = QString::fromStdString(tempPiece->getImagePath());
        QPixmap pieceImage(path);
        pm = scene->addPixmap(pieceImage);
        int left = padding + (fieldNum % 8)*size;
        int top = padding + (7 - fieldNum/8)*size;
        pm->setPos(left, top);
    }
}

//void MyGraphicsView::mousePressEvent(QMouseEvent *mouseEvent){
//    QPoint point = mouseEvent->pos();
//    if((point.rx() < padding)||(point.rx() > padding + size * 8)||(point.ry() < padding)||(point.ry() > padding + size * 8)) return;
//    int field_h = (point.rx() - padding) / size;
//    int field_v = 7 - ((point.ry() - padding) / size);
//    int field = field_h + field_v*8;
//    //std::cout << "\n -- Pressed field " << field << " --- ";
//}



void MyGraphicsView::mouseReleaseEvent(QMouseEvent *mouseEvent){
    if(myBoard->getWin() != 0) return;

    QPoint point = mouseEvent->pos();
    if((point.rx() < padding)||(point.rx() > padding + size * 8)||(point.ry() < padding)||(point.ry() > padding + size * 8)) return;
    int field_h = (point.rx() - padding) / size;
    int field_v = 7 - ((point.ry() - padding) / size);
    int field = field_h + field_v*8;    
    Piece* activePiece = myBoard->getPieceFromField(field);     // piece on field under mouse cursor
    Piece* chosenPiece = myBoard->getChosenPiece();             // piece, which was chosen as active by previous mouse click
    if((chosenPiece == nullptr)&&(activePiece == nullptr))return;
    if((chosenPiece != nullptr)&&(chosenPiece->checkPossibleMove(field)) == 0) {  // cancel choice
        //std::cout << "\n Cancel! \n";
        myBoard->setChosenPiece(false, nullptr);
        drawBoard();
        return;
    }
    if(chosenPiece == nullptr){                               // choose active piece for move
        //std::cout << "\n Choose! \n";
        if(myBoard->getMoveOrder() != activePiece->getColor()) return;
        myBoard->setChosenPiece(true, activePiece);
        drawBoard();
        drawField(field, Qt::yellow);
        drawPiece(field);
        int posMoves[64];
        activePiece->possiableMoves(myBoard);
        activePiece->getPosMoves(posMoves);

        for(int i=0; i<64; ++i){
            if((posMoves[i] == 1)||(posMoves[i] == 3)){
                drawField(i, Qt::blue);
                drawPiece(i);
            }
            if(posMoves[i] == 2){
                drawField(i, Qt::red);
                drawPiece(i);
            }
        }
    } else                                                                   // making move
    if(chosenPiece != nullptr){
        //std::cout << "\n Move! \n";
        myBoard->makeMove(field);
        drawBoard();
        myBoard->checkWin();
        if(myBoard->getWin() == 1) std::cout << "\n  White wins!\n";
        if(myBoard->getWin() == 2) std::cout << "\n  Black wins!\n";
    }

}
