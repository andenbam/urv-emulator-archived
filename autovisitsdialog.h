#ifndef AUTOVISITSDIALOG_H
#define AUTOVISITSDIALOG_H

#include <QDialog>

namespace Ui {
class AutoVisitsDialog;
}

class AutoVisitsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AutoVisitsDialog(QDialog *parent = 0);
    ~AutoVisitsDialog();

private:
    Ui::AutoVisitsDialog *ui;
};

#endif // AUTOVISITSDIALOG_H
