#include "pool.h"
#include "constants.h"

#include <Box2D/Box2D.h>
#include <QPainter>
#include <QPixmap>

QPixmap *Pool::s_texture = nullptr;

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
    auto w = c_world_width, h = c_world_height, t = 0.04f*w;   // half thickness
    QVector<b2PolygonShape> shapes(5);
    shapes[0].SetAsBox(t, 0.4f*h, {t, 0.5f*h}, 0);
    shapes[1].SetAsBox(0.5f*w, t, {0.5f*w, 0.9f*h}, 0);
    shapes[2].SetAsBox(0.2*w, 0.5f*t, {0.2f*w, 0.2f*h}, 0);
    shapes[3].SetAsBox(0.2*w, 0.5f*t, {0.2f*w, 0.4f*h}, 0); // Second plateform
    shapes[4].SetAsBox(t, 0.2f*h, {w-t, 0.7f*h}, 0);
    foreach (const b2PolygonShape &shape, shapes) {
        def.shape = &shape;
        body->CreateFixture(&def);
    }

    m_bbox = QRectF(mapFromB2(c_world_top_left), mapFromB2(c_world_bottom_right));
    m_bbox += QMarginsF(5, 5, 5, 5);
    Q_ASSERT(s_texture);
}

void Pool::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(Qt::NoPen);
    painter->setBrush(*s_texture);
//    painter->setBrush(QColor(150, 199, 185));
    drawB2Fixtures(m_body->GetFixtureList(), painter);

}

QRectF Pool::boundingRect() const
{
    return m_bbox;
}
