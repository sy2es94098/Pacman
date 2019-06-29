#ifndef PINKY_H
#define PINKY_H

#include "ghost.h"

class Blinky;
class Clyde;
class Inky;

class Pinky : public Ghost
{
    Q_OBJECT
public:
    Pinky(QGraphicsScene *sc, int **map, Pacman *pc);
    void setDefault();
    void moveRule();
    void findPacman();
    void setFriends(Blinky *bl, Clyde *cl, Inky *ink);
    void findPath();
    void initialize();

private:
    Blinky *blinky;
    Clyde *clyde;
    Inky *inky;

public slots:
    void moveGhostSlots();
};

#endif // PINKY_H
