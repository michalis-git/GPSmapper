#include "recorddialog.h"
#include "ui_recorddialog.h"
#include <QDebug>
#include<QMessageBox>

recordDialog::recordDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::recordDialog)
{
    ui->setupUi(this);
    setWindowFlags( Qt::CustomizeWindowHint );
    connect(ui->cancelButton, SIGNAL(clicked()), this, SLOT(close()));
    connect(ui->okButton, SIGNAL(clicked()), this, SLOT(onOkClicked()));
}

void recordDialog::onOkClicked()
{
    QString E = ui->xLineEdit->text();
    QString N = ui->yLineEdit->text();
    QString H = ui->hLineEdit->text();
    QString adrs = ui->adrsLineEdit->text();
    int id = ui->categoryComboBox->currentIndex();
    QString idStr = QString::number(id);
    QString cmnts = ui->cmntsLineEdit->text();
    qDebug() << E << N << H << adrs  << cmnts << id;
    if (ui->categoryComboBox->currentIndex() == 0)
        {
            QMessageBox::warning(this, tr("Warning!"), tr("You have to choose a category type."));
        }
        else
        {
            emit sendData(E,N,H,adrs,cmnts,idStr);;
            this->close();
        }
}

void recordDialog::getData(QString strE, QString strN, QString strH, QStringList strList)
{
    ui->xLineEdit->setText(strE);
    ui->yLineEdit->setText(strN);
    ui->hLineEdit->setText(strH);
    int i;
    for (i=0; i <= strList.length(); i++)
    {
        ui->categoryComboBox->addItem(strList.value(i));
    }
}

recordDialog::~recordDialog()
{
    delete ui;
}
