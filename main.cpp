#include <QApplication>

#include "ball.h"
#include "phys_engine.h"
#include "renderer.h"
#include "mediator.h"

#include "main_window.h"

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);

    Ball ball;
    PhysEngine physEngine(ball);
    physEngine.setTopWall(300.0f);
    physEngine.setLeftWall(-300.0f);
    physEngine.setRightWall(300.0f);
    physEngine.setBottomWall(-300.0f);
    physEngine.setVectorG(Vector2(0, -10));
    physEngine.setTimeScale(50);

    MainWindow mainWindow;
    mainWindow.show();

    Renderer renderer(mainWindow);

    Mediator(renderer, physEngine);

    physEngine.start();
    renderer.start();

    return a.exec();
}
