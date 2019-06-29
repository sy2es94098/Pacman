#ifndef SCORING_H
#define SCORING_H

#include <QString>
#include <QFont>
#include <QGraphicsItem>
#include <QGraphicsTextItem>

class Scoring : public QGraphicsTextItem
{

public:
    Scoring(QGraphicsItem *parent = nullptr);
    void increase();
private:
    int score;

};

#endif // SCORING_H
