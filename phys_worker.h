#ifndef PHYS_WORKER_H
#define PHYS_WORKER_H

#include <QObject>
#include "phys_data.h"

class PhysWorker : public QObject
{
    Q_OBJECT

public:

    explicit PhysWorker(QObject *parent = nullptr);

    PhysData compute(const PhysData& physData, float time);

signals:

public slots:

protected:

};

#endif // PHYS_WORKER_H
