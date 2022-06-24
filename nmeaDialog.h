#ifndef NMEADIALOG_H
#define NMEADIALOG_H

#include <QDialog>
#include <QFileDialog>
#include <QDir>
#include "c_dialog.h"

namespace Ui {
  class NmeaDialog;
}


class NmeaDialog : public QDialog {
    Q_OBJECT
    
public:
    explicit NmeaDialog(QWidget *parent = 0);
    ~NmeaDialog();

signals:
    void showPreviousDialog();
    
private:
    Ui::NmeaDialog *ui;
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

#endif // NMEADIALOG_H
