#ifndef REALTIME_DATABASE_H
#define REALTIME_DATABASE_H

#include <QObject>
#include "database.h"

class RealtimeDatabase : public QObject
{
Q_OBJECT

public:

    explicit RealtimeDatabase(QObject* parent = nullptr);
    void setUser(QString user);

public slots:

    void connect();
    void update(PhysData const& data);
    void close();

private:

    Database m_db;
    PhysData m_data;
    bool m_newData;
};

#endif // REALTIME_DATABASE_H
