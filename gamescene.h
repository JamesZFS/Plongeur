#ifndef GAMESCENE_H
#define GAMESCENE_H

#include "constants.h"
#include "diver.h"

#include <QGraphicsScene>

class b2World;


class GameScene : public QGraphicsScene
{
public:
    GameScene();
    ~GameScene();

    void clear();
    void createDiver(const b2Vec2 &pos);

private:
    b2World *m_world;
    Diver *m_diver;
};

#endif // GAMESCENE_H
