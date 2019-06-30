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
    void startMeasuring();  // start measuring water splash
    double stopMeasuring(); // return the total splash
    bool isMeasuring() const;

signals:
    void diverHitsWater();

private:
    bool m_first_hit = true;
    bool m_measuring = false;
    double m_splash = 0;
    size_t m_measure_count = 0;
};

#endif // CONTACTLISTENER_H
