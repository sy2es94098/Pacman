#include "inky.h"
#include <cmath>
#include "blinky.h"
#include "clyde.h"
#include "pinky.h"

Inky::Inky(QGraphicsScene *sc, int **map, Pacman *pc) : Ghost()
{
    scene = sc;
    pacman = pc;

    posI = 9;
    posJ = 10;
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
    this->setPixmap(QPixmap(":/pacimg/inky.png"));
    this->setPos(posJ * 32, posI * 32);
    scene->addItem(this);
}

void Inky::initialize()
{
    posI = 9;
    posJ = 10;
    this->setPixmap(QPixmap(":/pacimg/inky.png"));
    this->setPos(posJ * 32, posI * 32);
    this->setZValue(100);
}

void Inky::findPacman()
{
    d = 0;
    flag = 0;
    if (!pacman->scaredState())
    {
        this->setPixmap(QPixmap(":/pacimg/inky.png"));
        moveRule();
    }
    else
    {
        if (posI == SIZEX - 2 && posJ == 1)
            pacman->setScared();
        else
        {
            this->setPixmap(QPixmap(":/pacimg/frightened.png"));
            exitI = SIZEX - 2;
            exitJ = 1;
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

void Inky::findPath()
{
    mapPath[blinky->getPosI()][blinky->getPosJ()] = -5;
    mapPath[pinky->getPosI()][pinky->getPosJ()] = -5;
    mapPath[clyde->getPosI()][clyde->getPosJ()] = -5;
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
    mapPath[clyde->getPosI()][clyde->getPosJ()] = 0;
}

void Inky::setDefault()
{
    posI = 9;
    posJ = 10;

    exitI = posI;
    exitJ = posJ;
    direction = 0;
    this->setPos(posJ * 32, posI * 32);
}

void        Inky::moveRule()
{
    int direction;
    int blinkyI;
    int blinkyJ;
    int distance;

    direction = pacman->getDirection();
    if (direction == 1)
    {
        exitI = pacman->getPacmanI() - 2;
        exitJ = pacman->getPacmanJ();
        if (exitI < 0)
        {
            exitI = pacman->getPacmanI();
            exitJ = pacman->getPacmanJ();
        }
    }
    if (direction == 2)
    {
        exitI = pacman->getPacmanI() + 2;
        exitJ = pacman->getPacmanJ();
    }
    if (direction == 3)
    {
        exitI = pacman->getPacmanI();
        exitJ = pacman->getPacmanJ() - 2;
    }
    if (direction == 4)
    {
        exitI = pacman->getPacmanI();
        exitJ = pacman->getPacmanJ() + 2;
    }
    blinkyI = blinky->getPosI();
    blinkyJ = blinky->getPosJ();
    distance = pow(blinkyI - exitI, 2);
    distance += pow(blinkyJ - exitJ, 2);
    distance = sqrt(distance);
    distance /= 2;
    exitI += distance;
    exitJ += distance;
    if (exitI <= 0 || exitI >= (SIZEX - 1)
            || exitJ <= 0 || exitJ >= (SIZEY - 1))
    {
        exitI = 9;
        exitJ = 10;
    }
    this->setPixmap(QPixmap(":/pacimg/inky.png"));
}

void Inky::setFriends(Blinky *bl, Pinky *pnc, Clyde *cld)
{
    blinky = bl;
    pinky = pnc;
    clyde = cld;
}

void Inky::moveGhostSlots()
{
    if (pacman->getPoint() >= 100)
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
