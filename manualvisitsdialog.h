#ifndef MANUALVISITSDIALOG_H
#define MANUALVISITSDIALOG_H

#include <QDialog>
#include "sqlworker.h"
namespace Ui {
class ManualVisitsDialog;
}

class ManualVisitsDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ManualVisitsDialog(QWidget *parent = 0);
    ~ManualVisitsDialog();
    void setSQLWorker(SQLWorker* sqlWorker){this->sqlWorker = sqlWorker;}
    void initialize();

private slots:
    void on_getThroughButton_clicked();

    void on_useCurrentCheckBox_stateChanged(int arg1);

private:
    void addVisit();
    void resetTableView();
    QVector<QStringList> doorlockstable;
    QVector<int> workersIdsList;
    QVector<int> doorsIdsList;
    SQLWorker* sqlWorker = NULL;
    Ui::ManualVisitsDialog *ui;
};

#endif // MANUALVISITSDIALOG_H
