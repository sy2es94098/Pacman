#include "blinky.h"
#include "pinky.h"
#include "clyde.h"
#include "inky.h"

Blinky::Blinky(QGraphicsScene *sc, int **map, Pacman *pc) : Ghost()
{
    scene = sc;
    pacman = pc;
    posI = 8;
    posJ= 9;

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
    this->setPixmap(QPixmap(":/pacimg/blinky.png"));
    this->setPos(posJ * 32, posI * 32);
    scene->addItem(this);
}

void Blinky::initialize()
{
    posI = 8;
    posJ= 9;
    this->setPixmap(QPixmap(":/pacimg/blinky.png"));
    this->setPos(posJ * 32, posI * 32);
    this->setZValue(100);
}

void Blinky::setDefault()
{
    exitI = posI;
    exitJ = posJ;
    posI = 9;
    posJ = 9;
    direction = 0;
    this->setPos(posJ * 32, posI * 32);
}

void Blinky::setFriends(Pinky *pin, Clyde *cl, Inky *ink)
{
    pinky = pin;
    clyde = cl;
    inky = ink;
}

void Blinky::findPath()
{
    mapPath[pinky->getPosI()][pinky->getPosJ()] = -5;
    mapPath[clyde->getPosI()][clyde->getPosJ()] = -5;
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
    mapPath[pinky->getPosI()][pinky->getPosJ()] = 0;
    mapPath[clyde->getPosI()][clyde->getPosJ()] = 0;
    mapPath[inky->getPosI()][inky->getPosJ()] = 0;
}

void Blinky::moveRule()
{
    if (!pacman->scaredState())
    {
        exitI = pacman->getPacmanI();
        exitJ = pacman->getPacmanJ();
        this->setPixmap(QPixmap(":/pacimg/blinky.png"));
    }
    else
    {
        if (posI == 1 && posJ == 1)
            pacman->setScared();
        else
        {
            this->setPixmap(QPixmap(":/pacimg/frightened.png"));
            exitI = 1;
            exitJ = 1;
        }
    }
}

void Blinky::findPacman()
{
    d = 0;
    flag = 0;
    mapPath[posI][posJ] = d;
    if (checkIntersect())
    {
        clearMap();
        return ;
    }
    findPath();
    if (touch())
    {
        if (checkIntersect())
        {
            clearMap();
            return ;
        }
    }
    focusPath();
    setDirection();
    clearMap();
}

void Blinky::moveGhostSlots()
{
    moveRule();
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
