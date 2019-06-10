#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QCloseEvent>
#include "gameframe.h"
#include "statdialog.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QWidget
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void closeEvent(QCloseEvent *event) override;

private slots:
    void on_actionPlay_triggered();
    void on_actionHelp_triggered();
    void on_actionQuit_triggered();
    void onGameEnd();

private:
    Ui::MainWindow *ui;

    GameFrame gameFrame;

    StatDialog *statDialog;
};

#endif // MAINWINDOW_H
