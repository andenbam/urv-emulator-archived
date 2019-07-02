#include "autovisitsdialog.h"
#include "ui_autovisitsdialog.h"

AutoVisitsDialog::AutoVisitsDialog(QDialog *parent) :
    QDialog(parent),
    ui(new Ui::AutoVisitsDialog)
{
    ui->setupUi(this);
}

AutoVisitsDialog::~AutoVisitsDialog()
{
    delete ui;
}
