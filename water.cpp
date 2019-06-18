#include "water.h"
#include "actor.h"

#include <Box2D/Box2D.h>
#include <QPainter>
#include <QRandomGenerator>

Water::Water(b2ParticleSystem *particle_system, const b2Shape &water_shape, const b2Vec2 &pos) :
    m_particle_system(particle_system)
{
    particle_system->SetGravityScale(1.0f);
    particle_system->SetRadius(c_water_particle_radius);
    particle_system->SetDensity(c_water_density);
    particle_system->SetDamping(c_water_damping);
    b2ParticleGroupDef def;

    def.shape = &water_shape;
    def.position = pos;
    m_particle_group = particle_system->CreateParticleGroup(def);

    updateBoundingRect();
    m_timer.setInterval(1000);
    connect(&m_timer, SIGNAL(timeout()), this, SLOT(updateBoundingRect()));
    m_timer.start();
}

void Water::updateBoundingRect()
{
    QPolygonF hull;
    b2Vec2 *pos = m_particle_system->GetPositionBuffer();
    for (int i = 0; i < m_particle_system->GetParticleCount(); ++i) {
        hull << mapFromB2(pos[i]);
    }
    m_bbox = hull.boundingRect();
    m_bbox += QMarginsF(1, 1, 1, 1);
}

QRectF Water::boundingRect() const
{
    return m_bbox;
}

void Water::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setPen(Qt::NoPen);
    painter->setOpacity(0.7);
    painter->setBrush(QColor(150, 190, 250));
    b2Vec2 *pos = m_particle_system->GetPositionBuffer();
    auto r = scaleFromB2(m_particle_system->GetRadius());
    for (int i = 0; i < m_particle_system->GetParticleCount(); ++i) {
        painter->drawEllipse(mapFromB2(pos[i]), r, r);
    }
}

void Water::advance(int phase)
{
    QGraphicsItem::advance(1);
}
