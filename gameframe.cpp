#include "gameframe.h"
#include "gamescene.h"
#include "ui_gameframe.h"

#include <QDebug>
#include <QPainter>
#include <QtEvents>

GameFrame::GameFrame(QWidget *parent) :
    QFrame(parent), ui(new Ui::GameFrame),
    m_scene(new GameScene),
    m_cur_key(""), m_score(0),
    m_is_started(false), m_is_paused(false), m_is_finished(false)
{
    ui->setupUi(this);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);
    ui->graphicsView->setBackgroundBrush(Qt::white);
    ui->graphicsView->scale(2, 2);
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
    m_scene->createDiver(b2Vec2_zero);
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
    switch (event->key()) {
    case Qt::Key_A:
        putKey("←");
        break;
    case Qt::Key_D:
        putKey("→");
        break;
    case Qt::Key_S:
        putKey("↓");
        break;
    case Qt::Key_W:
        putKey("↑");
        break;
    case Qt::Key_Space:
        putKey("[space]");
        break;
    default:
        QFrame::keyPressEvent(event);
    }
}

void GameFrame::keyReleaseEvent(QKeyEvent *event)
{
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
    ++m_score;    // score up
    update();
}
