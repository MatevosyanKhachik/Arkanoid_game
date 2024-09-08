#ifndef MYBLOCK_H
#define MYBLOCK_H

#include <QObject>
#include <QRectF>
#include <QPainter>

class MyBlock : public QObject
{
    Q_OBJECT
public:
    explicit MyBlock(QObject *parent = nullptr);
    ~MyBlock();
    void Draw(QPainter* painter);
    void setRect(float x1, float y1, float width, float height);
    void setColor(const QColor& col);
    QColor getColor() const;
    int getHealth() const;
    QRectF getRect() const;
    void damage();
    void setHealth(int hp);
    bool intersects(const QRectF& p);
private:
    QRectF* block;
    QColor* color;
    int health;
};

#endif // MYBLOCK_H
