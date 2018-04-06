#include <QApplication>

#include "ball.h"
#include "phys_engine.h"
#include "renderer.h"
#include "mediator.h"

#include "form.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Form form;
    form.show();

    Ball ball;
    ball.setVelocity(10, 20);
    ball.setBounce(0.95f);

    PhysEngine physEngine(ball);
    physEngine.setTopWall(100.0f);
    physEngine.setLeftWall(-100.0f);
    physEngine.setRightWall(100.0f);
    physEngine.setBottomWall(-200.0f);

    Renderer renderer;

    Mediator(renderer, physEngine);

    physEngine.start();
    renderer.start();

    return a.exec();
}
