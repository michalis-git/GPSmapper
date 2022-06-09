#ifndef A_DIALOG_H
#define A_DIALOG_H

#include <QDialog>
#include "b_dialog.h"

namespace Ui {
class A_Dialog;
}

class A_Dialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit A_Dialog(QWidget *parent = 0);
    ~A_Dialog();
    
private:
    Ui::A_Dialog *ui;
    B_Dialog *my_b_dialog;
    C_Dialog *m_cDialog;

private slots:
    void openNextDialog();
    void onExitClicked();
};

#endif // A_DIALOG_H
