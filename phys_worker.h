#ifndef PHYS_WORKER_H
#define PHYS_WORKER_H

#include <QObject>
#include "phys_data.h"

class PhysEngine;

class PhysWorker : public QObject
{
    Q_OBJECT

public:

    explicit PhysWorker(PhysEngine& owner, PhysData const& physData, QObject* parent = nullptr);

    long periodMs() const;
    void setPeriodMs(long periodMs);

    bool isWork() const;

signals:

    void started();
    void finished();

    void resultReady(PhysData const& physData);

public slots:

    void doWork();
    void stop();

private:

    bool m_isWork;
    bool m_isShouldWork;

    const PhysEngine& m_owner;
    const PhysData& m_physData;

    long m_periodMs;

    PhysData compute(PhysData const& physData, QVector2D const& vectorG, float time);

};

#endif // PHYS_WORKER_H
