#include "main_window.h"
#include "ui_main_window.h"

#include <QInputDialog>
#include <QStringBuilder>
#include <QPainter>
#include <QDebug>

#include "phys_data.h"

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent), ui(new Ui::MainWindow), m_physEngine(m_ball)
{
    ui->setupUi(this);

    // Get user nickname
    QInputDialog dialogInput(this);
    QString user;
    while (user.size() < 4) {
        user = dialogInput.getText(nullptr, "Input dialog", "Enter nickname: ");
    }
    dialogInput.close();

    m_database.connect();

    m_database.setUser(user);
    // Load data from database
    if (m_database.exist()) {
        m_ball.setPhysData(m_database.getData());
        qDebug().noquote() << "Database: loaded data by " % user % " - " % m_ball.physData().toString();
    }
    else {
        qDebug().noquote() << "Database: new user - " % user;
    }


    connect(&m_physEngine, &PhysEngine::updateLocation, &m_renderer, &Renderer::updateLocation, Qt::DirectConnection);
    connect(&m_physEngine, &PhysEngine::updatePhysData, &m_database, &RealtimeDatabase::update, Qt::DirectConnection);
    connect(&m_renderer, &Renderer::draw, this, &MainWindow::draw);

    // Begin UI connect
    connect(&m_physEngine, &PhysEngine::updateLocation, [=] (QVector2D loc) {
        QString format("Location: x: %1, y: %2;");
        QString log = format.arg(loc.x()).arg(loc.x());
        ui->txtLocation->setText(log);
    });
    // End UI connect

    // Setup phys engine
    m_physEngine.setTopWall(300.0f);
    m_physEngine.setLeftWall(-300.0f);
    m_physEngine.setRightWall(300.0f);
    m_physEngine.setBottomWall(-300.0f);
    m_physEngine.setVectorG(QVector2D(0, -2800));

    ui->spinTimeScale->setValue(m_physEngine.timeScale());
    ui->spinBounce->setValue(m_ball.bounce());

    m_locationBall = m_ball.location();
    m_renderer.updateLocation(m_locationBall);
    draw(m_locationBall);
}

MainWindow::~MainWindow()
{    
    m_physEngine.stop();
    m_renderer.stop();
    m_database.close();

    delete ui;
}

//---------------------------------------------------------

void MainWindow::draw(QVector2D const& location)
{
    m_locationBall = location + QVector2D(size().width() / 2, size().height() / 2);
    m_locationBall.setY(size().height() - m_locationBall.y());
    update();
}

//---------------------------------------------------------

void MainWindow::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    painter.drawEllipse(m_locationBall.x(), m_locationBall.y(), m_radiusBall, m_radiusBall);

    QMainWindow::paintEvent(event);
}

//---------------------------------------------------------

void MainWindow::on_btnStartStop_clicked(bool checked)
{
    if (checked) {
        m_physEngine.start();
        m_renderer.start();
        ui->btnStartStop->setText("&Stop");
    }
    else {
        m_physEngine.stop();
        m_renderer.stop();
        ui->btnStartStop->setText("&Start");
    }
}

void MainWindow::on_spinTimeScale_valueChanged(double timeScale)
{
    m_physEngine.setTimeScale(timeScale);
}

void MainWindow::on_spinBounce_valueChanged(double bounce)
{
    m_ball.setBounce(bounce);
}
