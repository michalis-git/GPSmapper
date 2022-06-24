#ifndef C_DIALOG_H
#define C_DIALOG_H

#include <QDialog>
#include "mainwindow.h"
#include <QDir>

namespace Ui {
class DbDialog;
}

class DbDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit DbDialog(QWidget *parent = 0);
    ~DbDialog();
    void setFileName(QString fileName);

signals:
    void showPreviousDialog();
    void sendParam(QString filePath, QString dbName1);
    
private:
    Ui::DbDialog *ui;
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
