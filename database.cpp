#include "database.h"

#include <QSql>
#include <QSqlRecord>
#include <QSqlQuery>
#include <QSqlError>

#include <QStringBuilder>
#include <QFile>
#include <QDebug>

Database::Database(QObject* parent) : QObject(parent)
{
    m_isWriten = false;
}

//---------------------------------------------------------

void Database::setUser(QString user)
{
    m_user = user;
}

PhysData Database::getData() const
{
    PhysData data;
    QSqlQuery query;

    query.prepare("SELECT * FROM " % TABLE_NAME % " WHERE " % TABLE_KEY % " = :u");
    query.bindValue(":u", m_user);

    bool success = query.exec() && query.next();

    if (success) {
        QSqlRecord record = query.record();
        data.setLocation(record.value(TABLE_LOC_X).toFloat(), record.value(TABLE_LOC_Y).toFloat());
        data.setVelocity(record.value(TABLE_VEL_X).toFloat(), record.value(TABLE_VEL_Y).toFloat());
        data.setBounce(record.value(TABLE_BOUNCE).toFloat());
    }

    return data;
}

bool Database::exist() const
{
    QSqlQuery query;

    query.prepare("SELECT 1 FROM " % TABLE_NAME % " WHERE " % TABLE_KEY % " = :u");
    query.bindValue(":u", m_user);

    return query.exec() && query.next();
}

bool Database::isWriten() const
{
    return m_isWriten;
}

//---------------------------------------------------------

bool Database::write(PhysData const& data)
{
    m_isWriten = true;
    emit startedWrite();
    QSqlQuery query;

    if (exist()) {
        query.prepare("UPDATE " % TABLE_NAME % " SET " %
                      TABLE_LOC_X  % " = :lx, " % TABLE_LOC_Y % " = :ly, " %
                      TABLE_VEL_X  % " = :vx, " % TABLE_VEL_Y % " = :vy, " %
                      TABLE_BOUNCE % " = :b WHERE " % TABLE_KEY % " = :u");
    }
    else {
        query.prepare("INSERT INTO " %
                      TABLE_NAME   % "("  % TABLE_KEY   % ", " %
                      TABLE_LOC_X  % ", " % TABLE_LOC_Y % ", " %
                      TABLE_VEL_X  % ", " % TABLE_VEL_Y % ", " %
                      TABLE_BOUNCE % ") VALUES (:u, :lx, :ly, :vx, :vy, :b)");
    }

    query.bindValue(":u", m_user);
    query.bindValue(":lx", QString::number(data.location().x()));
    query.bindValue(":ly", QString::number(data.location().y()));
    query.bindValue(":vx", QString::number(data.velocity().x()));
    query.bindValue(":vy", QString::number(data.velocity().y()));
    query.bindValue(":b",  QString::number(data.bounce()));

    bool success = query.exec();
    m_isWriten = false;
    emit finishedWrite();
    return success;
}

//---------------------------------------------------------

void Database::connect()
{
    if (QFile(NAME).exists()) {
        open();
    }
    else {
        restore();
    }
}

void Database::close()
{
    m_database.close();
    qDebug() << "Database: closed";
}

//---------------------------------------------------------

bool Database::open()
{
    m_database = QSqlDatabase::addDatabase(TYPE);
    m_database.setDatabaseName(NAME);
    m_database.setHostName(HOST_NAME);

    bool success = m_database.open();

    if (success) {
        qDebug() << "Database: open";
    }

    return success;
}

bool Database::restore()
{
    if (open()) {
        return createTable();
    }
    qDebug() << "Database: restore failed!";
    return false;
}

bool Database::createTable()
{
    QSqlQuery query;
    bool success = query.exec("CREATE TABLE " % TABLE_NAME % " ( " %
                              TABLE_KEY    % " VARCHAR(25) PRIMARY KEY NOT NULL UNIQUE, " %
                              TABLE_LOC_X  % " FLOAT  NOT NULL, " %
                              TABLE_LOC_Y  % " FLOAT  NOT NULL, " %
                              TABLE_VEL_X  % " FLOAT  NOT NULL, " %
                              TABLE_VEL_Y  % " FLOAT  NOT NULL, " %
                              TABLE_BOUNCE % " FLOAT  NOT NULL )");
    if (success) {
        qDebug().noquote() << "Database: create " % TABLE_NAME;
    }
    else {
        qDebug().noquote() << "Database: error of create " % TABLE_NAME;
        qDebug().noquote() << query.lastError().text();
    }
    return success;
}
