#ifndef DOORMANAGERDIALOG_H
#define DOORMANAGERDIALOG_H

#include <QDialog>
#include <sqlworker.h>
#include <QSqlTableModel>
#include <mainwindow.h>
namespace Ui {
class DoorManagerDialog;
}

class DoorManagerDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DoorManagerDialog(QDialog *parent = 0);
    ~DoorManagerDialog();
    void setSQLWorker(SQLWorker* sqlWorker){this->sqlWorker = sqlWorker;}
    void setMW(MainWindow* mw){this->mw = mw;}
    void reject();
    void initialize();
private slots:

    void on_addButton_clicked();

    void updateSelected(const QModelIndex current);

    void on_editButton_clicked();

    void on_deleteButton_clicked();

    void on_outerRadio_toggled(bool checked);

private:
    void resetTableView();
    Ui::DoorManagerDialog *ui;
    MainWindow * mw;
    QSqlTableModel* model;
    SQLWorker* sqlWorker;
};

#endif // DOORMANAGERDIALOG_H
