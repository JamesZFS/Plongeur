#include "contactlistener.h"
#include "pool.h"
#include "diver.h"

#include <QDebug>

void ContactListener::BeginContact(b2Contact *contact)
{
    auto actorA = (Actor*)contact->GetFixtureA()->GetBody()->GetUserData();
    auto actorB = (Actor*)contact->GetFixtureB()->GetBody()->GetUserData();
    auto diver_part = dynamic_cast<DiverPart*>(actorA);
    Actor *other = actorB;
    if (!diver_part) {
        diver_part = dynamic_cast<DiverPart*>(actorB);
        other = actorA;
    }
    if (!diver_part) return; // not relating to diver
    if (diver_part->diver()->m_state == Diver::e_IN_WATER) return;
    auto *pool = dynamic_cast<Pool*>(other);
    if (!pool) return;
    // diver landing on pool
    diver_part->diver()->m_state = Diver::e_ON_PLATFORM;
    diver_part->diver()->freeze(true);
}

void ContactListener::EndContact(b2Contact *contact)
{
    auto actorA = (Actor*)contact->GetFixtureA()->GetBody()->GetUserData();
    auto actorB = (Actor*)contact->GetFixtureB()->GetBody()->GetUserData();
    auto diver_part = dynamic_cast<DiverPart*>(actorA);
    Actor *other = actorB;
    if (!diver_part) {
        diver_part = dynamic_cast<DiverPart*>(actorB);
        other = actorA;
    }
    if (!diver_part) return; // not relating to diver
    auto *pool = dynamic_cast<Pool*>(other);
    if (!pool) return;
    // diver leaving pool
    diver_part->diver()->m_state = Diver::e_IN_AIR;
    diver_part->diver()->freeze(false);
}

void ContactListener::BeginContact(b2ParticleSystem *particleSystem, b2ParticleBodyContact *particleBodyContact)
{
    auto actor = (Actor*)particleBodyContact->body->GetUserData();
    auto diver_part = dynamic_cast<DiverPart*>(actor);
    if (!diver_part) return;
    // diver hits water
    diver_part->diver()->m_state = Diver::e_IN_WATER;
    if (m_first_hit) {
        emit diverHitsWater();
        m_first_hit = false;
    }
    if (m_measuring) {
        auto vp = particleSystem->GetVelocityBuffer()[particleBodyContact->index];
        auto vb = particleBodyContact->body->GetLinearVelocity();
        auto vr = vb - vp;
        m_splash += b2Abs(b2Dot(vr, particleBodyContact->normal)) * particleBodyContact->weight;
    }
}

void ContactListener::startMeasuring()
{
    m_measuring = true;
    m_splash = 0;
}

double ContactListener::stopMeasuring()
{
    m_measuring = false;
    return m_splash;
}

bool ContactListener::isMeasuring() const
{
    return m_measuring;
}
