#include "water.h"

#include <Box2D/Box2D.h>

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
}

QRectF Water::boundingRect() const
{

}

void Water::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

}
