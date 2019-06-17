#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QDebug>
#include <QCloseEvent>

MainWindow::MainWindow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainWindow)
{
    qDebug("Welcome to Plongeur, a high diving game with awesome water effect "
           "powered by Liquidfun™.");
    ui->setupUi(this);
    connect(ui->btPlay, &QPushButton::clicked, ui->actionPlay, &QAction::trigger);
    connect(ui->btHelp, &QPushButton::clicked, ui->actionHelp, &QAction::trigger);
    connect(ui->btQuit, &QPushButton::clicked, ui->actionQuit, &QAction::trigger);

    connect(&gameFrame, &GameFrame::closed, this, &MainWindow::onGameEnd);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionPlay_triggered()
{
    qDebug("actionPlay()");
    gameFrame.setStart();
    gameFrame.show();
    // todo
}

void MainWindow::on_actionHelp_triggered()
{
    qDebug("actionHelp()");
    // todo popup a help dialog
}

void MainWindow::on_actionQuit_triggered()
{
    qDebug("on_actionQuit_triggered()");
    close();
}

void MainWindow::onGameEnd()
{
    qDebug("onGameEnd()");
    statDialog = new StatDialog(gameFrame.getScore());
    statDialog->show();
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    qDebug("closeEvent()");
    event->accept();
//    int ret = QMessageBox::question(
//                this,
//                "",
//                tr("Do you really want to quit?"),
//                QMessageBox::Yes,
//                QMessageBox::No);
//    if (ret == QMessageBox::Yes)
//        event->accept();
//    else
//        event->ignore();
}
