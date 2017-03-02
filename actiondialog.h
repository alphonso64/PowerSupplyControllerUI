#ifndef ACTIONDIALOG_H
#define ACTIONDIALOG_H
#include <QMap>
#include <QDialog>

namespace Ui {
class ActionDialog;
}

class ActionDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ActionDialog(QWidget *parent = 0);
    ~ActionDialog();
    void setStyle(int);

private slots:
    void doneExit();
    void rejectExit();

private:
    Ui::ActionDialog *ui;
public:
    QString filePath;
    QString fileName;
    QMap<QString,QString> list;
};

#endif // ACTIONDIALOG_H
