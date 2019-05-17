#include "gameframe.h"
#include "ui_gameframe.h"
#include <QDebug>
#include <QPainter>
#include <QtEvents>

GameFrame::GameFrame(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::GameFrame),
    isStarted(false), isPaused(false), isFinished(false),
    curKey(""), score(0)
{
    ui->setupUi(this);
}

GameFrame::~GameFrame()
{
    delete ui;
}

void GameFrame::setStart()
{
    isStarted = true;
    isPaused = false;
    isFinished = false;
    curKey = "";
    score = 0;
}

void GameFrame::togglePause()
{
    assert(isStarted);
    isPaused = !isPaused;
}

double GameFrame::getScore() const
{
    assert(isFinished);
    return score;
}

void GameFrame::paintEvent(QPaintEvent *event)  // paint game frame
{
    QPainter painter(this);
    QRect rect = contentsRect();
    QPoint size(50, 40);
    QRect textRect(rect.center() - size / 2, rect.center() + size / 2);
    painter.drawText(textRect, curKey);

    QFrame::paintEvent(event);
}

void GameFrame::keyPressEvent(QKeyEvent *event)
{
    // todo
    assert(isStarted);
    switch (event->key()) {
    case Qt::Key_Left:
        putKey("←");
        break;
    case Qt::Key_Right:
        putKey("→");
        break;
    case Qt::Key_Down:
        putKey("↓");
        break;
    case Qt::Key_Up:
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
    curKey = "";
    update();
    QFrame::keyPressEvent(event);
}

void GameFrame::closeEvent(QCloseEvent *event)
{
    isFinished = true;
    emit closed();
    event->accept();
}

void GameFrame::putKey(const QString &key)
{
    curKey = key;
    ++score;    // score up
    update();
}
