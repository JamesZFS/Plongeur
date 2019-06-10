#include "pool.h"

Pool::Pool(b2Body *body) : Actor(body)
{
    // todo create the fixtures of pool, see DiverHead::DiverHead for example
}

void Pool::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    // todo
}

QRectF Pool::boundingRect() const
{
    // todo
}
