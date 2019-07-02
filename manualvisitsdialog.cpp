#include "manualvisitsdialog.h"
#include "ui_manualvisitsdialog.h"
#include <QDateTime>
#include <QTableView>
#include <QScrollArea>
#include <QSqlTableModel>

ManualVisitsDialog::ManualVisitsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ManualVisitsDialog)
{
    ui->setupUi(this);
}

ManualVisitsDialog::~ManualVisitsDialog()
{
    delete ui;
}

void ManualVisitsDialog::resetTableView(){

    ui->tableView->setModel(sqlWorker->getVisitsTable());

    ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);

    ui->tableView->setColumnWidth(0,128);
    ui->tableView->setColumnWidth(1,128);
    ui->tableView->setColumnWidth(2,128);
    ui->tableView->setColumnWidth(3,128);

    ui->tableView->verticalHeader()->setVisible(false);
    ui->tableView->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    ui->tableView->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);

    //connect(ui->tableView->selectionModel(),
      //      SIGNAL(currentRowChanged(QModelIndex,QModelIndex)),this,
        //    SLOT(updateSelected(QModelIndex,QModelIndex)));
}

void ManualVisitsDialog::initialize(){

    doorsIdsList = sqlWorker->getDoorsIds();
    workersIdsList = sqlWorker->getWorkersIds();

    resetTableView();

    ui->workersComboBox->addItems(sqlWorker->getWorkersNames());
    ui->doorsComboBox->addItems(sqlWorker->getDoorsNames());
    ui->workersComboBox->setCurrentIndex(0);
    ui->doorsComboBox->setCurrentIndex(0);

    //ui->tableView->setColumnHidden(0,true);

}

void ManualVisitsDialog::addVisit(){

    if (doorsIdsList.empty() || workersIdsList.empty())
        return;

    sqlWorker->addVisit(
            workersIdsList[ui->workersComboBox->currentIndex()],
            doorsIdsList[ui->doorsComboBox->currentIndex()],
            QDateTime(ui->dateEdit->date(),ui->timeEdit->time()));
}

void ManualVisitsDialog::on_getThroughButton_clicked(){

    addVisit();
    resetTableView();
}

void ManualVisitsDialog::on_useCurrentCheckBox_stateChanged(int arg1)
{
    if (arg1){
        ui->timeEdit->setTime(QDateTime::currentDateTime().time());
        ui->dateEdit->setDate(QDateTime::currentDateTime().date());
        }
        ui->dateEdit->setEnabled(! arg1);
        ui->timeEdit->setEnabled(! arg1);

}
