#include "engine.h"
#include "constants.h"

#include <Box2D/Box2D.h>

Engine::Engine(b2World *world) : QThread(), m_world(world), m_timer(nullptr)
{
    connect(this, &Engine::stopAsync, this, [this](){   // --
        destroyTimer();
        this->quit();
    }, Qt::QueuedConnection);
}

Engine::~Engine()
{
    if (isRunning())
        emit stopAsync();
    else if (m_timer) {
        m_timer->stop();
        delete m_timer;
    }
}

void Engine::syncSimulate()
{
    // do the simulation in main thread
    Q_ASSERT(!isRunning());
    createTimer();
    m_timer->start();
}

void Engine::asyncSimulate()
{
    Q_ASSERT(!isRunning());
    start();    // logic goes to subthread --
}

void Engine::stopSimulation()
{
    if (this->isRunning()) {  // async
        emit stopAsync();   // see Engine::Engine()
        return;
    }
    // sync:
    destroyTimer();
}

void Engine::stepWorld()
{
    m_world->Step(c_time_step, c_velocity_iterations, c_position_iterations, c_particle_iterations);
    emit stepped();
}

void Engine::run()  // --
{
    createTimer();
    m_timer->start();
    this->exec();
}

void Engine::createTimer()
{
    Q_ASSERT(!m_timer);
    m_timer = new QTimer;
    m_timer->setInterval(1000 * c_time_step);
    connect(m_timer, SIGNAL(timeout()), this, SLOT(stepWorld()));
}

void Engine::destroyTimer()
{
    Q_ASSERT(m_timer);
    m_timer->stop();
    m_timer->deleteLater();
    m_timer = nullptr;
}
