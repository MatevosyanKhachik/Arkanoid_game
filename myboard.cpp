#include "myboard.h"

MyBoard::MyBoard()
    :board(new QRectF)
{

}

MyBoard::~MyBoard()
{
    delete board;
}

float MyBoard::X() const
{
    return board->x();
}

float MyBoard::Y() const
{
    return board->y();
}

float MyBoard::width() const
{
    return board->width();
}

float MyBoard::height() const
{
    return board->height();
}

void MyBoard::Draw(QPainter *painter)
{
    painter->setBrush(QBrush(Qt::gray,Qt::BrushStyle(Qt::Dense3Pattern)));
    painter->drawRect(*board);
}

void MyBoard::setRect(float x1, float y1, float width, float height)
{
    board->setRect(x1,y1,width,height);
}

