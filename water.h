#ifndef WATER_H
#define WATER_H

#include "constants.h"

#include <QGraphicsObject>

class b2ParticleSystem;
class b2ParticleGroup;
class b2Shape;


class Water : public QGraphicsObject
{
public:
    Water(b2ParticleSystem *particle_system, const b2Shape &water_shape, const b2Vec2 &pos);
private:
    b2ParticleSystem *m_particle_system;
    b2ParticleGroup *m_particle_group;

    // QGraphicsItem interface
public:
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
};

#endif // WATER_H
