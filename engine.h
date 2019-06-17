#ifndef ENGINE_H
#define ENGINE_H

#include <QThread>
#include <QTimer>

class b2World;
class b2Body;


class Engine : public QThread
{
    Q_OBJECT
public:
    Engine(b2World *world);
    ~Engine();

signals:
    void stepped(); // emitted after every call of stepWorld()
    void stopAsync();   // temporary signal

public slots:
    void syncSimulate();    // in main thread
    void asyncSimulate();   // in sub thread --
    void stopSimulation();

protected slots:
    void stepWorld();   // --

protected:
    void run() override;    // subthread --
    void createTimer();
    void destroyTimer();

private:
    b2World *m_world;
    QTimer *m_timer;

};

#endif // ENGINE_H
