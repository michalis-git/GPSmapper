#ifndef PREFERENCESDIALOG_H
#define PREFERENCESDIALOG_H

#include <QDialog>

namespace Ui {
class PreferencesDialog;
}

class PreferencesDialog : public QDialog
{
  Q_OBJECT

public:
  explicit PreferencesDialog(QWidget *parent = nullptr);
  ~PreferencesDialog();

private:
  Ui::PreferencesDialog *ui;

private slots:
  void onResetClicked();
};

#endif // PREFERENCESDIALOG_H
