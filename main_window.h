#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QMainWindow>
#include <QThread>

#include "ball.h"
#include "phys_engine.h"
#include "renderer.h"

#include "database.h"

namespace Ui
{
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    explicit MainWindow(QWidget* parent = nullptr);
    virtual ~MainWindow();

public slots:

    void draw(QVector2D const& location);

private:

    int const m_radiusBall = 50;

    Ui::MainWindow* ui;

    QThread m_threadDb;
    Database m_database;

    Ball m_ball;
    PhysEngine m_physEngine;
    Renderer m_renderer;

    QVector2D m_locationBall;

protected:

    void paintEvent(QPaintEvent* event) override;

private slots:

    void on_btnStartStop_clicked(bool checked);
    void on_spinTimeScale_valueChanged(double timeScale);
    void on_spinBounce_valueChanged(double bounce);
};

#endif // MAIN_WINDOW_H
