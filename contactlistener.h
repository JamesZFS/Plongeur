#ifndef CONTACTLISTENER_H
#define CONTACTLISTENER_H

#include <Box2D/Box2D.h>
#include <QObject>

class ContactListener : public QObject, public b2ContactListener
{
    Q_OBJECT
public:
    ContactListener() = default;

    // b2ContactListener interface
public:
    void BeginContact(b2Contact *contact) override;
    void EndContact(b2Contact *contact) override;
    void BeginContact(b2ParticleSystem *particleSystem, b2ParticleBodyContact *particleBodyContact) override;

signals:
    void diverHitsWater();

private:
    bool m_flag = true;
};

#endif // CONTACTLISTENER_H
