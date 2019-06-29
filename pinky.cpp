#include "pinky.h"
#include "blinky.h"
#include "clyde.h"
#include "inky.h"

Pinky::Pinky(QGraphicsScene *sc, int **map, Pacman *pc) : Ghost()
{
    scene = sc;
    pacman = pc;

    posI = 9;
    posJ = 9;
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
    this->setPixmap(QPixmap(":/pacimg/pinky.png"));
    this->setPos(posJ * 32, posI * 32);
    scene->addItem(this);
}

void Pinky::initialize()
{
    posI = 9;
    posJ = 9;
    this->setPixmap(QPixmap(":/pacimg/pinky.png"));
    this->setPos(posJ * 32, posI * 32);
    this->setZValue(100);
}

void Pinky::findPath()
{
    mapPath[blinky->getPosI()][blinky->getPosJ()] = -5;
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
    mapPath[blinky->getPosI()][blinky->getPosJ()] = 0;
    mapPath[clyde->getPosI()][clyde->getPosJ()] = 0;
    mapPath[inky->getPosI()][inky->getPosJ()] = 0;
}

void        Pinky::findPacman()
{
    d = 0;
    flag = 0;
    if (!pacman->scaredState())
    {
        this->setPixmap(QPixmap(":/pacimg/pinky.png"));
        moveRule();
    }
    else
    {
        if (posI == 1 && posJ == SIZEY - 2)
            pacman->setScared();
        else
        {
            this->setPixmap(QPixmap(":/pacimg/frightened.png"));
            exitI = 1;
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

void Pinky::setDefault()
{
    posI = 9;
    posJ = 9;

    exitI = posI;
    exitJ = posJ;
    direction = 0;
    this->setPos(posJ * 32, posI * 32);
}

void Pinky::moveRule()
{
    int direction;

    direction = pacman->getDirection();
    if (direction == 1)
    {
        exitI = pacman->getPacmanI() - 4;
        exitJ = pacman->getPacmanJ();
        if (exitI < 0)
        {
            exitI = pacman->getPacmanI();
            exitJ = pacman->getPacmanJ();
        }
    }
    if (direction == 2)
    {
        exitI = pacman->getPacmanI() + 4;
        exitJ = pacman->getPacmanJ();
        if (exitI >= SIZEX)
        {
            exitI = pacman->getPacmanI();
            exitJ = pacman->getPacmanJ();
        }
    }
    if (direction == 3)
    {
        exitI = pacman->getPacmanI();
        exitJ = pacman->getPacmanJ() - 4;
        if (exitJ < 0)
        {
            exitI = pacman->getPacmanI();
            exitJ = pacman->getPacmanJ();
        }
    }
    if (direction == 4)
    {
        exitI = pacman->getPacmanI();
        exitJ = pacman->getPacmanJ() + 4;
        if (exitJ > SIZEY)
        {
            exitI = pacman->getPacmanI();
            exitJ = pacman->getPacmanJ();
        }
    }
    if (mapPath[exitI][exitJ] != -3)
    {
        exitI = pacman->getPacmanI();
        exitJ = pacman->getPacmanJ();
    }
}

void Pinky::setFriends(Blinky *bl, Clyde *cl, Inky *ink)
{
    blinky = bl;
    clyde = cl;
    inky = ink;
}

void Pinky::moveGhostSlots()
{
    if (pacman->getPoint() >= 50)
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
