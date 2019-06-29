#ifndef INKY_H
#define INKY_H

#include "ghost.h"

class Blinky;
class Pinky;
class Clyde;

class Inky : public Ghost
{
    Q_OBJECT
public:
    Inky(QGraphicsScene *sc, int **map, Pacman *pc);
    void setDefault();
    void moveRule();
    void findPacman();
    void setFriends(Blinky *bl, Pinky *pnc, Clyde *cld);
    void findPath();
    void initialize();


private:
    Blinky *blinky;
    Clyde *clyde;
    Pinky *pinky;

public slots:
    void moveGhostSlots();
};

#endif // INKY_H
