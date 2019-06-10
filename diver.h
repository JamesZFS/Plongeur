#ifndef DIVER_H
#define DIVER_H

#include "actor.h"

class DiverPart : public Actor
{
public:
    DiverPart(b2Body *const body);
};


class DiverHead : public DiverPart
{
public:
    DiverHead(b2Body *const body);

    // QGraphicsItem interface
public:
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
};


class DiverTorso : public DiverPart
{
public:
    DiverTorso(b2Body *const body);

    // QGraphicsItem interface
public:
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
};


class DiverLimb : public DiverPart
{
public:
    DiverLimb(b2Body *const body);

    // QGraphicsItem interface
public:
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
};


// Diver is just an aggregation of 6 DiverParts
class Diver : public QGraphicsObject
{
public:
    Diver(QVector<b2Body *> part_bodies);  // initialize via 6 empty bodies created by b2world

private:
    void setPos() {}  // hiding
    void setRotation() {}   // hiding

    DiverHead m_head;
    DiverTorso m_torso;
    DiverLimb m_l_arm, m_r_arm;
    DiverLimb m_l_leg, m_r_leg;

    // QGraphicsItem interface
public:
    QRectF boundingRect() const override { return {}; }
    void paint(QPainter *, const QStyleOptionGraphicsItem *, QWidget *) override {}
};

#endif // DIVER_H
