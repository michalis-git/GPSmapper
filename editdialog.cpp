#include "editdialog.h"
#include "ui_editdialog.h"
#include <QDebug>

editDialog::editDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::editDialog)
{
    ui->setupUi(this);
    setWindowFlags( Qt::CustomizeWindowHint );
    connect(ui->saveButton, SIGNAL(clicked()), this, SLOT(onOkClicked()));
    connect(ui->cancelButton, SIGNAL(clicked()), this, SLOT(close()));
    qDebug() << "dhmiourgh8hke editDialog";
}

editDialog::~editDialog()
{
    delete ui;
}

void editDialog::getData(QString idStr, QString x, QString y, QString h, QString adr, QString com, QString cat,QStringList strList)
{
    ui->xLineEdit->setText(x);
    ui->yLineEdit->setText(y);
    ui->hLineEdit->setText(h);
    ui->adrsLineEdit->setText(adr);
    ui->cmntsLineEdit->setText(com);
    int i;
    for (i=0; i <= strList.length(); i++)
    {
        ui->comboBox->addItem(strList.value(i));
    }
    ui->comboBox->setCurrentIndex(cat.toInt());
    idStr1 = idStr;
}

void editDialog::onOkClicked()
{
    QString x = ui->xLineEdit->text();
    QString y = ui->yLineEdit->text();
    QString h = ui->hLineEdit->text();
    QString adr = ui->adrsLineEdit->text();
    QString com = ui->cmntsLineEdit->text();
    QString cat  = QString ("%1").arg(ui->comboBox->currentIndex());
    qDebug() << "cat from edit's combobox (on ok): " << cat;
    emit sendEditedData(idStr1,x,y,h,adr,com,cat);
    this->close();
}
