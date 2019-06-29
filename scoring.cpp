#include "scoring.h"

Scoring::Scoring(QGraphicsItem *parent) : QGraphicsTextItem(parent)
{
    score = 0;
    setPlainText("Score: " + QString::number(score));
    setDefaultTextColor("0x00e27d09");
    setFont(QFont("times", 15));
}

void Scoring::increase()
{
    setPlainText("Score: " + QString::number(score));
    setDefaultTextColor("0x00e27d09");
    setFont(QFont("times", 15));

}
