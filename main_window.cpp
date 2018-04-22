#include "main_window.h"
#include "ui_main_window.h"

#include <QStringBuilder>
#include <QPainter>
#include <QDebug>

#include "phys_data.h"

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent), ui(new Ui::MainWindow), physEngine_(ball_)
{
    ui->setupUi(this);

    // Load data from database
    if (database_.exist(user)) {
        ball_.setPhysData(database_.getData(user));
    }

    // Begin UI connect
    connect(&physEngine_, &PhysEngine::updateLocation, &renderer_, &Renderer::updateLocation, Qt::DirectConnection);
    connect(&renderer_, &Renderer::draw, this, &MainWindow::draw, Qt::DirectConnection);

    connect(&physEngine_, &PhysEngine::updateLocation, [=] (QVector2D loc) {
        QString format("Location: x: %1, y: %2;");
        QString log = format.arg(loc.x()).arg(loc.x());
        ui->txtLocation->setText(log);
    });
    // End UI connect

    // Setup phys engine
    physEngine_.setTopWall(300.0f);
    physEngine_.setLeftWall(-300.0f);
    physEngine_.setRightWall(300.0f);
    physEngine_.setBottomWall(-300.0f);
    physEngine_.setVectorG(QVector2D(0, -2800));

    draw(ball_.location());
}

MainWindow::~MainWindow()
{    
    physEngine_.stop();
    renderer_.stop();

    database_.set(user, ball_.physData());

    delete ui;
}

//---------------------------------------------------------

void MainWindow::draw(QVector2D location)
{
    locationBall_ = location + QVector2D(size().width() / 2, size().height() / 2);
    locationBall_.setY(size().height() - locationBall_.y());
    update();
}

//---------------------------------------------------------

void MainWindow::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    painter.drawEllipse(locationBall_.x(), locationBall_.y(), radiusBall_, radiusBall_);

    QMainWindow::paintEvent(event);
}

//---------------------------------------------------------

void MainWindow::on_btnStartStop_clicked(bool checked)
{
    if (checked) {
        physEngine_.start();
        renderer_.start();
        ui->btnStartStop->setText("&Stop");
    }
    else {
        physEngine_.stop();
        renderer_.stop();
        ui->btnStartStop->setText("&Start");
    }
}
