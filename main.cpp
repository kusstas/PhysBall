#include <QApplication>

#include "main_window.h"
#include "phys_data.h"

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);

    MainWindow mainWindow;
    mainWindow.show();

    return a.exec();
}
