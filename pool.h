#ifndef POOL_H
#define POOL_H

#include "actor.h"


class Pool : public Actor
{
public:
    Pool(b2Body *body);

    // QGraphicsItem interface
public:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
    QRectF boundingRect() const override;
};

#endif // POOL_H
