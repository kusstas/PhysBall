#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>
#include <QSqlDatabase>

#include "phys_data.h"

class Database : public QObject
{
    Q_OBJECT

public:

    explicit Database(QObject* parent = nullptr);

    PhysData getData(QString user) const;
    bool exist(QString user) const;

public slots:

    bool set(QString user, const PhysData& data);
    void close();

private:

    mutable QSqlDatabase database_;

    const QString TYPE         = "QSQLITE";
    const QString NAME         = "phys_ball.db";
    const QString HOST_NAME    = "PhysBall";
    const QString TABLE_NAME   = "PhysData";

    const QString TABLE_KEY    = "User";
    const QString TABLE_LOC_X  = "LocationX";
    const QString TABLE_LOC_Y  = "LocationY";
    const QString TABLE_VEL_X  = "VelocityX";
    const QString TABLE_VEL_Y  = "VelocityY";
    const QString TABLE_BOUNCE = "Bounce";

    bool open();
    bool restore();
    bool createTable();
};

#endif // DATABASE_H
