#ifndef GAMESCENE_H
#define GAMESCENE_H

#include "constants.h"
#include "diver.h"
#include "pool.h"
#include "water.h"

#include <QGraphicsScene>

class b2World;
class Engine;


class GameScene : public QGraphicsScene
{
    Q_OBJECT
public:
    GameScene();
    ~GameScene();

    void clear();
    void createPool();
    void createDiver(const b2Vec2 &pos);
    void createWater(const b2Shape &shape, const b2Vec2 &pos);

    // input requests:
    Actor* createDebugBall(const b2Vec2 &pos);
    void destroyActor(Actor *actor);
    inline Diver &diver();

public slots:
    void asyncSimulate();
    void syncSimulate();
    void stopSimulation();

private:

    b2World *m_world;
    Pool *m_pool;
    Diver *m_diver;
    Water *m_water;

    Engine *m_engine;

};

#endif // GAMESCENE_H
