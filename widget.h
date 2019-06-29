#ifndef WIDGET_H
#define WIDGET_H

#include <fstream>
#include <string>
#include <ctime>
#include <random>
#include <vector>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <QTimer>
#include <QLabel>
#include <QObject>
#include <QApplication>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include "pacman.h"
#include "ghost.h"
#include "blinky.h"
#include "pinky.h"
#include "clyde.h"
#include "inky.h"
#include <QKeyEvent>
class Widget: public QGraphicsView
{
public:

    Widget(char *fileName);
    Widget();
    ~Widget();
    void keyPressEvent(QKeyEvent *event);
    void writeLineMap(int *map, std::string str);
    void startGame();
    void createMap();
    int checkFileInp(std::string str);
    void storeMap();
    void speedUpPac();
    void speedUpGhost();
    void madeInHeaven();
    void calmDownPac();
    void calmDownGhost();
    void calmDownAll();
    void zawarudo();

private:
    QGraphicsScene *scene;
    QGraphicsView *view;
    QGraphicsPixmapItem **mapPix;
    Pacman *pacman;
    Blinky *blinky;
    Pinky *pinky;
    Clyde *clyde;
    Inky *inky;
    int **mapInt;
    int **mapCopy;
    int pacCount = 10;
    int ghostCount = 20;
    QTimer *timerPacman;
    QTimer *timerBlinky;
    QTimer *timerPinky;
    QTimer *timerClyde;
    QTimer *timerInky;
    QLabel *notice;
    bool start = false;
    bool timeOut = false;
public slots:
    void startSlots();
};

#endif // WIDGET_H
