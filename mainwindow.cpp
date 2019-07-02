#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "logindialog.h"
#include "manualvisitsdialog.h"
#include "doormanagerdialog.h"
#include "autovisitsdialog.h"
#include "messagedropper.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::quit(){

    QCoreApplication::quit();
}

void MainWindow::connectTo(){

    LoginDialog lDialog;
    lDialog.setSQLWorker(sqlWorker);
    lDialog.setMW(this);
    lDialog.setModal(true);
    lDialog.exec();
}

bool MainWindow::isConnected(){
    return connected;
}

void MainWindow::setConnected(bool value){
    connected = value;
    if (value) ui->dbnamelabel->setText(sqlWorker->getDBName());
}

void MainWindow::setSQLWorker(SQLWorker *sqlWorker){
    this->sqlWorker = sqlWorker;
}


void MainWindow::on_manualVisitsButton_clicked()
{
    ManualVisitsDialog *mvd = new ManualVisitsDialog();
    mvd->setSQLWorker(sqlWorker);
    mvd->initialize();
    mvd->setModal(true);
    mvd->exec();

}

void MainWindow::on_autoVisitsButton_clicked()
{
    MessageDropper::DropThis("Not Ready Yet...", "This Area is Under Construction.\n Sorry, it's unavailable :(");

}

void MainWindow::on_doorManagerButton_clicked()
{
    DoorManagerDialog *dmd = new DoorManagerDialog();
    dmd->setSQLWorker(sqlWorker);
    dmd->setMW(this);
    dmd->initialize();
    //dmd->setModal(true);
    dmd->exec();
}
