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

    void draw(QVector2D const& location);

public slots:

    void doWork();
    void stop();

    void updateLocation(QVector2D const& location);

private:

    long m_periodMs;

    bool m_isWork;
    bool m_isShouldWork;

    QVector2D m_location;
};

#endif // RENDER_WORKER_H
