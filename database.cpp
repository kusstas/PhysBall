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
    if (QFile(NAME).exists()) {
        open();
    }
    else {
        restore();
    }
}

//---------------------------------------------------------

PhysData Database::getData(QString user)
{
    PhysData data;
    QSqlQuery query;

    query.prepare("SELECT * FROM " % TABLE_NAME % " WHERE " % TABLE_KEY % " = :u");
    query.bindValue(":u", user);

    bool success = query.exec() && query.next();

    if (success) {
        QSqlRecord record = query.record();
        qDebug().noquote() << record.value(TABLE_KEY).toString();
        data.setLocation(record.value(TABLE_LOC_X).toFloat(), record.value(TABLE_LOC_Y).toFloat());
        data.setVelocity(record.value(TABLE_VEL_X).toFloat(), record.value(TABLE_VEL_Y).toFloat());
        data.setBounce(record.value(TABLE_BOUNCE).toFloat());
    }

    qDebug().noquote() << data.toString();

    return data;
}

bool Database::exist(QString user) const
{
    QSqlQuery query;

    query.prepare("SELECT 1 FROM " % TABLE_NAME % " WHERE " % TABLE_KEY % " = :u");
    query.bindValue(":u", user);

    return query.exec() && query.next();
}

//---------------------------------------------------------

bool Database::set(QString user, const PhysData& data)
{
    QSqlQuery query;

    if (exist(user)) {
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

    query.bindValue(":u", user);
    query.bindValue(":lx", QString::number(data.location().x()));
    query.bindValue(":ly", QString::number(data.location().y()));
    query.bindValue(":vx", QString::number(data.velocity().x()));
    query.bindValue(":vy", QString::number(data.velocity().y()));
    query.bindValue(":b",  QString::number(data.bounce()));

    bool success = query.exec();

    if (success) {
        qDebug().noquote() << "Database: setup record by " % user % " - " % data.toString();
    }
    else {
        qDebug().noquote() << "Database: failed record by " % user % " - " % data.toString();
    }

    return success;
}

//---------------------------------------------------------

bool Database::open()
{
    database_ = QSqlDatabase::addDatabase(TYPE);
    database_.setDatabaseName(NAME);
    database_.setHostName(HOST_NAME);

    bool success = database_.open();

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
