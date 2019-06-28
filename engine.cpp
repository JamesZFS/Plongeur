#include "engine.h"
#include "constants.h"

#include <QDebug>
#include <Box2D/Box2D.h>

Engine::Engine(b2World *world) : QThread(),
    m_world(world), m_timer(nullptr)
{
}

Engine::~Engine()
{
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

void Engine::stepWorld()
{
    if (m_should_stop) {
        m_should_stop = false;
        destroyTimer();
        quit();
        return;
    }
    m_world->Step(c_time_step, c_velocity_iterations, c_position_iterations, c_particle_iterations);
    emit stepped();
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
