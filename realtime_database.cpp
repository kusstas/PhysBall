#include "realtime_database.h"

RealtimeDatabase::RealtimeDatabase(QObject* parent) : QObject(parent)
{
    m_db.moveToThread(&m_thread);
    m_newData = false;
    m_closed = false;

    QObject::connect(this, &RealtimeDatabase::write, &m_db, &Database::write);
    QObject::connect(&m_db, &Database::finishedWrite, this, &RealtimeDatabase::finishedWrite);
}

bool RealtimeDatabase::exist() const
{
    return m_db.exist();
}

PhysData RealtimeDatabase::getData() const
{
    return m_db.getData();
}

void RealtimeDatabase::setUser(QString user)
{
    m_db.setUser(user);
}

void RealtimeDatabase::connect()
{
    m_closed = false;
    m_thread.start();
    m_db.connect();
}

void RealtimeDatabase::update(PhysData const& data)
{
    m_data = data;
    m_newData = true;

    if (!m_db.isWriten() && !m_closed) {
        emit write(m_data);
    }
}

void RealtimeDatabase::close()
{
    m_closed = true;
    m_thread.quit();
    m_thread.wait();
    m_db.close();
}

void RealtimeDatabase::finishedWrite()
{
    if (m_newData && !m_closed) {
        emit update(m_data);
        m_newData = false;
    }
}
