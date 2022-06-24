#include "dbDialog.h"
#include "ui_dbDialog.h"
#include <QFileDialog>
#include<QDebug>
#include<QMessageBox>
#include <QSettings>

DbDialog::DbDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DbDialog) {
  ui->setupUi(this);
  setWindowFlags( Qt::CustomizeWindowHint );
  connect(ui->toolButton, SIGNAL(clicked()), this, SLOT(selectFile()));
  connect(ui->backButton, SIGNAL(clicked()), this, SLOT(openPreviousDialog()));
  connect(ui->finishButton, SIGNAL(clicked()), this, SLOT(finishDialog()));
}

void DbDialog::setFileName(QString fileName) {
  filePath = fileName;
}

void DbDialog::openPreviousDialog() {
  emit showPreviousDialog();
  this->close();
}

void DbDialog::selectFile() {
  dbName = QFileDialog::getOpenFileName(this,
                                        tr("Open DataBase file"), ".",
                                        tr("SQLITE database (*sqlite)"));
  if(!dbName.isEmpty())
    curFile = dbName;
  setWindowModified(false);

  ui->lineEdit->setText(dbName);
  if(!ui->lineEdit->text().isEmpty()) ui->finishButton->setEnabled(true);

  QSettings settings;
  settings.setValue("DbPath", dbName);

}

void DbDialog::finishDialog() {
  qDebug() << "apo dialogB: " << fileName << dbName;
  if(!ui->lineEdit->text().isEmpty()) {
    my_mainwindow = new MainWindow(0, filePath, dbName);
    my_mainwindow->filePathPublic = filePath;
    my_mainwindow->dbNamePublic = dbName;
    qDebug() << "mesa apo dialogb: " << filePath << dbName;
    my_mainwindow->show();
    my_mainwindow->activateWindow();
    this->close();
  } else {
    QMessageBox::warning(this, tr("Warning!"), tr("You have not chosen any file."));
  }

}

DbDialog::~DbDialog()
{
  delete ui;
}
