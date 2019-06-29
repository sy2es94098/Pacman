#ifndef BLINKY_H
#define BLINKY_H

#include "ghost.h"

class Pinky;
class Clyde;
class Inky;

class Blinky : public Ghost
{
public:
    Blinky(QGraphicsScene *sc, int **map, Pacman *pc);
    void setDefault();
    void moveRule();
    void findPacman();
    void setFriends(Pinky *pin, Clyde *cl, Inky *ink);
    void findPath();
    void initialize();

private:
    Pinky *pinky;
    Clyde *clyde;
    Inky *inky;

public slots:
    void moveGhostSlots();


};

#endif // BLINKY_H
