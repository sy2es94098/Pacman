#include "ghost.h"
#include <QGraphicsPixmapItem>

Ghost::Ghost(){}

void Ghost::setDefault(){}

void Ghost::moveGhostSlots(){}

void Ghost::moveRule(){}

void Ghost::findPacman(){}

void Ghost::findPath(){}

void Ghost::setDirection()
{
    if (posI + 1 < SIZEX)
    {
        if (mapPath[posI + 1][posJ] == -4)
            direction = 2;
    }
    if (posI - 1 >= 0)
    {
        if (mapPath[posI - 1][posJ] == -4)
            direction = 1;
    }
    if (posJ + 1 < SIZEX)
    {
        if (mapPath[posI][posJ + 1] == -4)
            direction = 4;
    }
    if (posJ - 1 < SIZEX)
    {
        if (mapPath[posI][posJ - 1] == -4)
            direction = 3;
    }
}

int Ghost::getPosI()
{
    return (posI);
}

int Ghost::getPosJ()
{
    return (posJ);
}

int Ghost::checkMove(int posI, int posJ)
{
    if (mapPath[posI][posJ] == -5)
        return (0);
    return (1);
}

int Ghost::checkIntersect()
{
    if (posI == pacman->getPacmanI() && posJ == pacman->getPacmanJ() && !pacman->scaredState())
    {
        clearMap();
        pacman->setDefaut();
        pacman->setLives();
        return (1);
    }
    if (posI == pacman->getPacmanI() && posJ == pacman->getPacmanJ()&& pacman->scaredState())
    {
        clearMap();
        posI = 8;
        posJ = 9;
        this->setPos(posJ * 32, posI * 32);
        pacman->incrScore();
        return (1);
    }
    return (0);
}

void Ghost::clearMap()
{
    for (int i = 0; i < SIZEX; i++)
    {
        for (int j = 0; j < SIZEY; j++)
        {
            if (mapPath[i][j] != -5)
                mapPath[i][j] = -3;
        }
    }
}

void Ghost::focusPath()
{
    int i;
    int j;
    int k;

    i = exitI;
    j = exitJ;
    while (d > 0)
    {
        d--;
        k = 0;
        while (k < 4)
        {
            testX = i + dirX[k];
            testY = j + dirY[k];
            if (testX >= 0 && testX < SIZEX && testY >= 0 && testY < SIZEY && mapPath[testX][testY] == d)
            {
                mapPath[testX][testY] = -4;
                i = i + dirX[k];
                j = j + dirY[k];
                break ;
            }
            k++;
        }
    }
}

int Ghost::touch()
{
    int flag;

    flag = 0;
    if (posI + 1 < SIZEX)
    {
        if (posI + 1 == exitI && posJ == exitJ)
        {
            direction = 2;
            flag = 1;
        }
    }
    if (posI - 1 >= 0)
    {
        if (posI -1 == exitI && posJ == exitJ)
        {
            direction = 1;
            flag = 1;
        }
    }
    if (posJ + 1 < SIZEX)
    {
        if (posI == exitI && posJ + 1 == exitJ)
        {
            direction = 4;
            flag = 1;
        }
    }
    if (posJ - 1 < SIZEX)
    {
        if (posI == exitI && posJ - 1 == exitJ)
        {
            direction = 3;
            flag = 1;
        }
    }
    if (flag)
        return (1);
    return (0);
}
