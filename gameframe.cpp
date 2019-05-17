#include "gameframe.h"
#include "ui_gameframe.h"
#include <QDebug>
#include <QPainter>
#include <QtEvents>

GameFrame::GameFrame(QWidget *parent) :
    QFrame(parent),
    ui(new Ui::GameFrame), scene(-200, -200, 400, 400),
    isStarted(false), isPaused(false), isFinished(false),
    curKey(""), score(0)
{
    ui->setupUi(this);
    ui->graphicsView->setScene(&scene);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);
    ui->graphicsView->setBackgroundBrush(QColor(230, 200, 167));
}

GameFrame::~GameFrame()
{
    delete ui;
}

void GameFrame::setStart()  // game entrance
{
    isStarted = true;
    isPaused = false;
    isFinished = false;
    curKey = "";
    score = 0;
    scene.clear();
    scene.addEllipse(-100, -100, 200, 200);
    scene.addRect(50, 50, 10, 10);
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
//    qDebug() << "GameFrame::paintEvent()";
    ui->labelStatus->setText(QString("You've pressed: %0").arg(curKey));
    QFrame::paintEvent(event);
}

void GameFrame::keyPressEvent(QKeyEvent *event)
{
    // todo
    assert(isStarted);
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
