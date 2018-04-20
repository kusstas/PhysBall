#ifndef PHYS_DATA_H
#define PHYS_DATA_H

#include <QVector2D>

class QTextStream;

struct PhysData
{
public:

    PhysData();

    const QVector2D& location() const;
    const QVector2D& velocity() const;
    float bounce() const;

    void setLocation(const QVector2D& location);
    void setLocation(float x, float y);

    void setVelocity(const QVector2D& velocity);
    void setVelocity(float x, float y);
    void setBounce(float bounce);

private:

    QVector2D location_;
    QVector2D velocity_;
    float bounce_;

};

#endif // PHYS_DATA_H
