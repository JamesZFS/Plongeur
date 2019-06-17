#include "gamescene.h"
#include "engine.h"

#include <Box2D/Box2D.h>


GameScene::GameScene() :
    m_world(new b2World(c_gravity)),
    m_pool(nullptr), m_diver(nullptr),
    m_engine(new Engine(m_world))
{
    setSceneRect(QRectF(mapFromB2(c_world_top_left), mapFromB2(c_world_bottom_right)));
    connect(m_engine, SIGNAL(stepped()), this, SLOT(advance()));
}

GameScene::~GameScene()
{
    delete m_world;
    delete m_engine;
}

void GameScene::clear()
{
    QGraphicsScene::clear();
    delete m_world;
    m_world = new b2World(c_gravity);
    m_pool = nullptr;
    m_diver = nullptr;
}

void GameScene::createPool()
{
    Q_ASSERT(!m_pool);
    b2BodyDef def;
    def.position = {0, 0};
    m_pool = new Pool(m_world->CreateBody(&def));
    addItem(m_pool);
    advance();
}

void GameScene::createDiver(const b2Vec2 &pos)
{
    Q_ASSERT(!m_diver); // diver should only be created once
    b2BodyDef def;
    def.position = pos;
    QVector<b2Body*> part_bodies;   // a diver has 6 body parts
    for (int i = 0; i < 6; ++i) {
        part_bodies << m_world->CreateBody(&def);  // create an empty b2body
    }
    // and then pass it to Diver() to construct a Diver with concrete shapes and physical attributes
    m_diver = new Diver(part_bodies);
    addItem(m_diver);   // to scene
    advance();
}

void GameScene::stopSimulation()
{
    m_engine->stopSimulation();
}

void GameScene::asyncSimulate()
{
    m_engine->syncSimulate();
}

void GameScene::syncSimulate()
{
    m_engine->syncSimulate();
}
