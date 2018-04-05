#include <QApplication>

#include <QThread>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QThread threadDraw;
    QThread threadPhys;

    return a.exec();
}
