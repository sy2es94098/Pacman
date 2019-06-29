#ifndef GHOST_H
#define GHOST_H

#include "pacman.h"

class Ghost: public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    Ghost();
    void clearMap();
    void focusPath();
    void setDirection();
    int checkIntersect();
    int touch();
    int getPosI();
    int getPosJ();
    int checkMove(int posI, int posJ);
    virtual void setDefault() = 0;
    virtual void moveRule() = 0;
    virtual void findPacman() = 0;
    virtual void findPath() = 0;
    virtual void initialize() = 0;
protected:
    int d;
    int posI;
    int posJ;
    int testX;
    int testY;
    int flag;
    int exitI;
    int exitJ;
    int direction;
    int mapPath[21][19];
    int dirX[4] = { 1, -1, 0, 0 };
    int dirY[4] = { 0, 0, 1, -1 };
    Pacman *pacman;
    QGraphicsScene  *scene;
public slots:
    virtual void moveGhostSlots() = 0;

};

#endif // GHOST_H
