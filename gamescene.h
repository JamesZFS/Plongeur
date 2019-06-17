#ifndef GAMESCENE_H
#define GAMESCENE_H

#include "constants.h"
#include "diver.h"
#include "pool.h"

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
    void createWater(const b2PolygonShape &shape);

public slots:
    void asyncSimulate();
    void syncSimulate();
    void stopSimulation();

private:
    b2World *m_world;
    Pool *m_pool;
    Diver *m_diver;
    Engine *m_engine;
};

#endif // GAMESCENE_H
