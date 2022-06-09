#ifndef B_DIALOG_H
#define B_DIALOG_H

#include <QDialog>
#include <QFileDialog>
#include <QDir>
#include "c_dialog.h"

namespace Ui {
class B_Dialog;
}


class B_Dialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit B_Dialog(QWidget *parent = 0);
    ~B_Dialog();

signals:
    void showPreviousDialog();
    
private:
    Ui::B_Dialog *ui;
    C_Dialog *my_c_dialog;
    QDir directory;
    QDir currentDir;
    QString fileName;
    QString text;
    QFile files;
    QString curFile;

private slots:
    void openPreviousDialog();
    void openNextDialog();
    void selectFile();
};

#endif // B_DIALOG_H
