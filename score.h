#ifndef SCORE_H
#define SCORE_H

#include <QString>
#include <QFont>
#include <QGraphicsItem>
#include <QGraphicsTextItem>

class   Stats : public QGraphicsTextItem
{
private:
    int  score;
public:
                Stats(QGraphicsItem *parent = NULL);
    void        ft_increase();
};


#endif // SCORE_H
