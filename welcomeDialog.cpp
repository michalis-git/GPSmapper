#include "welcomeDialog.h"
#include "ui_welcomeDialog.h"
#include <QMessageBox>
#include <QSettings>

WelcomeDialog::WelcomeDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WelcomeDialog) {
    ui->setupUi(this);
    setWindowFlags( Qt::CustomizeWindowHint );
    connect(ui->exitButton, SIGNAL(clicked()), this, SLOT(onExitClicked()));
    connect(ui->nextButton, SIGNAL(clicked()), this, SLOT(openNextDialog()));

}

void WelcomeDialog::openNextDialog() {
  QSettings settings;
  QString nmeaPath = settings.value("NmeaPath").toString();
  QString dbPath   = settings.value("DbPath").toString();

  if (nmeaPath.isEmpty()) {
    m_nmeaDialog = new NmeaDialog;
    m_nmeaDialog->show();
    m_nmeaDialog->activateWindow();
    this->hide();
    //    ONLY after  the creation of object for child class
    connect(m_nmeaDialog, SIGNAL(showPreviousDialog()), this, SLOT(show()));
    ;
  } else if (dbPath.isEmpty()) {
    m_cDialog = new DbDialog;
    m_cDialog->show();
    m_cDialog->activateWindow();
    this->hide();
  }
}

void WelcomeDialog::onExitClicked() {
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

WelcomeDialog::~WelcomeDialog() {
    delete ui;
}
