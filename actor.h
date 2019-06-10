#ifndef ACTOR_H
#define ACTOR_H

#include "constants.h"

#include <QGraphicsObject>

class b2World;
class b2Body;
class b2Fixture;
class b2PolygonShape;

template<typename T>
inline T scaleFromB2(T x)   // scale liquidfun coordinate 10 times to scene coordinate
{ return 10*x; }

inline QPointF mapFromB2(const b2Vec2 &pos)
{ return {scaleFromB2(pos.x), scaleFromB2(pos.y)}; }

QPolygonF getPolygonFromB2(const b2PolygonShape &polygon);
QRectF getBoundingRectFromB2(const b2Body *body);
void drawB2Fixtures(const b2Fixture *fixture_list, QPainter *painter);    // debug draw

class Actor : public QGraphicsObject
{
    Q_OBJECT
public:
    explicit Actor(b2Body *const body);
    virtual ~Actor();
    // QGraphicsItem interface
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) override;
    void advance(int phase) override;

protected:
    b2Body *const m_body;   // weak pointer to its b2body

private:
    // hiding methods:
    void setPos() {}
    void setRotation() {}
    void setScale() {}
    void setTransform() {}

};

#endif // ACTOR_H
