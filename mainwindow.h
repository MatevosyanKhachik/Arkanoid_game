#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsRectItem>
#include <myboard.h>
#include <myball.h>
#include <myblock.h>
#include <QMouseEvent>
#include <QTimer>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
private slots:
    void on_pushButton_clicked();
    void on_timer_timeout();
    //void on_board_timer_timeout();
private:
    virtual void paintEvent(QPaintEvent *event) override;
    virtual void keyPressEvent(QKeyEvent *event) override;
    virtual void mousePressEvent(QMouseEvent* event) override;
    void update_board();
    QRectF giveRect(int width, int height);
private:
    Ui::MainWindow *ui;
    QTimer* timer;
    QTimer* board_timer;
    bool play_btn_clicked;
    bool mouse_clicked;
    bool pressed_with_shift;
    bool central_widget_cleared;
    bool won;
    //std::vector<bool> key_is_pressed;
    MyBoard* board;
    MyBall* ball;
    QVector<MyBlock*>blocks;
};
#endif // MAINWINDOW_H
