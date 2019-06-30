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

class GameFrame : public QFrame
{
    Q_OBJECT

public:
    explicit GameFrame(QWidget *parent = 0);
    ~GameFrame();

    void setStart();    // start the game

    void setEnd();

    void togglePause(); // pause / continue

    double getScore() const;

signals:
    void closed();

protected:
    void paintEvent(QPaintEvent *event) override;

    void keyPressEvent(QKeyEvent *event) override;

    void keyReleaseEvent(QKeyEvent *event) override;

    void closeEvent(QCloseEvent *event) override;

    void putKey(const QString &key);

private slots:
    void on_bt_remove_ball_clicked();

private:
    Ui::GameFrame *ui;
    GameScene *m_scene;
    QTimer m_timer;
    QString m_cur_key; // current key pressed
    double m_score;

    bool m_is_started, m_is_paused, m_is_finished;

    QStack<Actor*> m_balls; // for debug

    std::function<void()> m_keep_doing;
    int m_pressed_key;

    // QObject interface
public:
    bool eventFilter(QObject *watched, QEvent *event) override;
};

#endif // GAMEFRAME_H
