#ifndef GAMEFRAME_H
#define GAMEFRAME_H

#include <QFrame>
#include <QGraphicsScene>

namespace Ui {
class GameFrame;
}

class GameFrame : public QFrame
{
    Q_OBJECT

public:
    explicit GameFrame(QWidget *parent = 0);
    ~GameFrame();

    void setStart();    // start the game

    void togglePause(); // pause / continue

    double getScore() const;

signals:
    void closed();

protected:
    void paintEvent(QPaintEvent *event) override;

    void keyPressEvent(QKeyEvent *event) override;

    void keyReleaseEvent(QKeyEvent *event) override;

    void closeEvent(QCloseEvent *event) override;

private:
    Ui::GameFrame *ui;

    QGraphicsScene *scene;

    bool isStarted, isPaused, isFinished;
    QString curKey; // current key pressed
    double score;

    void putKey(const QString &key);

};

#endif // GAMEFRAME_H
