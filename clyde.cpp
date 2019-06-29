#include "clyde.h"
#include <cmath>
#include "blinky.h"
#include "pinky.h"
#include "inky.h"

Clyde::Clyde(QGraphicsScene *sc, int **map, Pacman *pc)
{
    scene = sc;
    pacman = pc;

    posI = 9;
    posJ = 8;
    for (int i = 0; i < SIZEX; i++)
    {
        for (int j = 0; j < SIZEY; j++)
        {
            if (map[i][j] == 1)
                mapPath[i][j] = -5;
            else
                mapPath[i][j] = -3;
        }
    }
    this->setPixmap(QPixmap(":/pacimg/clyde.png"));
    this->setPos(posJ * 32, posI * 32);
    scene->addItem(this);
}

void Clyde::initialize()
{
    posI = 9;
    posJ = 8;
    this->setPixmap(QPixmap(":/pacimg/clyde.png"));
    this->setPos(posJ * 32, posI * 32);
    this->setZValue(100);
}

void Clyde::findPacman()
{
    d = 0;
    flag = 0;
    if (!pacman->scaredState())
    {
        this->setPixmap(QPixmap(":/pacimg/clyde.png"));
        moveRule();
    }
    else
    {
        if (posI == SIZEX - 2 && posJ == SIZEY - 2)
            pacman->setScared();
        else
        {
            this->setPixmap(QPixmap(":/pacimg/frightened.png"));
            exitI = SIZEX - 2;
            exitJ = SIZEY - 2;
        }
    }
    mapPath[posI][posJ] = d;
    if (checkIntersect())
        return ;
    findPath();
    if (touch())
    {
        clearMap();
        return ;
    }
    focusPath();
    setDirection();
    clearMap();
}

void Clyde::findPath()
{

    mapPath[blinky->getPosI()][blinky->getPosJ()] = -5;
    mapPath[pinky->getPosI()][pinky->getPosJ()] = -5;
    mapPath[inky->getPosI()][inky->getPosJ()] = -5;
    while (!flag && mapPath[exitI][exitJ] == -3)
    {
        flag = 1;
        for(int i = 0 ; i < SIZEX; ++i)
        {
            for(int j = 0 ; j < SIZEY; ++j)
            {
                if (mapPath[i][j] == d)
                {
                    for(int k = 0 ; k < 4 ; ++k)
                    {
                        testX = dirX[k] + i;
                        testY = dirY[k] + j;
                        if ((testX >= 0 && testX < SIZEX)
                            && (testY >= 0 && testY < SIZEY) && (mapPath[testX][testY] == -3))
                        {
                            mapPath[testX][testY] = d + 1;
                            flag = 0;
                        }
                    }
                }
            }
        }
        d++;
    }
    mapPath[blinky->getPosI()][blinky->getPosJ()] = 0;
    mapPath[pinky->getPosI()][pinky->getPosJ()] = 0;
    mapPath[inky->getPosI()][inky->getPosJ()] = 0;
}

void Clyde::setDefault()
{
    posI = 9;
    posJ = 8;

    exitI = posI;
    exitJ = posJ;
    direction = 0;
    this->setPos(posJ * 32, posI * 32);
}

void        Clyde::moveRule()
{
    int distance;

    distance = pow(posI - pacman->getPacmanI(), 2);
    distance += pow(posJ - pacman->getPacmanJ(), 2);
    distance = sqrt(distance);
    if (distance <= 8)
    {
        exitI = pacman->getPacmanI();
        exitJ = pacman->getPacmanJ();
    }
    else
    {
        exitI = SIZEX - 2;
        exitJ = 1;
    }
    this->setPixmap(QPixmap(":/pacimg/clyde.png"));
}

void Clyde::setFriends(Blinky *bl, Pinky *pnc, Inky *ink)
{
    blinky = bl;
    pinky = pnc;
    inky = ink;
}

void Clyde::moveGhostSlots()
{
    if (pacman->getPoint() >= 90)
    {
        findPacman();
        if (direction == 1)
        {
            if (checkMove(posI - 1, posJ))
                posI--;
        }
        if (direction == 2)
        {
            if (checkMove(posI + 1, posJ))
                posI++;
        }
        if (direction == 3)
        {
            if (checkMove(posI, posJ - 1))
                posJ--;
        }
        if (direction == 4)
        {
            if (checkMove(posI, posJ + 1))
                posJ++;
        }
        this->setPos(posJ * 32, posI * 32);
        if (checkIntersect())
            return ;
    }
}

