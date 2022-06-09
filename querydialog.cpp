#include "querydialog.h"
#include "ui_querydialog.h"
#include<QDebug>
#include <QMessageBox>

queryDialog::queryDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::queryDialog)
{
    ui->setupUi(this);
    setWindowFlags( Qt::CustomizeWindowHint );
    connect(ui->cancelButton, SIGNAL(clicked()), this, SLOT(close()));
    connect(ui->loadButton, SIGNAL(clicked()), this, SLOT(onLoadClicked()));
    connect(ui->removeButton, SIGNAL(clicked()), this, SLOT(onRemoveClicked()));
    connect(ui->undoButton, SIGNAL(clicked()), this, SLOT(onUndoClicked()));
}

void queryDialog::getData(QStringList strList) {
    for (int i=0; i <= strList.length(); i++) {
        ui->listWidget->addItem(strList.value(i));
    }
}

void queryDialog::onLoadClicked()
{
    int countList = ui->listWidget->count();
    QStringList catStringList;
    int i;
    for (i = 0; i < countList; i++)
    {
        QString catString = ui->listWidget->item(i)->text();
        catStringList.append(catString);
    }
    emit sendCatQuery(catStringList);
    this->close();
}

void queryDialog::onRemoveClicked()
{
    QListWidgetItem *curItem = ui->listWidget->currentItem();
    lastItem = curItem->text();
    ui->undoButton->setEnabled(true);
    curItem->~QListWidgetItem();
}

void queryDialog::onUndoClicked()
{
    ui->listWidget->addItem(lastItem);
    ui->undoButton->setEnabled(false);
}

queryDialog::~queryDialog()
{
    delete ui;
}
