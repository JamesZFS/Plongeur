#ifndef STATDIALOG_H
#define STATDIALOG_H

#include <QDialog>

namespace Ui {
class StatDialog;
}

class StatDialog : public QDialog
{
    Q_OBJECT

public:
    explicit StatDialog(double score);
    ~StatDialog();

signals:
    void closed();

private:
    Ui::StatDialog *ui;

    // QWidget interface
protected:
    void closeEvent(QCloseEvent *event) override;
};

#endif // STATDIALOG_H
