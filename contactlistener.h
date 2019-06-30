#ifndef CONTACTLISTENER_H
#define CONTACTLISTENER_H

#include <Box2D/Box2D.h>

class ContactListener : public b2ContactListener
{
public:
    ContactListener() = default;

    // b2ContactListener interface
public:
    void BeginContact(b2Contact *contact) override;
    void EndContact(b2Contact *contact) override;
    void BeginContact(b2ParticleSystem *particleSystem, b2ParticleBodyContact *particleBodyContact) override;
};

#endif // CONTACTLISTENER_H
