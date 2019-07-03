#include "contactlistener.h"
#include "pool.h"
#include "diver.h"

#include <QDebug>
#include <QtMultimedia/QSoundEffect>

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
    auto diver_torso = dynamic_cast<DiverTorso*>(actor);
    if (!diver_torso) return;
    // diver hits water
    // play the splash here
    QSoundEffect effect;
    effect.setSource(QUrl::fromLocalFile("/resources/slapsh.mp3"));
    effect.setLoopCount(1);
    effect.setVolume(0.25f);
    effect.play();

    auto diver = diver_torso->diver();
    diver->m_state = Diver::e_IN_WATER;
    if (m_first_hit) {
        emit diverHitsWater();
        m_first_hit = false;
    }
    if (m_measuring) {
//        if (particleBodyContact->weight > 0.5)
//            ++m_splash;
        auto vp = particleSystem->GetVelocityBuffer()[particleBodyContact->index];
        auto vb = particleBodyContact->body->GetLinearVelocity();
        auto vr = vb - vp;
        auto d = diver->getDirection();
        m_splash += b2Abs(b2Dot(vr, {-d.y, d.x})) * particleBodyContact->weight;
        ++m_measure_count;
    }
}

void ContactListener::startMeasuring()
{
    m_measuring = true;
    m_splash = 0;
    m_measure_count = 0;
}

double ContactListener::stopMeasuring()
{
    m_measuring = false;
    return m_splash / m_measure_count;
}

bool ContactListener::isMeasuring() const
{
    return m_measuring;
}
