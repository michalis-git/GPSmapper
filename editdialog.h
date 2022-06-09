#ifndef EDITDIALOG_H
#define EDITDIALOG_H

#include <QDialog>

namespace Ui {
class editDialog;
}

class editDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit editDialog(QWidget *parent = 0);
    ~editDialog();
    void getComboBoxItems(QString catName, QVariant(id));
    void getData(QString idStr, QString x, QString y, QString h, QString adr, QString com, QString cat, QStringList strList);
    QString idStr1;
    
private:
    Ui::editDialog *ui;

signals:
    void sendEditedData(QString idStr1, QString x, QString y, QString h, QString adr, QString com, QString cat);

private slots:
    void onOkClicked();
};

#endif // EDITDIALOG_H
