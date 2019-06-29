#include "pacman.h"
#include <QGraphicsScene>

Pacman::Pacman(int **mapI, QGraphicsPixmapItem **mapP, QGraphicsScene *sc)
{
        posI = 15;
        score = 0;
        points = 0;
        posJ = 9;
        counter = 0;
        direction = 0;
        mapInt = mapI;
        mapPix = mapP;
        scene = sc;
        scared = 0;
        lives = 3;
        text = new QGraphicsTextItem();
        message = new QGraphicsTextItem();
        this->setPixmap(QPixmap(":/pacimg/pacman_left.png"));
        this->setPos(posJ * 32, posI * 32);
        scene->addItem(this);
        scene->addItem(text);
        printScore();
}

void Pacman::updateScene()
{
    static int flag;

    if (points == 50)
    {
        mapInt[15][9] = 6;
        if (!flag)
        {
            mapPix[15][9].setPixmap(QPixmap(":/pacimg/cherries.png"));
            scene->addItem(&(mapPix[15][9]));
            flag = 1;
        }
    }
    if (mapInt[posI][posJ] == 6)
    {
        score += 200;
        mapInt[posI][posJ] = 0;
        scene->removeItem(&(mapPix[15][9]));
        flag = 0;
    }
    if (mapInt[posI][posJ] == 3)
    {
        mapInt[posI][posJ] = 0;
        score += 10;
        points++;
        scene->removeItem(&(mapPix[posI][posJ]));
    }
    if (mapInt[posI][posJ] == 4)
    {
        scared = 1;
        mapInt[posI][posJ] = 0;
        scene->removeItem(&(mapPix[posI][posJ]));
    }
}

int Pacman::scaredState()
{
    return (scared);
}

void Pacman::setScared()
{
    scared = !scared;
}

int Pacman::getScore()
{
    return (score);
}

void Pacman::printScore()
{
    text->setDefaultTextColor(0x00ffffff);
    text->setFont(QFont("times", 15));
    text->setPlainText("SCORE: " + QString::number(score) + "\t\tLIVES: " + QString::number(lives));
    text->setPos(10 , HEIGHT - 30);
}

void Pacman::incrScore()
{
    score += 100;
}

void Pacman::setLives()
{
    lives--;
}

int Pacman::getDirection()
{
    return (direction);
}

void Pacman::setDirection(int n)
{
    this->direction = n;
}

void Pacman::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Left)
     {
        this->direction = 3;
        this->setPixmap(QPixmap(":/pacimg/pacman_left.png"));
     }
     if (event->key() == Qt::Key_Right)
     {
        this->direction = 4;
         this->setPixmap(QPixmap(":/pacimg/pacman_right.png"));
     }
     if (event->key() == Qt::Key_Down)
     {
        this->direction = 2;
        this->setPixmap(QPixmap(":/pacimg/pacman_down.png"));
     }
     if (event->key() == Qt::Key_Up)
     {
        this->direction = 1;
        this->setPixmap(QPixmap(":/pacimg/pacman_up.png"));
     }
}

int Pacman::getPoint()
{
    return (points);
}

void Pacman::moveSlots()
{
    static int flag;

    printScore();
    if (points == 149 && !flag)
    {
        message->setDefaultTextColor(0x00ff00ff);
        message->setFont(QFont("times", 40));
        message->setPlainText("YOU WIN");
        message->setPos(60, HEIGHT / 2 - 30);
        scene->addItem(message);
        scene->removeItem(this);
        scene->removeItem(text);
        flag = 1;
    }
    if (lives <= 0 && !flag)
    {
        message->setDefaultTextColor(0x00ff00ff);
        message->setFont(QFont("times", 60));
        message->setPlainText("YOU LOST");
        message->setPos(80, HEIGHT / 2);
        scene->addItem(message);
        scene->removeItem(this);
        scene->removeItem(text);
        flag = 1;
    }
    updateScene();
    if (direction == 1)
    {
        if (posI == 0)
        {
           if (checkMove(SIZEX - 1, posJ))
               posI = SIZEX - 1;
        }
        else
            if (checkMove(posI - 1, posJ))
                posI--;
    }
    if (direction == 2)
    {
        if (posI == SIZEX - 1)
        {
            if (checkMove(0, posJ))
                posI = 0;
        }
        else
            if (checkMove(posI + 1, posJ))
                posI++;
    }
    if (direction == 3)
    {
        if (posJ == 0)
        {
            if (checkMove(posI, SIZEY - 1))
                posJ = SIZEY - 1;
        }
        else
            if (checkMove(posI, posJ - 1))
                posJ--;
    }
    if (direction == 4)
    {
        if (posJ == SIZEY - 1)
        {
            if (checkMove(posI, 0))
                posJ = 0;
        }
        else
            if (checkMove(posI, posJ + 1))
                posJ++;
    }
    this->setPos(posJ * 32, posI * 32);
}

int Pacman::getPacmanI(void)
{
    return (posI);
}

int Pacman::getPacmanJ(void)
{
    return (posJ);
}

int Pacman::checkMove(int posI, int posJ)
{
    if (mapInt[posI][posJ] == 1)
        return (0);
    return (1);
}

void Pacman::setDefaut()
{
    posI = 15;
    posJ = 9;

    direction = 0;
    this->setPos(posJ * 32, posI * 32);
    this->setZValue(100);
}

void Pacman::initializePacman()
{
    posI = 15;
    score = 0;
    points = 0;
    posJ = 9;
    counter = 0;
    direction = 0;
    scared = 0;
    lives = 3;
    this->setZValue(100);

}
