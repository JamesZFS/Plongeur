#include "pool.h"
#include "constants.h"

#include <Box2D/Box2D.h>
#include <QPainter>

Pool::Pool(b2Body *body) : Actor(body)
{
    body->SetType(b2_staticBody);
    // todo create the fixtures of pool, see DiverHead::DiverHead for example
    b2FixtureDef def;
    // pool fixture params:
    def.density = 1;
    def.friction = 0.5;
    def.restitution = 0.5;
    // pool fixture shape:
//    b2Vec2 vertices[12];
//    vertices[0].Set(-50, 200);
//    vertices[1].Set(150, 200);
//    vertices[2].Set(150, 150);
//    vertices[3].Set(140, 150);
//    vertices[4].Set(140, 190);
//    vertices[5].Set(-40, 190);
//    vertices[6].Set(-40, 18);
//    vertices[7].Set(2, 18);
//    vertices[8].Set(2, 14);
//    vertices[9].Set(-40, 14);
//    vertices[10].Set(-40, 10);
//    vertices[11].Set(-50, 10);
    //    polygonShape.Set(vertices, 4);
    auto w = c_world_width, h = c_world_height, t = 0.04f*w;   // half thickness
    QVector<b2PolygonShape> shapes(4);
    shapes[0].SetAsBox(t, 0.4f*h, {t, 0.5f*h}, 0);
    shapes[1].SetAsBox(0.5f*w, t, {0.5f*w, 0.9f*h}, 0);
    shapes[2].SetAsBox(0.2*w, 0.5f*t, {0.2f*w, 0.2f*h}, 0);
    shapes[3].SetAsBox(t, 0.2f*h, {w-t, 0.7f*h}, 0);
    foreach (const b2PolygonShape &shape, shapes) {
        def.shape = &shape;
        body->CreateFixture(&def);
    }

    m_bbox = QRectF(mapFromB2(c_world_top_left), mapFromB2(c_world_bottom_right));
    m_bbox += QMarginsF(1, 1, 1, 1);
}

void Pool::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    // todo
    //    QPoint points[12]= {
    //        QPoint(-50, 200),
    //        QPoint(150, 200),
    //        QPoint(150, 150),
    //        QPoint(140, 150),
    //        QPoint(140, 190),
    //        QPoint(-40, 190),
    //        QPoint(-40, 18),
    //        QPoint(2, 18),
    //        QPoint(2, 14),
    //        QPoint(-40, 14),
    //        QPoint(-40, 10),
    //        QPoint(-50, 10)

    //    };
    painter->setPen(QPen(Qt::black, 0.2));
    painter->setBrush(QColor(150, 199, 185));
    drawB2Fixtures(m_body->GetFixtureList(), painter);
}

QRectF Pool::boundingRect() const
{
    return m_bbox;
}
