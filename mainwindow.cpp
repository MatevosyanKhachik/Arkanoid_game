#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPixmap>
#include <QPalette>
#include <QPushButton>
#include <QHBoxLayout>
#include <QPainter>
#include <QKeyEvent>
#include <QDebug>
#include <windows.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    ,play_btn_clicked(false)
    ,mouse_clicked(false)
    ,pressed_with_shift(false)
    ,central_widget_cleared(false)
    ,board(new MyBoard)
    ,ball(new MyBall)
    ,timer(new QTimer(this))
    //,board_timer(new QTimer(this))
    ,won(false)
{
    //key_is_pressed.resize(255);
    srand(time(nullptr));
    connect(timer,SIGNAL(timeout()),this,SLOT(on_timer_timeout()));
    //connect(board_timer, SIGNAL(timeout()),this,SLOT(on_board_timer_timeout()));
    timer->setSingleShot(false);
    timer->setInterval(20);
    //board_timer->setSingleShot(false);
    //board_timer->setInterval(50);
    setStyleSheet("MainWindow {background-image:url(C:/Users/kmate/OneDrive/Pictures/hexagon_pattern.png)}");
    ui->setupUi(this);
    ui->pushButton->setStyleSheet("background-color:yellow;");
    ui->pushButton_2->setStyleSheet("background-color:yellow;");
}

MainWindow::~MainWindow()
{
    delete board;
    delete ball;
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    if(!play_btn_clicked)
    {
        play_btn_clicked = true;
        return;
    }
    QPainter* painter = new QPainter(this);
    board->Draw(painter);
    ball->Draw(painter);
    for(int i=0; i < blocks.size(); ++i)
    {
        painter->setBrush(QBrush(blocks[i]->getColor()));//err
        blocks[i]->Draw(painter);
    }
    delete painter;

}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    //key_is_pressed[event->key()] = true;
    if(event->key() == Qt::Key_Space && event->modifiers() & Qt::ShiftModifier)
    {
        pressed_with_shift = true;
        mousePressEvent(nullptr);
    }
    else if(event->key() == Qt::Key_Space)
    {
        mousePressEvent(nullptr);
    }
    if(board->X() > 5 && event->key() == Qt::Key_Left)
    {
        int move = 13;
        if(event->modifiers() & Qt::ShiftModifier)
            move = 18;
        board->setRect(board->X() - move,board->Y(),board->width(),board->height());
        if(ball->is_on_the_board)
            ball->setRect(ball->X() - move, ball->Y(),ball->width(),ball->height());
    }
    else if(board->X() + board->width()  + 5 < this->geometry().width() && event->key() == Qt::Key_Right)
    {
        int move = 13;
        if(event->modifiers() & Qt::ShiftModifier)
            move = 18;
        board->setRect(board->X() + move,board->Y(),board->width(),board->height());
        if(ball->is_on_the_board)
            ball->setRect(ball->X() + move, ball->Y(),ball->width(),ball->height());
    }
    update();
}

/*
void MainWindow::keyReleaseEvent(QKeyEvent *event)
{
    key_is_pressed[event->key()] = false;
}
*/
void MainWindow::mousePressEvent(QMouseEvent *event)
{
    if(!central_widget_cleared)
        return;
    if(!mouse_clicked)
    {
        ball->is_on_the_board = false;
        int a = rand() + 1;
        float vx = (a % 2 == 0 ? -5 : 5);
        float vy = rand() % 4 - 5;
        float add_shift = 0;
        if(pressed_with_shift)
            add_shift = vx;
        ball->setVx(vx + add_shift);
        ball->setVy(vy - 5);
        timer->start();
        mouse_clicked = true;
    }
}

void MainWindow::update_board()
{
    board->setRect(this->geometry().width()/2-48,this->geometry().height() - 25,
                   120,18);
}

QRectF MainWindow::giveRect(int width, int height)
{
    return QRectF(rand() % (this->geometry().width() - width),
                  rand() % this->geometry().height() / 2 + 1,width,height);
}

void MainWindow::on_pushButton_clicked()
{
    board->setRect(this->geometry().width()/2-48,this->geometry().height() - 25,
                    120,18);
    ball->setRect(board->X() + board->width()/2 - 10,board->Y() - board->height() - 3,
                        20,20);
    delete this->centralWidget();
    int width = this->geometry().width() / 10;
    int height = width / 2;
    for(int i = 0; i < 10; ++i)
    {
        MyBlock* block = new MyBlock;
        bool exists = false;
        QRectF rect = giveRect(width, height);
        for(int j=0; j < blocks.size(); ++j)
        {
            if(blocks[j]->intersects(rect))
            {
                exists = true;
                break;
            }
        }
        if(exists)
        {
            --i;
            continue;
        }
        else
            block->setRect(rect.x(),rect.y(), width, height);
        int a = rand() % 3 + 1;
        switch(a)
        {
        case 1:
            block->setHealth(1);
            block->setColor(Qt::green);
            break;
        case 2:
            block->setHealth(2);
            block->setColor(Qt::blue);
            break;
        case 3:
            block->setHealth(3);
            block->setColor(Qt::red);
            break;
        }
        blocks.push_back(block);
    }
    central_widget_cleared = true;
    update();
}

void MainWindow::on_timer_timeout()
{
    if(blocks.empty())
    {
        won = true;
        QLabel* label = new QLabel("Game Over",this);
        label->setFont(QFont("MS Sans Serif",60,20,true));
        label->setAlignment(Qt::AlignCenter);
        label->setGeometry(QRect(this->geometry().width() / 2 - 250,this->geometry().height() / 2,500,50));
        label->setText("You Won!");
        label->show();
        timer->stop();
    }
    else if(ball->Y() > this->geometry().height() + 5 && !won)
    {
        blocks.clear();
        QLabel* label = new QLabel("Game Over",this);
        label->setFont(QFont("MS Sans Serif",60,20,true));
        label->setAlignment(Qt::AlignCenter);
        label->setGeometry(QRect(this->geometry().width() / 2 - 250,this->geometry().height() / 2,500,50));
        label->show();
        timer->stop();
    }

    ball->moveTo(ball->X() + ball->Vx(), ball->Y() + ball->Vy());
    if(ball->X() < 2 || ball->X() + ball->width() > this->geometry().width())
        ball->setVx(-ball->Vx());
    else if(ball->Y() < 2)
        ball->setVy(-ball->Vy());
    else if(ball->X() + ball->width() / 2 >= board->X() && ball->X() + ball->width() / 2 <= board->X() + board->width() + 2
            && ball->Y() + ball->height() >= board->Y() && ball->Y() + ball->height() <= board->Y() + board->height())
        ball->setVy(-ball->Vy());
    /*else if((ball->X() >= board->X() + board->width() && ball->Y() + ball->height() / 2 >= board->Y() &&
            ball->Y() + ball->height() / 2<= board->Y() + board->height()))
        ball->setVx(-ball->Vx()); Doesn't work */
    for(auto& x : blocks)
    {
        QRectF rect = x->getRect();
        if(ball->X() + ball->width() >= rect.x() && ball->X() + ball->width() < rect.x() + 4 &&
                ball->Y() + ball->height() / 2 >= rect.y() && ball->Y() + ball->height() / 2 <= rect.y() + rect.height())
        {
            ball->setVx(-ball->Vx());
            x->damage();
        }
        if(ball->X() <= rect.x() + rect.width() && ball->X() > rect.x() + rect.width() - 4 &&
                ball->Y() + ball->height() / 2 >= rect.y() && ball->Y() + ball->height() / 2 <= rect.y() + rect.height())
        {
            ball->setVx(-ball->Vx());
            x->damage();
        }
        else if(ball->X() + ball->width() / 2 >= rect.x() - 2 && ball->X() + ball->width() / 2 <= rect.x() + rect.width() + 2
               && ball->Y() <= rect.y() + rect.height() + 2 && ball->Y() + ball->height() >= rect.y())
        {
            ball->setVy(-ball->Vy());
            x->damage();
        }
        if(x->getHealth() <= 0)
            blocks.erase(&x);
        switch(x->getHealth())
        {
        case 1:
            x->setColor(Qt::green);
            break;
        case 2:
            x->setColor(Qt::blue);
            break;
        }

    }
    update();
}
/*
void MainWindow::on_board_timer_timeout(QKeyEvent* event)
{
    if(board->X() > 5 && key_is_pressed[Qt::Key_Left])
    {
        int move = 13;
        if(event->modifiers() & Qt::ShiftModifier)
            move = 18;
        board->setRect(board->X() - move,board->Y(),board->width(),board->height());
        if(ball->is_on_the_board)
            ball->setRect(ball->X() - move, ball->Y(),ball->width(),ball->height());
    }
    else if(board->X() + board->width()  + 5 < this->geometry().width() && key_is_pressed[Qt::Key_Right])
    {
        int move = 13;
        if(event->modifiers() & Qt::ShiftModifier)
            move = 18;
        board->setRect(board->X() + move,board->Y(),board->width(),board->height());
        if(ball->is_on_the_board)
            ball->setRect(ball->X() + move, ball->Y(),ball->width(),ball->height());
    }
    update();
}
*/
