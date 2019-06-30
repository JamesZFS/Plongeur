#include "gameframe.h"
#include "gamescene.h"
#include "ui_gameframe.h"
#include "engine.h"

#include "constants.h"

#include <QDebug>
#include <QPainter>
#include <QtEvents>
#include <QGraphicsSceneMouseEvent>
#include <Box2D/Collision/Shapes/b2PolygonShape.h>

GameFrame::GameFrame(QWidget *parent) :
    QFrame(parent), ui(new Ui::GameFrame),
    m_scene(new GameScene),
    m_timer(),
    m_cur_key(""), m_score(0),
    m_is_started(false), m_is_paused(false), m_is_finished(false)
{
    ui->setupUi(this);
    ui->bt_stop->setEnabled(false);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);
    ui->graphicsView->setBackgroundBrush(Qt::white);
    ui->graphicsView->scale(2, 2);

    m_scene->installEventFilter(this);
    connect(ui->bt_sync, &QPushButton::clicked, this, [this](){
        m_scene->syncSimulate();
        ui->bt_sync->setEnabled(false);
        ui->bt_async->setEnabled(false);
        ui->bt_stop->setEnabled(true);
    });
    connect(ui->bt_async, &QPushButton::clicked, this, [this](){
        m_scene->asyncSimulate();
        ui->bt_sync->setEnabled(false);
        ui->bt_async->setEnabled(false);
        ui->bt_stop->setEnabled(true);
    });
    connect(ui->bt_stop, &QPushButton::clicked, this, [this](){
        m_scene->stopSimulation();
        ui->bt_sync->setEnabled(true);
        ui->bt_async->setEnabled(true);
        ui->bt_stop->setEnabled(false);
    });
    connect(&m_timer, &QTimer::timeout, this, [this](){ m_keep_doing(); });
    m_timer.setInterval(1000 * c_time_step);
    m_keep_doing = nullptr;
    m_pressed_key = Qt::Key_unknown;
}

GameFrame::~GameFrame()
{
    delete ui;
    delete m_scene;
}

void GameFrame::setStart()  // game entrance
{
    m_is_started = true;
    m_is_paused = false;
    m_is_finished = false;
    m_cur_key = "";
    m_score = 0;
    ui->graphicsView->setScene(m_scene);
    m_scene->createDiver({5.5, 3.3});
    m_scene->createPool();
    b2PolygonShape shape;
    shape.SetAsBox(0.4*c_world_width, 0.1*c_world_height);
    m_scene->createWater(shape, {0.5f*c_world_width, 0.76f*c_world_height});
}

void GameFrame::setEnd()
{
    m_is_finished = true;
    m_scene->clear();
}

void GameFrame::togglePause()
{
    Q_ASSERT(m_is_started);
    m_is_paused = !m_is_paused;
}

double GameFrame::getScore() const
{
    Q_ASSERT(m_is_finished);
    return m_score;
}

void GameFrame::paintEvent(QPaintEvent *event)  // paint game frame
{
    //    qDebug() << "GameFrame::paintEvent()";
    ui->labelStatus->setText(QString("You've pressed: %0").arg(m_cur_key));
    QFrame::paintEvent(event);
}

void GameFrame::keyPressEvent(QKeyEvent *event)
{
    // todo
    Q_ASSERT(m_is_started);
    auto &diver = m_scene->diver();
    if (m_pressed_key == Qt::Key_unknown) {
        m_pressed_key = event->key();
        switch (m_pressed_key) {
        case Qt::Key_A:
            putKey("←");
            m_keep_doing = [&diver](){ diver.turnLeft(); };
            m_timer.start();
            break;
        case Qt::Key_D:
            putKey("→");
            m_keep_doing = [&diver](){ diver.turnRight(); };
            m_timer.start();
            break;
        case Qt::Key_S:
            putKey("↓");
            diver.pose();
            break;
        case Qt::Key_W:
            putKey("↑");
            m_keep_doing = [&diver]() { diver.swim(); };
            m_timer.start();
            break;
        case Qt::Key_Space:
            putKey("[space]");
            diver.jump();
            break;
        default:
            QFrame::keyPressEvent(event);
        }
    }
    else
        QFrame::keyPressEvent(event);
}

void GameFrame::keyReleaseEvent(QKeyEvent *event)
{
    // Mark the key as released.
    m_pressed_key = Qt::Key_unknown;
    m_timer.stop();
    m_cur_key = "";
    update();
    QFrame::keyPressEvent(event);
}

void GameFrame::closeEvent(QCloseEvent *event)
{
    setEnd();
    emit closed();
    event->accept();
}

void GameFrame::putKey(const QString &key)
{
    m_cur_key = key;
    update();
}

void GameFrame::on_bt_remove_ball_clicked()
{
    if (m_balls.isEmpty())
        return;
    m_scene->destroyActor(m_balls.pop());
}

bool GameFrame::eventFilter(QObject *watched, QEvent *event)
{
    if (watched == m_scene && event->type() == QEvent::GraphicsSceneMousePress) {
        auto me = (QGraphicsSceneMouseEvent*) event;
        auto pos = mapToB2(me->scenePos());
        qDebug() << "mouse clicked at" << pos.x << pos.y;
        if (me->button() == Qt::LeftButton) {
            auto ball = dynamic_cast<Actor*>(m_scene->itemAt(me->scenePos(), {}));
            if (!ball) goto finally;
            m_scene->engine().requestImpulse(&ball->body(), {0, -3.f});
        }
        else {
            // add debug ball
            auto ball = m_scene->createDebugBall(pos);
            m_balls.push(ball);
        }
    }
    finally:
    return QFrame::eventFilter(watched, event);
}
