#ifndef CUSDIALOG_H
#define CUSDIALOG_H

#include <QDialog>

namespace Ui {
class CusDialog;
}

class CusDialog : public QDialog
{
    Q_OBJECT
public:
    explicit CusDialog(QWidget *parent = 0);
    explicit CusDialog(QString msg,int type,QWidget *parent = 0);
    void changeStyle(QString msg,int type);
    ~CusDialog();
private slots:
    void doneExit();
    void rejectExit();

private:
    Ui::CusDialog *ui;
};

#endif // CUSDIALOG_H
