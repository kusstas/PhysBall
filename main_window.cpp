#include "main_window.h"
#include "ui_main_window.h"

#include <QInputDialog>
#include <QStringBuilder>
#include <QPainter>
#include <QDebug>

#include "phys_data.h"

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent), ui(new Ui::MainWindow), physEngine_(ball_)
{
    ui->setupUi(this);

    // Get user nickname
    QInputDialog dialogInput(this);
    while (user_.size() < 4) {
        user_ = dialogInput.getText(nullptr, "Input dialog", "Enter nickname: ");
    }
    dialogInput.close();

    database_.connect();

    // Load data from database
    if (database_.exist(user_)) {
        ball_.setPhysData(database_.getData(user_));
        qDebug().noquote() << "Database: loaded data by " % user_ % " - " % ball_.physData().toString();
    }
    else {
        qDebug().noquote() << "Database: new user - " % user_;
    }


    connect(&physEngine_, &PhysEngine::updateLocation, &renderer_, &Renderer::updateLocation);
    connect(&renderer_, &Renderer::draw, this, &MainWindow::draw);

    // Begin UI connect
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

    ui->spinTimeScale->setValue(physEngine_.timeScale());
    ui->spinBounce->setValue(ball_.bounce());

    locationBall_ = ball_.location();
    renderer_.updateLocation(locationBall_);
    draw(locationBall_);
}

MainWindow::~MainWindow()
{    
    physEngine_.stop();
    renderer_.stop();

    database_.set(user_, ball_.physData());
    database_.close();

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

void MainWindow::on_spinTimeScale_valueChanged(double timeScale)
{
    physEngine_.setTimeScale(timeScale);
}

void MainWindow::on_spinBounce_valueChanged(double bounce)
{
    ball_.setBounce(bounce);
}
