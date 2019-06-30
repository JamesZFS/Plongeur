#ifndef GAMEFRAME_H
#define GAMEFRAME_H

#include <QFrame>
#include <QStack>
#include <QTimer>
#include <functional>

class GameScene;
class Actor;

namespace Ui {
class GameFrame;
}

typedef QVector<QPair<double, double>> ScoreTable;

// this class is responsible for taking control of the game logic
class GameFrame : public QFrame
{
    Q_OBJECT

public:
    explicit GameFrame(QWidget *parent = 0);
    ~GameFrame();

public slots:
    void setStart();    // start the game

    void setEnd();

    const ScoreTable &getScores() const;

signals:
    void closed();

protected:
    void keyPressEvent(QKeyEvent *event) override;

    void keyReleaseEvent(QKeyEvent *event) override;

    void closeEvent(QCloseEvent *event) override;

private slots:
    void calculateScore(double splash);

private:
    Ui::GameFrame *ui;
    GameScene *m_scene;
    QTimer m_timer;
    double m_cur_score;
    ScoreTable m_scores;   // history scores, difficulty scores and subjective scores
    bool m_hit_water;

    bool m_is_started, m_is_finished;

    QStack<Actor*> m_balls; // for debug

    std::function<void()> m_keep_doing;
    int m_pressed_key;

    // QObject interface
public:
    bool eventFilter(QObject *watched, QEvent *event) override;
};

#endif // GAMEFRAME_H
