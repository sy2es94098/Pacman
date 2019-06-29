#ifndef PACMAN_H
#define PACMAN_H

#include <QObject>
#include <QGraphicsTextItem>
#include <QKeyEvent>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <unistd.h>

#define WIDTH 608
#define HEIGHT 702
#define SIZEX 21
#define SIZEY 19


class Pacman : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:

    Pacman(int **mapInt, QGraphicsPixmapItem **mapPix, QGraphicsScene *scene);
    void keyPressEvent(QKeyEvent *event);
    void initializePacman();
    int getPacmanI(void);
    int getPacmanJ(void);
    void setDefaut();
    int getScore();
    int scaredState();
    void setScared();
    int getDirection();
    void setDirection(int n);
    void incrScore();
    void printScore();
    void setLives();
    int getPoint();

private:
    int posI;
    int posJ;
    int direction;
    int **mapInt;
    int lives;

    int checkMove(int posI, int posJ);
    int scared;
    int counter;
    int score;
    int points;
    void updateScene();
    QGraphicsPixmapItem **mapPix;
    QGraphicsScene *scene;
    QGraphicsTextItem *text;
    QGraphicsTextItem *message;

public slots:
    void moveSlots();
};

#endif // PACMAN_H
