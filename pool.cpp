#include "pool.h"

#include <Box2D/Box2D.h>
#include <QPainter>

Pool::Pool(b2Body *body) : Actor(body)
{
    // todo create the fixtures of pool, see DiverHead::DiverHead for example
    b2FixtureDef def;
    // pool fixture params:
    def.density = 1;
    def.friction = 1;
    def.restitution = 1;
    // pool fixture shape:
    b2PolygonShape polygonShape;
    b2Vec2 vertices[12];
    vertices[0].Set(-50, 200);
    vertices[1].Set(150, 200);
    vertices[2].Set(150, 150);
    vertices[3].Set(140, 150);
    vertices[4].Set(140, 190);
    vertices[5].Set(-40, 190);
    vertices[6].Set(-40, 18);
    vertices[7].Set(2, 18);
    vertices[8].Set(2, 14);
    vertices[9].Set(-40, 14);
    vertices[10].Set(-40, 10);
    vertices[11].Set(-50, 10);
    polygonShape.Set(vertices, 4);
    def.shape = &polygonShape;
    body->CreateFixture(&def);





}

void Pool::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    // todo
    QPoint points[12]= {
        QPoint(-50, 200),
        QPoint(150, 200),
        QPoint(150, 150),
        QPoint(140, 150),
        QPoint(140, 190),
        QPoint(-40, 190),
        QPoint(-40, 18),
        QPoint(2, 18),
        QPoint(2, 14),
        QPoint(-40, 14),
        QPoint(-40, 10),
        QPoint(-50, 10)

    };
    // draw head
    painter->setPen(QPen(Qt::black, 0.2));
    painter->setBrush(QColor(150, 199, 185));
    painter->drawPolygon(points,12);
//    // draw eye
//    painter->rotate(-45);
//    painter->setPen(Qt::NoPen);
//    painter->setBrush(Qt::white);
}

QRectF Pool::boundingRect() const
{
    // todo
}
