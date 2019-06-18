#ifndef WATER_H
#define WATER_H

#include "constants.h"

#include <QGraphicsObject>
#include <QTimer>

class b2ParticleSystem;
class b2ParticleGroup;
class b2Shape;


class Water : public QGraphicsObject
{
    Q_OBJECT
public:
    Water(b2ParticleSystem *particle_system, const b2Shape &water_shape, const b2Vec2 &pos);

private slots:
    void updateBoundingRect();

private:
    b2ParticleSystem *m_particle_system;
    b2ParticleGroup *m_particle_group;
    QRectF m_bbox;
    QTimer m_timer;

    // QGraphicsItem interface
public:
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

    void advance(int phase) override;
};

#endif // WATER_H
