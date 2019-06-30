
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
    def.filter.categoryBits = c_head_category;
    def.filter.maskBits &= ~c_limb_category;
    // head fixture shape:
    b2CircleShape shape;
    shape.m_p.Set(0.0f, -0.6f);
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
    painter->drawEllipse(scaleFromB2(-0.2), scaleFromB2(-0.8), 2 * m_r,2 *  m_r);
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

    // joints:
    auto world = m_head.m_body->GetWorld();
    // Head to torso
    b2DistanceJointDef djd;
    djd.Initialize(m_head.m_body, m_torso.m_body,
                   m_head.m_body->GetWorldCenter(),
                   m_torso.m_body->GetPosition() + b2Vec2(0, -0.35f));
    djd.collideConnected = true;
    world->CreateJoint(&djd);

    b2RevoluteJointDef rjd;
    // Arm to torso
    rjd.Initialize(m_l_arm.m_body, m_torso.m_body,
                   m_torso.m_body->GetPosition() + b2Vec2(-0.1, -0.3));
    rjd.lowerAngle = 0.0f * b2_pi;
    rjd.upperAngle = 1.0f * b2_pi;
    rjd.enableLimit = true;
    world->CreateJoint(&rjd);

    // Leg to torso
    rjd.Initialize(m_l_leg.m_body, m_torso.m_body,
                   m_torso.m_body->GetPosition() + b2Vec2(0.0, 0.4));
    rjd.lowerAngle = 0.0f * b2_pi;
    rjd.upperAngle = 0.8f * b2_pi;
    world->CreateJoint(&rjd);

}

DiverTorso::DiverTorso(b2Body *body) : DiverPart(body)
{
    b2FixtureDef def;
    def.density = c_diver_density;
    def.friction = c_diver_friction;
    def.restitution = c_diver_restitution;
    //torso shape:
    b2PolygonShape shape;
    b2Vec2 vertices[12] = {};
    vertices[0].Set(-0.1f, 0.4f);
    vertices[1].Set(-0.2f, -0.4f);
    vertices[2].Set(0.2f, -0.4f);
    vertices[3].Set(0.1f, 0.4f);
    shape.Set(vertices, 4);
    def.shape = &shape;
    body->CreateFixture(&def);
    m_theight = scaleFromB2(0.4);
    m_twidth = scaleFromB2(0.2);
}

QRectF DiverTorso::boundingRect() const
{
    return QRectF(-m_twidth, m_theight, 2*m_twidth, 2*m_theight) + QMargins(1, 1, 1, 1);
}

void DiverTorso::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    // draw torso
    painter->setPen(QPen(Qt::black, 0.2));
    painter->setBrush(QColor(247, 199, 185));
    painter->drawRect(scaleFromB2(-0.2),scaleFromB2(-0.4), 2 * m_twidth, 2 * m_theight);


    // before implementing this, you should at least read the example DiverHead::paint above,
    // and learn the basic usage of QPainter (google it or press F1)
    // the other two params (option and widget) are useless in our project
    // you can uncomment the below function for a simple debug draw, implemented by James
    //    Actor::paint(painter, option, widget);
}

DiverLeg::DiverLeg(b2Body *body) : DiverPart(body)
{
    b2FixtureDef def;
    def.density = c_diver_density;
    def.friction = c_diver_friction;
    def.restitution = c_diver_restitution;
    //limb shape:
    b2PolygonShape shape;
    shape.SetAsBox(0.1f, 0.3f, b2Vec2(0.0f, 0.7f), 0.0f);
    def.filter.categoryBits = c_limb_category;
    def.filter.maskBits &= ~c_head_category;
    def.shape = &shape;
    body->CreateFixture(&def);
    m_theight = scaleFromB2(0.3);
    m_twidth = scaleFromB2(0.1);
}

QRectF DiverLeg::boundingRect() const
{
    return QRectF(-m_twidth, m_theight, 4*m_twidth, 4*m_theight) + QMargins(1, 1, 1, 1);
}

void DiverLeg::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(QPen(Qt::black, 0.2));
    painter->setBrush(QColor(247, 199, 185));
    painter->drawRect(scaleFromB2(-0.1), scaleFromB2(0.4), 2 * m_twidth, 2 * m_theight);

}

DiverArm::DiverArm(b2Body *body) : DiverPart(body)
{

    b2FixtureDef def;
    def.density = c_diver_density;
    def.friction = c_diver_friction;
    def.restitution = c_diver_restitution;
    //arm shape:
    b2PolygonShape shape;
    shape.SetAsBox(0.1f, 0.3f, b2Vec2(-0.1f, 0.0f), 0.0f);
    def.filter.categoryBits = c_limb_category;
    def.filter.maskBits &= ~c_head_category;
    def.shape = &shape;
    body->CreateFixture(&def);
    m_theight = scaleFromB2(0.3);
    m_twidth = scaleFromB2(0.1);
}

QRectF DiverArm::boundingRect() const
{
    return QRectF(-m_twidth, m_theight, 4*m_twidth, 4*m_theight) + QMargins(1, 1, 1, 1);
}

void DiverArm::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(QPen(Qt::black, 0.2));
    painter->setBrush(QColor(247, 199, 185));
    painter->drawRect(scaleFromB2(-0.2), scaleFromB2(-0.3), 2 * m_twidth, 2 * m_theight);
}

void Diver::jump() {
    static int jumpcount = 0;
    jumpcount++;
    if (jumpcount < 3) m_torso.m_body->SetLinearVelocity(b2Vec2(0, -25));
    else if (jumpcount == 3) m_torso.m_body->SetLinearVelocity(b2Vec2(70 * cosf(0.42 * b2_pi) / 3, -70 * sinf(0.42 * b2_pi) / 3));
}

void Diver::turnLeft() {
    m_torso.m_body->SetAngularVelocity(-20.0);

}

void Diver::turnRight() {
    m_torso.m_body->SetAngularVelocity(20.0);
}
