#include "c_dialog.h"
#include "ui_c_dialog.h"
#include <QFileDialog>
#include<QDebug>
#include<QMessageBox>
#include <QSettings>

C_Dialog::C_Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::C_Dialog) {
  ui->setupUi(this);
  setWindowFlags( Qt::CustomizeWindowHint );
  connect(ui->toolButton, SIGNAL(clicked()), this, SLOT(selectFile()));
  connect(ui->backButton, SIGNAL(clicked()), this, SLOT(openPreviousDialog()));
  connect(ui->finishButton, SIGNAL(clicked()), this, SLOT(finishDialog()));
}

void C_Dialog::setFileName(QString fileName) {
  filePath = fileName;
}

void C_Dialog::openPreviousDialog() {
  emit showPreviousDialog();
  this->close();
}

void C_Dialog::selectFile() {
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

void C_Dialog::finishDialog() {
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

C_Dialog::~C_Dialog()
{
  delete ui;
}
