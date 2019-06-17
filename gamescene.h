#ifndef GAMESCENE_H
#define GAMESCENE_H

#include "constants.h"
#include "diver.h"

#include <QGraphicsScene>
#include <QTimer>

class b2World;
class Engine;


class GameScene : public QGraphicsScene
{
    Q_OBJECT
public:
    GameScene();
    ~GameScene();

    void clear();
    void createDiver(const b2Vec2 &pos);

public slots:
    void asyncSimulate(float32 duration);   // sec
    void syncSimulate(float32 duration);

signals:
    void simulationFinished();

private:
    b2World *m_world;
    Diver *m_diver;
    Engine *m_engine;
    QTimer m_timer;
};

#endif // GAMESCENE_H
