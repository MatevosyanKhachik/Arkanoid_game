#ifndef MYBALL_H
#define MYBALL_H
#include <QObject>
#include <QRectF>
#include <QPainter>

class MyBall : public QObject
{
    Q_OBJECT
public:
    float X() const;
    float Y() const;
    float Vx() const;
    float Vy() const;
    float width() const;
    float height() const;
    void setVx(float vx);
    void setVy(float vy);
    explicit MyBall(QObject *parent = nullptr);
    ~MyBall();
    void setRect(float x1, float y1, float width, float height);
    void Draw(QPainter* painter);
    void moveTo(float x, float y);
private:
    QRectF* ball;
    float vx, vy;
public:
    bool is_on_the_board;
};

#endif // MYBALL_H
