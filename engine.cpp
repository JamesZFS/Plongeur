#include "engine.h"
#include "contactlistener.h"

#include <QDebug>
#include <Box2D/Box2D.h>

Engine::Engine(b2World *world) : QThread(),
    m_world(world), m_timer(nullptr)
{
    m_contact_listener = new ContactListener;
    m_world->SetContactListener(m_contact_listener);
    connect(m_contact_listener, &ContactListener::diverHitsWater, this, [this](){ emit diverHitsWater(); }, Qt::QueuedConnection);
}

Engine::~Engine()
{
    delete m_contact_listener;
    if (isRunning()) {
        m_should_stop = true;
        wait(1000);
    }
    else if (m_timer) {
        m_timer->stop();
        delete m_timer;
    }
}

bool Engine::isBusy()
{
    return isRunning() || m_timer;
}

void Engine::syncSimulate()
{
    // do the simulation in main thread
    Q_ASSERT(!isRunning());
    qDebug() << "sync: " << QThread::currentThreadId();
    m_should_stop = false;
    createTimer();
    m_timer->start();
}

void Engine::asyncSimulate()
{
    Q_ASSERT(!isRunning());
    m_should_stop = false;
    start();    // logic goes to subthread --
}

void Engine::stopSimulation()
{
    if (!isBusy())
        return;
    m_should_stop = true;
}

void Engine::requestTransform(b2Body *object, b2Vec2 position, float32 angle)
{
    m_transform_requests.insert(object, {position, angle});
}

void Engine::requestImpulse(b2Body *object, b2Vec2 impulse)
{
    m_impulse_requests.insert(object, impulse);
}

void Engine::stepWorld()
{
    if (m_should_stop) {
        m_should_stop = false;
        destroyTimer();
        quit();
        return;
    }
    handleRequests();
    m_world->Step(c_time_step, c_velocity_iterations, c_position_iterations, c_particle_iterations);
    emit stepped();
}

void Engine::handleRequests()
{
    // deal with transform requests here
    for (auto it = m_transform_requests.cbegin(); it != m_transform_requests.cend(); ++it) {
        b2Body *object = it.key();
        object->SetTransform(it.value().first, it.value().second);
    }
    m_transform_requests.clear();

    for (auto it = m_impulse_requests.cbegin(); it != m_impulse_requests.cend(); ++it) {
        b2Body *object = it.key();
        object->ApplyLinearImpulse(it.value(), object->GetWorldCenter(), true);
    }
    m_impulse_requests.clear();
}

void Engine::run()  // --
{
    qDebug() << "async: " << QThread::currentThreadId();
    createTimer();
    m_timer->start();
    this->exec();
}

void Engine::createTimer()
{
    Q_ASSERT(!m_timer);
    m_timer = new QTimer;
    m_timer->setInterval(1000 * c_time_step);
    connect(m_timer, SIGNAL(timeout()), this, SLOT(stepWorld()), Qt::DirectConnection);
}

void Engine::destroyTimer()
{
    Q_ASSERT(m_timer);
    m_timer->stop();
    m_timer->deleteLater();
    m_timer = nullptr;
}
