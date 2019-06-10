#include "gamescene.h"

#include <Box2D/Box2D.h>


GameScene::GameScene() : m_world(new b2World(c_gravity)), m_diver(nullptr)
{
    setSceneRect(QRectF(mapFromB2(c_world_top_left), mapFromB2(c_world_bottom_right)));
}

GameScene::~GameScene()
{
    delete m_world;
    delete m_diver;
}

void GameScene::clear()
{
    QGraphicsScene::clear();
    delete m_world;
    m_world = new b2World(c_gravity);
    m_diver = nullptr;
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
