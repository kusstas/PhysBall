#include <QApplication>
#include <QThread>
#include <iostream>

#include "ball.h"
#include "phys_engine.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Ball ball;

    PhysEngine physEngine(ball);
    physEngine.setTopWall(100.0f);
    physEngine.setLeftWall(-100.0f);
    physEngine.setRightWall(100.0f);
    physEngine.setBottomWall(900.0f);

    physEngine.start();

    while (true) {
        std::cout << ball.getLocation().x << ' ' << ball.getLocation().y << std::endl;
    }
    return 0;
}
