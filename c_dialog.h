#ifndef C_DIALOG_H
#define C_DIALOG_H

#include <QDialog>
#include "mainwindow.h"
#include <QDir>

namespace Ui {
class C_Dialog;
}

class C_Dialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit C_Dialog(QWidget *parent = 0);
    ~C_Dialog();
    void setFileName(QString fileName);

signals:
    void showPreviousDialog();
    void sendParam(QString filePath, QString dbName1);
    
private:
    Ui::C_Dialog *ui;
    MainWindow *my_mainwindow;
    QString filePath;
    QDir directory;
    QDir currentDir;
    QString fileName, dbName;
    QString text;
    QFile files;
    QString curFile, shownName;
    QString strippedName(const QString &fullFileName);

private slots:
    void openPreviousDialog();
    void finishDialog();
    void selectFile();
};

#endif // C_DIALOG_H
