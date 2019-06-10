#include "diver.h"

#include <Box2D/Box2D.h>
#include <QPainter>


DiverPart::DiverPart(b2Body * const body) : Actor(body)
{
    body->SetType(b2_dynamicBody);
    body->SetLinearDamping(c_diver_linear_damping);
    body->SetAngularDamping(c_diver_angular_damping);
    // fixture is created in subclasses' constructor
}


DiverHead::DiverHead(b2Body * const body) : DiverPart(body)
{
    b2FixtureDef def;
    // head fixture params:
    def.density = c_diver_density;
    def.friction = c_diver_friction;
    def.restitution = c_diver_restitution;
    // head fixture shape:
    b2CircleShape shape;
    shape.m_radius = 0.2;   // 0.2 meter
    def.shape = &shape;
    body->CreateFixture(&def);
}

QRectF DiverHead::boundingRect() const
{

}

void DiverHead::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Actor::paint(painter, option, widget);
}

Diver::Diver(QVector<b2Body *> part_bodies) :
    m_head(part_bodies[0]), m_torso(part_bodies[1]),
    m_l_arm(part_bodies[2]), m_r_arm(part_bodies[3]),
    m_l_leg(part_bodies[4]), m_r_leg(part_bodies[5])
{
    QGraphicsItem::setPos(0, 0);
    m_head.setParentItem(this);
    m_torso.setParentItem(this);
    m_l_arm.setParentItem(this);
    m_r_arm.setParentItem(this);
    m_l_leg.setParentItem(this);
    m_r_leg.setParentItem(this);
}

DiverTorso::DiverTorso(b2Body * const body) : DiverPart(body)
{

}

QRectF DiverTorso::boundingRect() const
{

}

void DiverTorso::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

}

DiverLimb::DiverLimb(b2Body * const body) : DiverPart(body)
{

}

QRectF DiverLimb::boundingRect() const
{

}

void DiverLimb::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

}
