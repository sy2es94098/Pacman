#include "widget.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget *w;
    if (argc == 1 || argc > 2)
    {
            std::cout << "Error in argc.\n";
            exit(0);
    }
    w= new Widget(argv[1]);
    w->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    w->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    w->setFixedSize(WIDTH, HEIGHT);
    w->setSceneRect(0, 0, WIDTH, HEIGHT);
    w->show();
   // w->startGame();

    return a.exec();
}
