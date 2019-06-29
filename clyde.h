#ifndef CLYDE_H
#define CLYDE_H

#include "ghost.h"

class Blinky;
class Pinky;
class Inky;

class Clyde : public Ghost
{
    Q_OBJECT
public:
    Clyde(QGraphicsScene *sc, int **map, Pacman *pc);
    void setDefault();
    void moveRule();
    void findPacman();
    void setFriends(Blinky *bl, Pinky *pnc, Inky *ink);
    void findPath();
    void initialize();

private:
    Blinky  *blinky;
    Pinky   *pinky;
    Inky    *inky;

public slots:
    void moveGhostSlots();
};

#endif // CLYDE_H
