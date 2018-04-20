#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QMainWindow>
#include <QThread>

#include "ball.h"
#include "phys_engine.h"
#include "renderer.h"

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

    void draw(QVector2D location);

private:

    const int radiusBall_ = 50;

    Ui::MainWindow* ui;

    Ball ball_;
    PhysEngine physEngine_;
    Renderer renderer_;

    QVector2D locationBall_;

protected:

    void paintEvent(QPaintEvent* event) override;
    void closeEvent(QCloseEvent* event) override;

};

#endif // MAIN_WINDOW_H
