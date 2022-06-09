#include "a_dialog.h"
#include "ui_a_dialog.h"
#include <QMessageBox>
#include <QSettings>

A_Dialog::A_Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::A_Dialog)
{
    ui->setupUi(this);
    setWindowFlags( Qt::CustomizeWindowHint );
    connect(ui->exitButton, SIGNAL(clicked()), this, SLOT(onExitClicked()));
    connect(ui->nextButton, SIGNAL(clicked()), this, SLOT(openNextDialog()));

}

void A_Dialog::openNextDialog() {
  QSettings settings;
  QString nmeaPath = settings.value("NmeaPath").toString();
  QString dbPath   = settings.value("DbPath").toString();

  if (nmeaPath.isEmpty()) {
    my_b_dialog = new B_Dialog;
    my_b_dialog->show();
    my_b_dialog->activateWindow();
    this->hide();
    //    ONLY after  the creation of object for child class
    connect(my_b_dialog, SIGNAL(showPreviousDialog()), this, SLOT(show()));
    ;
  } else if (dbPath.isEmpty()) {
    m_cDialog = new C_Dialog;
    m_cDialog->show();
    m_cDialog->activateWindow();
    this->hide();
  }
}

void A_Dialog::onExitClicked()
{
    int ret = QMessageBox::warning(this, tr("My Application"),
                                   tr("Are you sure yoy want to exit?"),
                                   QMessageBox::Ok | QMessageBox::Cancel);

    switch (ret) {
       case QMessageBox::Ok:
           // OK was clicked
           this->close();
           break;
       case QMessageBox::Cancel:
           // Cancel was clicked
           break;
       default:
           // should never be reached
           break;
     }
}

A_Dialog::~A_Dialog()
{
    delete ui;
}
