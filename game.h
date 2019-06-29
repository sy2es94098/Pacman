#ifndef GAME_H
#define GAME_H

#include<QObject>
#include<QPushButton>

class Widget;

class Game:public QWidget
{
    Q_OBJECT
public:
    Game();
private:
    QPushButton *start;
    Widget *w;
public slots:
    void startSlots();
};

#endif // GAME_H
