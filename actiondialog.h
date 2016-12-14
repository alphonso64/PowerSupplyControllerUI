#ifndef ACTIONDIALOG_H
#define ACTIONDIALOG_H

#include <QDialog>

namespace Ui {
class ActionDialog;
}

class ActionDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ActionDialog(QWidget *parent = 0);
    explicit ActionDialog(QString msg,int ID,QWidget *parent = 0);
    ~ActionDialog();

private slots:
    void doneExit();
    void rejectExit();

private:
    Ui::ActionDialog *ui;
    int flagID;
};

#endif // ACTIONDIALOG_H
