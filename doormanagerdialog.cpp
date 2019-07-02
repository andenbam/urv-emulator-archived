#include "doormanagerdialog.h"
#include "ui_doormanagerdialog.h"
#include <QAbstractItemView>
#include "messagedropper.h"
DoorManagerDialog::DoorManagerDialog(QDialog *parent) :
    QDialog(parent),
    ui(new Ui::DoorManagerDialog)
{
     ui->setupUi(this);
}

void DoorManagerDialog::updateSelected(const QModelIndex current){

    QModelIndex index = ui->tableView->
            model()->index(current.row(), 0);

    int id = ui->tableView->model()->data(index).toInt();
    ui->nameEdit->setText(sqlWorker->getDoorlockName(id));
    ui->innerRadio->setChecked(sqlWorker->getDoorlockType(id) == 1);
    ui->outerRadio->setChecked(sqlWorker->getDoorlockType(id) == 2);//UNDER CONSTRUCTION


}

void DoorManagerDialog::resetTableView(){
    model = sqlWorker->getDoorlocksTable();
    ui->tableView->setModel(model);
    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);

    ui->tableView->setColumnWidth(0,128);
    ui->tableView->setColumnWidth(1,128);
    ui->tableView->setColumnWidth(2,128);

    ui->tableView->verticalHeader()->setVisible(false);
    ui->tableView->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);

    connect(ui->tableView->selectionModel(),
            SIGNAL(currentRowChanged(QModelIndex,QModelIndex)),this,
            SLOT(updateSelected(QModelIndex,QModelIndex)));

}

void DoorManagerDialog::initialize(){

    this->setSizePolicy(QSizePolicy::Fixed,QSizePolicy::Fixed);
    this->setSizeGripEnabled(false);
    resetTableView();
    this->setFixedSize(this->width(),this->height());
    this->setSizeGripEnabled(false);

    mw->hide();

}

DoorManagerDialog::~DoorManagerDialog()
{
    delete ui;
}

void DoorManagerDialog::on_addButton_clicked()
{
    int id = sqlWorker->getDoorsMaxId()+1;
    QString name = ui->nameEdit->text();
    int type = ui->innerRadio->isChecked() ? 1 : 2;

    sqlWorker->insertDoorlock(id,name,type);
    resetTableView();

}

void DoorManagerDialog::on_editButton_clicked()
{

    QModelIndexList selection = ui->tableView->selectionModel()->selectedRows();
    if (selection.count() < 1){
        return;
    }
    QModelIndex index = ui->tableView->model()->index(
                ui->tableView->selectionModel()->selectedRows().at(0).row(), 0, QModelIndex());

    int id = ui->tableView->model()->data(index).toInt();
    QString name = ui->nameEdit->text();
    int type = ui->innerRadio->isChecked() ? 1 : 2;

    sqlWorker->updateDoorlock(id,name,type);
    resetTableView();
}

void DoorManagerDialog::on_deleteButton_clicked()
{
    QModelIndexList selection = ui->tableView->selectionModel()->selectedRows();
    if (selection.count() < 1){
        return;
    }

    if (! MessageDropper::DropAsk("Deleting doorlock...", "Are you sure?\n This action cannot be undone."))
        return;

    QModelIndex index = ui->tableView->model()->index(
                ui->tableView->selectionModel()->selectedRows().at(0).row(), 0, QModelIndex());

    int id = ui->tableView->model()->data(index).toInt();

    sqlWorker->dropDoorlock(id);
    resetTableView();
}

void DoorManagerDialog::on_outerRadio_toggled(bool checked)
{
    ui->innerRadio->setChecked(! checked);
}

void DoorManagerDialog::reject(){

    mw->show();
    QDialog::reject();
}
