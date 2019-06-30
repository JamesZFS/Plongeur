#include "statdialog.h"
#include "ui_statdialog.h"
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QCloseEvent>
#include <QDebug>

StatDialog::StatDialog(ScoreTable scores) :
    QDialog(0),
    ui(new Ui::StatDialog)
{
    ui->setupUi(this);

    // below will init an example table
    QTableWidget &table = *ui->statTable;
    table.insertRow(0);
    table.insertColumn(0);
    table.insertColumn(1);
    table.insertColumn(2);
    table.insertColumn(3);
    // table head:
    QTableWidgetItem *item;
    item = new QTableWidgetItem("Jump");
    table.setItem(0, 0, item);
    item = new QTableWidgetItem("Difficulty Score");
    table.setItem(0, 1, item);
    item = new QTableWidgetItem("Subjective Score(%)");
    table.setItem(0, 2, item);
    item = new QTableWidgetItem("Total Score");
    table.setItem(0, 3, item);
    // table body:
    qDebug() << scores;
    for (int i = 0; i < scores.size(); ++i) {
        table.insertRow(i+1);
        auto &sc = scores[i];
        item = new QTableWidgetItem(QString::number(i));
        table.setItem(i+1, 0, item);
        item = new QTableWidgetItem(QString::number(sc.first, 'f', 2));
        table.setItem(i+1, 1, item);
        item = new QTableWidgetItem(QString::number(sc.second*100, 'f', 1));
        table.setItem(i+1, 2, item);
        item = new QTableWidgetItem(QString::number(sc.first*sc.second, 'f', 2));
        table.setItem(i+1, 3, item);
    }
}

StatDialog::~StatDialog()
{
    delete ui;
}

void StatDialog::closeEvent(QCloseEvent *event)
{
    emit closed();
    event->accept();
}
