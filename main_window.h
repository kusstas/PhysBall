#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QMainWindow>
#include "vector2.h"

namespace Ui
{
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    explicit MainWindow(QWidget* parent = 0);
    virtual ~MainWindow();

public slots:

    void drawBall(Vector2 location);

private:

    Ui::MainWindow* ui;
    Vector2 locationBall;

protected:

    virtual void paintEvent(QPaintEvent* e) Q_DECL_OVERRIDE;

};

#endif // MAIN_WINDOW_H
