#ifndef REALTIME_DATABASE_H
#define REALTIME_DATABASE_H

#include <QObject>
#include <QThread>

#include "database.h"

class RealtimeDatabase : public QObject
{
Q_OBJECT

public:

    explicit RealtimeDatabase(QObject* parent = nullptr);

    bool exist() const;
    PhysData getData() const;
    void setUser(QString user);

signals:

    void write(PhysData const& data);

public slots:

    void connect();
    void update(PhysData const& data);
    void close();

private slots:

    void finishedWrite();

private:

    QThread m_thread;
    Database m_db;
    PhysData m_data;
    bool m_newData;
    bool m_closed;
};

#endif // REALTIME_DATABASE_H
