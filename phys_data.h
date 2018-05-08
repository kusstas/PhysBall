#ifndef PHYS_DATA_H
#define PHYS_DATA_H

#include <QVector2D>
#include <QString>

struct PhysData
{
public:

    PhysData();

    QVector2D const& location() const;
    QVector2D const& velocity() const;
    float bounce() const;

    void setLocation(QVector2D const& location);
    void setLocation(float x, float y);

    void setVelocity(QVector2D const& velocity);
    void setVelocity(float x, float y);
    void setBounce(float bounce);

    QString toString() const;

private:

    QVector2D m_location;
    QVector2D m_velocity;
    float m_bounce;

};

#endif // PHYS_DATA_H
