#ifndef GAMEFRAME_H
#define GAMEFRAME_H

#include <QFrame>

class GameScene;

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

private:
    Ui::GameFrame *ui;
    GameScene *m_scene;
    QString m_cur_key; // current key pressed
    double m_score;

    bool m_is_started, m_is_paused, m_is_finished;

    void putKey(const QString &key);

};

#endif // GAMEFRAME_H
