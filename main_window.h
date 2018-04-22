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

    void draw(QVector2D location);

private:

    const int radiusBall_ = 50;

    Ui::MainWindow* ui;

    Database database_;

    Ball ball_;
    PhysEngine physEngine_;
    Renderer renderer_;

    QVector2D locationBall_;

    QString user_ = "kusstas";

protected:

    void paintEvent(QPaintEvent* event) override;

private slots:

    void on_btnStartStop_clicked(bool checked);
};

#endif // MAIN_WINDOW_H
