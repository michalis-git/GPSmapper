#ifndef RECORDDIALOG_H
#define RECORDDIALOG_H

#include <QDialog>

namespace Ui {
class recordDialog;
}

class recordDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit recordDialog(QWidget *parent = 0);
    ~recordDialog();
    void getData(QString strE, QString strN, QString strH, QStringList strList);

signals:
    void sendData(QString E, QString N, QString H, QString adrs, QString cmnts, QString id);
    
private:
    Ui::recordDialog *ui;

private slots:
    void onOkClicked();
};

#endif // RECORDDIALOG_H
