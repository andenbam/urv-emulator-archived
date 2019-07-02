#include "logindialog.h"
#include "ui_logindialog.h"
#include <messagedropper.h>
#include <QFileDialog>
#include <QSettings>
LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);
    dbString = "";
    acc = "";
    password = "";
    loginSuccessful = false;
    loadSettings();
}

LoginDialog::~LoginDialog()
{
    delete ui;
}

void LoginDialog::saveSettings(){
    QSettings settings("BlackSofa","URVEmulatorSQLite");
    settings.setValue("Login/dbPath", ui->dbline->text());
    settings.setValue("Login/username", ui->accline->text());
}

void LoginDialog::loadSettings(){
    QSettings settings("BlackSofa","URVEmulatorSQLite");
    ui->dbline->setText(settings.value("Login/dbPath").value<QString>());
    ui->accline->setText(settings.value("Login/username").value<QString>());
}

void LoginDialog::on_loginButton_clicked()
{
    dbString = ui->dbline->text();
    acc = ui->accline->text();
    password = ui->passline->text();

    bool a = sqlWorker->tryConnectTo(dbString);
    if (!a) {
        MessageDropper::DropThis("cannot connect to DB", dbString + " is not here");
    }
    else {
        if (sqlWorker->tryLogIn(acc,password) != 1)
            MessageDropper::DropThis("U R Not Admin", "\nCheck username/password \n(" + acc + " , " + password + ")");
        else{
        loginSuccessful = true;
        mw->setConnected(true);
        saveSettings();
        mw->show();
        close();
        }
     }
}
void LoginDialog::on_pathButton_clicked()
{
    QString str = QFileDialog::getOpenFileName(this,tr("Choose SQLite Database"),"", tr("SQLite DB (*.sqlite)"));
    if (str != "") ui->dbline->setText(str);
}

