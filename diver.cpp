#include "diver.h"

#include <Box2D/Box2D.h>
#include <QPainter>


DiverPart::DiverPart(b2Body *body) : Actor(body)
{
    body->SetType(b2_dynamicBody);
    body->SetLinearDamping(c_diver_linear_damping);
    body->SetAngularDamping(c_diver_angular_damping);
    // fixture is created in subclasses' constructor
}


DiverHead::DiverHead(b2Body *body) : DiverPart(body)
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
    m_r = scaleFromB2(shape.m_radius);
}

// bounding rect example
QRectF DiverHead::boundingRect() const
{
    return QRectF(-m_r, -m_r, 2*m_r, 2*m_r) + QMargins(1, 1, 1, 1);
    // QMargins is for expanding the rect slightly, to sure the bound is affluent
    // you can press F1 on QMargins to see its usage
}


// paint method example
void DiverHead::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    // draw head
    painter->setPen(QPen(Qt::black, 0.2));
    painter->setBrush(QColor(247, 199, 185));
    painter->drawEllipse({}, m_r, m_r);
    // draw eye
    painter->rotate(-45);
    painter->setPen(Qt::NoPen);
    painter->setBrush(Qt::white);
    painter->drawEllipse({0.5*m_r, 0}, 0.3*m_r, 0.3*m_r);
    painter->setBrush(Qt::black);
    painter->drawEllipse({0.7*m_r, 0}, 0.1*m_r, 0.1*m_r);
}

Diver::Diver(QVector<b2Body *> part_bodies) :
    m_head(part_bodies[0]), m_torso(part_bodies[1]),
    m_l_arm(part_bodies[2]), m_r_arm(part_bodies[3]),
    m_l_leg(part_bodies[4]), m_r_leg(part_bodies[5])
{
    QGraphicsItem::setPos(0, 0);
    QGraphicsItem::setRotation(0);
    m_head.setParentItem(this);
    m_torso.setParentItem(this);
    m_l_arm.setParentItem(this);
    m_r_arm.setParentItem(this);
    m_l_leg.setParentItem(this);
    m_r_leg.setParentItem(this);
}

DiverTorso::DiverTorso(b2Body *body) : DiverPart(body)
{
// todo create the fixtures of torso, see DiverHead::DiverHead for example
}

QRectF DiverTorso::boundingRect() const
{
// todo
}

void DiverTorso::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    // before implementing this, you should at least read the example DiverHead::paint above,
    // and learn the basic usage of QPainter (google it or press F1)
    // the other two params (option and widget) are useless in our project
    // you can uncomment the below function for a simple debug draw, implemented by James
//    Actor::paint(painter, option, widget);
}

DiverLimb::DiverLimb(b2Body *body) : DiverPart(body)
{
// todo create the fixtures of limb, see DiverHead::DiverHead for example
}

QRectF DiverLimb::boundingRect() const
{
// todo
}

void DiverLimb::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
// todo
}
