#ifndef ENGINE_H
#define ENGINE_H

#include <QThread>
#include <QTimer>
#include <QMap>
#include "constants.h"

class b2World;
class b2Body;


class Engine : public QThread
{
    Q_OBJECT
public:
    Engine(b2World *world);
    ~Engine();
    bool isBusy();

signals:
    void stepped(); // emitted after every call of stepWorld()

public slots:
    void syncSimulate();    // in main thread
    void asyncSimulate();   // in sub thread --
    void stopSimulation();
    void requestTransform(b2Body *object, b2Vec2 position, float32 angle);
    void requestImpulse(b2Body *object, b2Vec2 impulse);

protected slots:
    void stepWorld();   // --
    void handleRequests();

protected:
    void run() override;    // subthread --
    void createTimer();
    void destroyTimer();

private:
    b2World *m_world;
    QTimer *m_timer;
    QMap<b2Body *, QPair<b2Vec2, float32>> m_transform_requests;
    QMap<b2Body *, b2Vec2> m_impulse_requests;

    bool m_should_stop; // shared memory
};

#endif // ENGINE_H
