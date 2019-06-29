#include "game.h"
#include "widget.h"
Game::Game()
{
    start = new QPushButton("遊戲開始",this);
    start->setStyleSheet("QPushButton{background:#0000FF;}");
    start->setGeometry(250,350,100,40);
    start->show();
    QObject::connect(start,SIGNAL(clicked(bool)),SLOT(startSlots()));
}

void Game::startSlots()
{
    start->hide();
    Widget *w;
    w->startGame();
}
