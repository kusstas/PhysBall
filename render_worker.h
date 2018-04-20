#ifndef RENDER_WORKER_H
#define RENDER_WORKER_H

#include <QObject>
#include <QVector2D>

class RenderWorker : public QObject
{
    Q_OBJECT

public:

    explicit RenderWorker(QObject* parent = nullptr);

    bool isWork() const;

    long periodMs() const;
    void setPeriodMs(long periodMs);

signals:

    void started();
    void finished();

    void draw(QVector2D location);

public slots:

    void doWork();
    void stop();

    void updateLocation(QVector2D location);

private:

    long periodMs_;

    bool isWork_;
    bool isShouldWork_;

    QVector2D location_;
};

#endif // RENDER_WORKER_H
