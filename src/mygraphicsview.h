#ifndef MYGRAPHICSVIEW_H
#define MYGRAPHICSVIEW_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsItemGroup>
#include <QMouseEvent>
#include "chessboard.h"

class MyGraphicsView : public QGraphicsView
{
public:
    MyGraphicsView(QWidget *parent);

private:
    Chessboard *myBoard = nullptr;
    QGraphicsScene *scene = nullptr;
    const int size = 50;
    const int padding = 20;

    void drawField(int fieldNum, QBrush color);
    void drawPiece(int fieldNum);
    void drawBoard();

protected slots:
    //void mousePressEvent(QMouseEvent *mouseEvent);
    //void mouseMoveEvent(QMouseEvent *mouseEvent);
    void mouseReleaseEvent(QMouseEvent *mouseEvent);
};

#endif // MYGRAPHICSVIEW_H
