#include "main_window.h"
#include "ui_main_window.h"

#include <QPainter>

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent), ui(new Ui::MainWindow), physEngine_(ball_)
{
    ui->setupUi(this);

    connect(ui->pushButtonStart, &QPushButton::clicked, &physEngine_, &PhysEngine::start);
    connect(ui->pushButtonStop, &QPushButton::clicked, &physEngine_, &PhysEngine::stop);

    connect(ui->pushButtonStart, &QPushButton::clicked, &renderer_, &Renderer::start);
    connect(ui->pushButtonStop, &QPushButton::clicked, &renderer_, &Renderer::stop);

    connect(&physEngine_, &PhysEngine::updateLocation, &renderer_, &Renderer::updateLocation, Qt::DirectConnection);
    connect(&renderer_, &Renderer::draw, this, &MainWindow::draw, Qt::DirectConnection);

    physEngine_.setTopWall(300.0f);
    physEngine_.setLeftWall(-300.0f);
    physEngine_.setRightWall(300.0f);
    physEngine_.setBottomWall(-300.0f);
    physEngine_.setVectorG(QVector2D(0, -2800));

    draw(ball_.location());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::draw(QVector2D location)
{
    locationBall_ = location + QVector2D(size().width() / 2, size().height() / 2);
    locationBall_.setY(size().height() - locationBall_.y());
    update();
}

void MainWindow::paintEvent(QPaintEvent* event)
{
    QMainWindow::paintEvent(event);

    QPainter painter;
    painter.begin(this);
    painter.drawEllipse(locationBall_.x(), locationBall_.y(), radiusBall_, radiusBall_);
    painter.end();

    QMainWindow::paintEvent(event);
}

void MainWindow::closeEvent(QCloseEvent* event)
{
    physEngine_.stop();
    renderer_.stop();
    QMainWindow::closeEvent(event);
}
