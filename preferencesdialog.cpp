#include "preferencesdialog.h"
#include "ui_preferencesdialog.h"
#include <QDebug>
#include <QSettings>

PreferencesDialog::PreferencesDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PreferencesDialog) {
  ui->setupUi(this);

  connect(ui->resetButton, &QPushButton::clicked, this, &PreferencesDialog::onResetClicked);
}

PreferencesDialog::~PreferencesDialog() {
  delete ui;
}

void PreferencesDialog::onResetClicked() {
  qDebug() << "reset!";
  QSettings settings;
  settings.clear();
}
