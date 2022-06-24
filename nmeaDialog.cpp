#include "nmeaDialog.h"
#include "nmeaDialog.h"
#include <QFileDialog>
#include <QDir>
#include <QMessageBox>
#include <QDebug>
#include <QSettings>

NmeaDialog::NmeaDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::NmeaDialog) {
    ui->setupUi(this);
    setWindowFlags( Qt::CustomizeWindowHint );
    connect(ui->backButton, SIGNAL(clicked()), this, SLOT(openPreviousDialog()));
    connect(ui->nextButton, SIGNAL(clicked()), this, SLOT(openNextDialog()));
    connect(ui->toolButton, SIGNAL(clicked()), this, SLOT(selectFile()));
}

void NmeaDialog::openPreviousDialog() {
    emit showPreviousDialog();
    this->close();
}

void NmeaDialog::openNextDialog()
{
    qDebug() << "apo dialogB: " << fileName;
    if(!ui->lineEdit->text().isEmpty())
    {
        my_c_dialog = new C_Dialog;
        my_c_dialog->setFileName(fileName);
        my_c_dialog->show();
        my_c_dialog->activateWindow();
        this->hide();
    //    ONLY after  the creation of object for child class
        connect(my_c_dialog, SIGNAL(showPreviousDialog()), this, SLOT(show()));
    } else {
        QMessageBox::warning(this, tr("Warning!"), tr("You have not chosen any file."));
    }

}

void NmeaDialog::selectFile()
{
         fileName = QFileDialog::getOpenFileName(this,
                                                         tr("Open NMEA file"), ".",
                                                         tr("TXT image (*txt)"));
         if(!fileName.isEmpty()) curFile = fileName;

         setWindowModified(false);

         ui->lineEdit->setText(fileName);
         if(!ui->lineEdit->text().isEmpty()) ui->nextButton->setEnabled(true);
         QSettings settings;
         settings.setValue("NmeaPath", fileName);
}

NmeaDialog::~NmeaDialog() {
    delete ui;
}
