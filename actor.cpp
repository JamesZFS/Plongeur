#include "actor.h"

#include <Box2D/Box2D.h>
#include <QPainter>
#include <QtMath>


Actor::Actor(b2Body * const body) : m_body(body)
{
    Q_ASSERT(body->GetFixtureList() == nullptr);
    // body's fixture should be initialized in the Actor's subclasses' constructor
    body->SetUserData(this);    // link b2body to its Actor pointer
    body->SetLinearDamping(c_actor_linear_damping);
    body->SetAngularDamping(c_actor_angular_damping);
    body->SetGravityScale(1);
}

Actor::~Actor()
{
    // b2body should be destroyed by b2world, not here.
}

QRectF Actor::boundingRect() const
{
    return getBoundingRectFromB2(m_body);
}

// default draw for dev time
void Actor::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    drawB2Fixtures(m_body->GetFixtureList(), painter);
}

void Actor::advance(int phase)
{
    // synchronize the behavior of Actor with b2body
    if (phase == 0) return;
    QGraphicsItem::setPos(mapFromB2(m_body->GetPosition()));
    QGraphicsItem::setRotation(qRadiansToDegrees(m_body->GetAngle()));
}

QPolygonF getPolygonFromB2(const b2PolygonShape &polygon)
{
    QPolygonF res;
    for (int i = 0; i < polygon.GetVertexCount(); ++i) {
        auto &v = polygon.GetVertex(i);
        res << mapFromB2(v);
    }
    return res;
}

QRectF getBoundingRectFromB2(const b2Body *body)
{
    QRectF bound;
    for (auto fixture = body->GetFixtureList(); fixture; fixture = fixture->GetNext()) {
        QRectF fix_bound;
        switch (fixture->GetType()) {
        case b2Shape::e_circle: {
            auto circle = (b2CircleShape*)fixture->GetShape();
            qreal r = scaleFromB2(circle->m_radius);
            fix_bound = QRectF(-r, -r, 2*r, 2*r);
            break;
        }
        case b2Shape::e_polygon: {
            auto polygon = (b2PolygonShape*)fixture->GetShape();
            fix_bound = getPolygonFromB2(*polygon).boundingRect();
            break;
        }
        default:
            qFatal("unsupported b2Shape in Actor::getBoundingRectFromB2()!");
            break;
        }
        bound = bound.united(fix_bound);
    }
    return bound + QMargins(1, 1, 1, 1);
}

void drawB2Fixtures(const b2Fixture *fixture_list, QPainter *painter)
{
    for (auto fixture = fixture_list; fixture; fixture = fixture->GetNext()) {
        switch (fixture->GetType()) {
        case b2Shape::e_circle: {
            auto circle = (b2CircleShape*)fixture->GetShape();
            qreal r = scaleFromB2(circle->m_radius);
            painter->drawEllipse({}, r, r);
            break;
        }
        case b2Shape::e_polygon: {
            auto polygon = (b2PolygonShape*)fixture->GetShape();
            painter->drawPolygon(getPolygonFromB2(*polygon));
            break;
        }
        default:
            qFatal("unsupported b2Shape in Actor::drawBody()!");
            break;
        }
    }
}
