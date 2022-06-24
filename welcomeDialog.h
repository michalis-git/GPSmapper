#ifndef WELCOMEDIALOG_H
#define WELCOMEDIALOG_H

#include <QDialog>
#include "nmeaDialog.h"

namespace Ui {
  class WelcomeDialog;
}

class WelcomeDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit WelcomeDialog(QWidget *parent = 0);
    ~WelcomeDialog();
    
private:
    Ui::WelcomeDialog *ui;
    NmeaDialog *m_nmeaDialog;
    DbDialog *m_cDialog;

private slots:
    void openNextDialog();
    void onExitClicked();
};

#endif // WELCOMEDIALOG_H
