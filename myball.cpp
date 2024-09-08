#include "myball.h"

MyBall::MyBall(QObject *parent) : QObject(parent),
  ball(new QRectF),
  is_on_the_board(true)
{

}

MyBall::~MyBall()
{
    delete ball;
}

void MyBall::setRect(float x1, float y1, float width, float height)
{
    ball->setRect(x1, y1, width, height);
}

void MyBall::Draw(QPainter *painter)
{
    painter->setBrush(QBrush(Qt::red));
    painter->drawEllipse(*ball);
}

void MyBall::moveTo(float x, float y)
{
    ball->moveTo(x, y);
}

float MyBall::X() const
{
    return ball->x();
}

float MyBall::Y() const
{
    return ball->y();
}

float MyBall::Vx() const
{
    return vx;
}

float MyBall::Vy() const
{
    return vy;
}

float MyBall::width() const
{
    return ball->width();
}

float MyBall::height() const
{
    return ball->height();
}

void MyBall::setVx(float vx)
{
    this->vx = vx;
}

void MyBall::setVy(float vy)
{
    this->vy = vy;
}
