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
#include <QPropertyAnimation>
#include <QSequentialAnimationGroup>

GameFrame::GameFrame(QWidget *parent) :
    QFrame(parent), ui(new Ui::GameFrame),
    m_scene(new GameScene),
    m_is_started(false), m_is_finished(false)
{
    ui->setupUi(this);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);
    ui->graphicsView->setBackgroundBrush(Qt::white);
    ui->graphicsView->scale(2, 2);

    m_scene->installEventFilter(this);
    connect(ui->bt_restart, SIGNAL(clicked(bool)), this, SLOT(setStart()));
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

void GameFrame::setStart()  // game entrance, start/restart
{
    m_scene->stopSimulation();
    m_scene->clear();
    m_is_started = true;
    m_is_finished = false;
    m_cur_score = 0;
    ui->graphicsView->setScene(m_scene);
    m_scene->createPool();
    b2PolygonShape shape;
    shape.SetAsBox(0.4*c_world_width, 0.1*c_world_height);
    m_scene->createWater(shape, {0.5f*c_world_width, 0.76f*c_world_height});
    m_scene->createDiver({5.5, 3.3});
    m_scene->asyncSimulate();
    connect(&m_scene->engine(), SIGNAL(diverHitsWater(double)), this, SLOT(calculateScore(double)));
}

void GameFrame::setEnd()
{
    m_is_finished = true;
    m_scene->stopSimulation();
    m_scene->engine().wait();
    m_scene->clear();
}

const ScoreTable &GameFrame::getScores() const
{
    return m_scores;
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
            m_keep_doing = [&diver](){ diver.turnLeft(); };
            m_timer.start();
            break;
        case Qt::Key_D:
            m_keep_doing = [&diver](){ diver.turnRight(); };
            m_timer.start();
            break;
        case Qt::Key_S:
            m_cur_score += diver.pose();
            break;
        case Qt::Key_W:
            m_keep_doing = [&diver]() { diver.swim(); };
            m_timer.start();
            break;
        case Qt::Key_Space:
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
    update();
    QFrame::keyPressEvent(event);
}

void GameFrame::closeEvent(QCloseEvent *event)
{
    setEnd();
    emit closed();
    event->accept();
}

void GameFrame::on_bt_remove_ball_clicked()
{
    if (m_balls.isEmpty())
        return;
    m_scene->destroyActor(m_balls.pop());
}

void GameFrame::calculateScore(double splash)
{
    qDebug() << "onDiverHitsWater";
    // calculate difficulty scores:
    QPair<double, double> score;
    auto rounds = fabs(m_scene->diver().getAngle()) / 360;
    m_cur_score += c_score_per_round * rounds;
    score.first = m_cur_score;
    double subj = 1.1 - 0.1*splash - 0.2*splash*splash;    // interpolation: (0.5,1) (1.0,0.8) (2.0,0.1)
    subj = std::max(subj, 0.1);
    subj = std::min(subj, 1.0);
    score.second = subj;
    m_cur_score *= subj;
    m_scores.push_back(score);
    // display scores:
    static const QFont score_font("arial", 8, 2);
    auto dst = m_scene->addText(QString("Difficulty Score: %1").arg(QString::number(score.first, 'f', 2)), score_font);
    auto sjt = m_scene->addText(QString("Subjective Score: %1%").arg(QString::number(score.second*100, 'f', 1)), score_font);
    auto tst = m_scene->addText(QString("Total Score: %1").arg(QString::number(m_cur_score, 'f', 2)), score_font);
    dst->setPos(1000, 0);
    sjt->setPos(1000, 0);
    tst->setPos(1000, 0);
    auto anims = new QSequentialAnimationGroup;
    auto pa = new QPropertyAnimation(dst, "pos");
    pa->setStartValue(QPointF(200, 10));
    pa->setEndValue(QPointF(100, 10));
    pa->setEasingCurve(QEasingCurve::OutQuad);
    pa->setDuration(300);
    anims->addAnimation(pa);
    pa = new QPropertyAnimation(sjt, "pos");
    pa->setStartValue(QPointF(200, 25));
    pa->setEndValue(QPointF(100, 25));
    pa->setEasingCurve(QEasingCurve::OutQuad);
    pa->setDuration(300);
    anims->addAnimation(pa);
    pa = new QPropertyAnimation(tst, "pos");
    pa->setStartValue(QPointF(200, 40));
    pa->setEndValue(QPointF(100, 40));
    pa->setEasingCurve(QEasingCurve::OutQuad);
    pa->setDuration(300);
    anims->addAnimation(pa);
    anims->start(QAbstractAnimation::DeleteWhenStopped);
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
