#include "myblock.h"

MyBlock::MyBlock(QObject *parent) : QObject(parent),
    block(new QRectF)
{

}

MyBlock::~MyBlock()
{
    delete block;
    delete color;
}

void MyBlock::Draw(QPainter *painter)
{
    painter->drawRect(*block);
}

void MyBlock::setRect(float x1, float y1, float width, float height)
{
    block->setRect(x1, y1, width, height);
}

void MyBlock::setColor(const QColor &col)
{
    color = new QColor(col);
}

QColor MyBlock::getColor() const
{
    return *color;
}

int MyBlock::getHealth() const
{
    return health;
}

QRectF MyBlock::getRect() const
{
    return *block;
}

void MyBlock::damage()
{
    --health;
}

void MyBlock::setHealth(int hp)
{
    health = hp;
}

bool MyBlock::intersects(const QRectF &p)
{
    return block->intersects(p);
}

