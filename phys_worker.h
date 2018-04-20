#ifndef PHYS_WORKER_H
#define PHYS_WORKER_H

#include <QObject>
#include "phys_data.h"

class PhysEngine;

class PhysWorker : public QObject
{
    Q_OBJECT

public:

    explicit PhysWorker(PhysEngine& owner, const PhysData& physData, QObject* parent = nullptr);

    long periodMs() const;
    void setPeriodMs(long periodMs);

    bool isWork() const;

signals:

    void started();
    void finished();

    void resultReady(PhysData physData);

public slots:

    void doWork();
    void stop();

private:

    bool isWork_;
    bool isShouldWork_;

    const PhysEngine& owner_;
    const PhysData& physData_;

    long periodMs_;

    PhysData compute(const PhysData& physData, const QVector2D& vectorG, float time);

};

#endif // PHYS_WORKER_H
