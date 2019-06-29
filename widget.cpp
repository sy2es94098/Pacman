#include "widget.h"
#include "game.h"
Widget::Widget(char *file_name)
{
    std::ifstream input;
    std::string temp;
    int nb;

    mapInt = new int *[SIZEX];
    mapPix = new QGraphicsPixmapItem *[SIZEX];
    mapCopy = new int *[SIZEX];
    for (int i = 0; i < SIZEX; i++)
    {
        mapInt[i] = new int[SIZEY];
        mapPix[i] = new QGraphicsPixmapItem[SIZEY];
        mapCopy[i] = new int[SIZEY];
    }

    input.open(file_name);
    if (input.is_open())
    {
        nb = 0;
        while (std::getline(input, temp))
        {
            if (temp.length() != SIZEY)
            {
                std::cout << "File error.\n";
                exit(0);
            }
            if (checkFileInp(temp))
            {
                std::cout << "File error Inp.\n";
                exit(0);
            }
            writeLineMap(mapInt[nb], temp);
            writeLineMap(mapCopy[nb], temp);
            nb++;
        }
        if (nb != SIZEX)
        {
            std::cout << "File error.\n";
            exit(0);
        }
        input.close();
    }
    else
    {
        std::cout << "File missing: " << file_name << ".\n";
        exit(0);
    }
    scene = new QGraphicsScene();
    view = new QGraphicsView();
    this->setScene(scene);
    createMap();
    QGraphicsView::setStyleSheet("background-color:black;");
    pacman = new Pacman(mapInt, mapPix, scene);
    pacman->setFlag(QGraphicsPixmapItem::ItemIsFocusable);
    pacman->setFocus();
    blinky = new Blinky(scene, mapInt, pacman);
    pinky = new Pinky(scene, mapInt, pacman);
    clyde = new Clyde(scene, mapInt, pacman);
    inky = new Inky(scene, mapInt, pacman);
    notice = new QLabel("Press [R] to start the game",this);
    notice->setGeometry(200,350,180,40);
    notice->setStyleSheet("background-color:white;");
    notice->show();
    blinky->setFriends(pinky, clyde, inky);
    pinky->setFriends(blinky, clyde, inky);
    clyde->setFriends(blinky, pinky, inky);
    inky->setFriends(blinky, pinky, clyde);
}

Widget::Widget()
{

}


Widget::~Widget()
{
    delete scene;
    delete view;
    delete pacman;
    delete pinky;
    delete clyde;
    delete blinky;
    delete inky;
    delete timerPacman;
    delete timerBlinky;
    delete timerPinky;
    delete timerClyde;
    delete timerInky;
    for (int i = 0; i < SIZEX; i++)
    {
        for (int j = 0; j < SIZEY; j++)
        {
            delete mapPix[i];
            delete mapInt[i];
        }
    }
    delete []mapPix;
    delete []mapInt;
}

int Widget::checkFileInp(std::string str)
{
    int i;

    i = 0;
    while (str[i])
    {
        if ((str[i] < '0' || str[i] > '4') && (str[i] < 'a' || str[i] > 'd'))
            return (1);
        i++;
    }
    return (0);
}

void Widget::startGame()
{
    timerBlinky = new QTimer();
    timerPinky = new QTimer();
    timerClyde = new QTimer();
    timerPacman = new QTimer();
    timerInky = new QTimer();
    QObject::connect(timerPacman, SIGNAL(timeout()), pacman, SLOT(moveSlots()));
    QObject::connect(timerInky, SIGNAL(timeout()), inky, SLOT(moveGhostSlots()));
    QObject::connect(timerClyde, SIGNAL(timeout()), clyde, SLOT(moveGhostSlots()));
    QObject::connect(timerBlinky, SIGNAL(timeout()), blinky, SLOT(moveGhostSlots()));
    QObject::connect(timerPinky, SIGNAL(timeout()), pinky, SLOT(moveGhostSlots()));
    timerPacman->start(200);
    timerInky->start(400);
    timerClyde->start(400);
    timerBlinky->start(400);
    timerPinky->start(400);
}

void Widget::speedUpPac()
{
    pacCount--;
    timerPacman->start(pacCount*20);
    if( (pacCount*20)<=20)
    {
        timerPacman->start(20);
    }

}

void Widget::speedUpGhost()
{
    ghostCount--;
    timerInky->start(ghostCount*40);
    timerClyde->start(ghostCount*40);
    timerBlinky->start(ghostCount*40);
    timerPinky->start(ghostCount*40);
    if((ghostCount*40)<=40)
    {
        timerInky->start(40);
        timerClyde->start(40);
        timerBlinky->start(40);
        timerPinky->start(40);
    }
}


void Widget::madeInHeaven()
{
    speedUpPac();
    speedUpGhost();
}


void Widget::calmDownPac()
{
    pacCount++;
    timerPacman->start(pacCount*20);
}

void Widget::calmDownGhost()
{
    ghostCount++;
    timerInky->start(ghostCount*40);
    timerClyde->start(ghostCount*40);
    timerBlinky->start(ghostCount*40);
    timerPinky->start(ghostCount*40);

}

void Widget::calmDownAll()
{
    calmDownPac();
    calmDownGhost();
}

void Widget::zawarudo()
{
    if(timeOut == false)
    {
        timerInky->stop();
        timerClyde->stop();
        timerPinky->stop();
        timerBlinky->stop();
        timeOut = true;
    }
    else if(timeOut == true)
    {
        timerInky->start(ghostCount*40);
        timerClyde->start(ghostCount*40);
        timerBlinky->start(ghostCount*40);
        timerPinky->start(ghostCount*40);
        timeOut = false;
    }
}

void Widget::createMap()
{
    for (int i = 0; i < SIZEX; i++)
    {
        for (int j = 0; j < SIZEY; j++)
        {
            if (mapCopy[i][j] == 1)
            {
                mapPix[i][j].setPixmap(QPixmap(":/pacimg/bluestone.png"));
                mapPix[i][j].setPos(j * 32, i * 32);
                scene->addItem(&(mapPix[i][j]));
            }
            if (mapCopy[i][j] == 3)
            {
                mapPix[i][j].setPixmap(QPixmap(":/pacimg/ball.png"));
                mapPix[i][j].setPos(j * 32, i * 32);
                scene->addItem(&(mapPix[i][j]));
            }
            if (mapCopy[i][j] == 4)
            {
                mapPix[i][j].setPixmap(QPixmap(":/pacimg/energizer.png"));
                mapPix[i][j].setPos(j * 32, i * 32);
                scene->addItem(&(mapPix[i][j]));
            }
            if (mapCopy[i][j] == 'a')
            {
                mapPix[i][j].setPixmap(QPixmap(":/pacimg/bomb.png"));
                mapPix[i][j].setPos(j * 32, i * 32);
                scene->addItem(&(mapPix[i][j]));
            }
            if (mapCopy[i][j] == 'b')
            {
                mapPix[i][j].setPixmap(QPixmap(":/pacimg/rocket.png"));
                mapPix[i][j].setPos(j * 32, i * 32);
                scene->addItem(&(mapPix[i][j]));
            }
            if (mapCopy[i][j] == 'c')
            {
                mapPix[i][j].setPixmap(QPixmap(":/pacimg/ghostzzz.png"));
                mapPix[i][j].setPos(j * 32, i * 32);
                scene->addItem(&(mapPix[i][j]));
            }
            if (mapCopy[i][j] == 'd')
            {
                mapPix[i][j].setPixmap(QPixmap(":/pacimg/zzz.png"));
                mapPix[i][j].setPos(j * 32, i * 32);
                scene->addItem(&(mapPix[i][j]));
            }
        }
    }
}

void Widget::writeLineMap(int *map, std::string str)
{
    for (int i = 0; i < SIZEY; i++)
        map[i] = str[i] - '0';
}

void Widget::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_R)
    {
        pacman->initializePacman();
        blinky->initialize();
        pinky->initialize();
        inky->initialize();
        clyde->initialize();
        storeMap();
        if(start == false)
        {
            startGame();
            start = true;
        }
        notice->hide();
    }
    if (event->key() == Qt::Key_F1)
    {
        madeInHeaven();
    }
    if (event->key() == Qt::Key_F2)
    {
        calmDownAll();
    }
    if (event->key() == Qt::Key_F3)
    {
        speedUpPac();
    }
    if (event->key() == Qt::Key_F4)
    {
        calmDownPac();
    }
    if (event->key() == Qt::Key_F5)
    {
        speedUpGhost();
    }
    if (event->key() == Qt::Key_F6)
    {
        calmDownGhost();
    }
    if (event->key() == Qt::Key_Z)
    {
        zawarudo();
    }
    if (event->key() == Qt::Key_Left)
    {
        pacman->setDirection(3);
        pacman->setPixmap(QPixmap(":/pacimg/pacman_left.png"));
    }
    if (event->key() == Qt::Key_Right)
    {
        pacman->setDirection(4);
        pacman->setPixmap(QPixmap(":/pacimg/pacman_right.png"));
    }
    if (event->key() == Qt::Key_Down)
    {
        pacman->setDirection(2);
        pacman->setPixmap(QPixmap(":/pacimg/pacman_down.png"));
    }
    if (event->key() == Qt::Key_Up)
    {
        pacman->setDirection(1);
        pacman->setPixmap(QPixmap(":/pacimg/pacman_up.png"));
    }
}

void Widget::storeMap()
{
    for(int i = 0 ; i < SIZEX ; ++i )
    {
        for(int j = 0 ; j < SIZEY ; ++j)
        {
            mapInt[i][j] = mapCopy[i][j];
        }
    }
    createMap();
}
