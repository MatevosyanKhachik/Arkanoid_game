#ifndef MyBoard_H
#define MyBoard_H
#include <QRectF>
#include <QObject>
#include <QPainter>

class MyBoard : public QObject
{
public:
    MyBoard();
    ~MyBoard();
    float X() const;
    float Y() const;
    float width() const;
    float height() const;
    void Draw(QPainter* painter);
    void setRect(float x1, float y1, float width, float height);
private:
    QRectF* board;
};

#endif // MyBoard_H
