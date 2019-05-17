#include "statdialog.h"
#include "ui_statdialog.h"
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QCloseEvent>

StatDialog::StatDialog(double score) :
    QDialog(0),
    ui(new Ui::StatDialog)
{
    ui->setupUi(this);

    // below will init an example table
    ui->statTable->insertRow(0);
    ui->statTable->insertRow(1);
    ui->statTable->insertColumn(0);
    ui->statTable->insertColumn(1);
    auto item0 = new QTableWidgetItem("player");
    auto item1 = new QTableWidgetItem("score");
    auto itemScore = new QTableWidgetItem(QString("%1").arg(score));
    ui->statTable->setItem(0, 0, item0);
    ui->statTable->setItem(1, 0, item1);
    ui->statTable->setItem(1, 1, itemScore);
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
