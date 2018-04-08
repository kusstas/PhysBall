#include "main_window.h"
#include "ui_main_window.h"

#include <QPainter>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::drawBall(Vector2 location)
{
    locationBall = location + Vector2(size().width() / 2, size().height() / 2);
    locationBall.y = size().height() - locationBall.y;
    qDebug() << location.x << ' ' << location.y;
    update();
}

void MainWindow::paintEvent(QPaintEvent* e)
{
    QMainWindow::paintEvent(e);

    QPainter painter;
    painter.begin(this);
    painter.drawEllipse(locationBall.x, locationBall.y, 30, 30);
    painter.end();
}
