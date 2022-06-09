#ifndef QUERYDIALOG_H
#define QUERYDIALOG_H

#include <QDialog>

namespace Ui {
class queryDialog;
}

class queryDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit queryDialog(QWidget *parent = 0);
    ~queryDialog();
    void getData(QStringList strList);
    QString lastItem;
    
private:
    Ui::queryDialog *ui;

signals:
    void sendCatQuery(QStringList);

private slots:
    void onLoadClicked();
    void onRemoveClicked();
    void onUndoClicked();
};

#endif // QUERYDIALOG_H
