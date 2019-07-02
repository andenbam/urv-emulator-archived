#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include "mainwindow.h"

namespace Ui {
class LoginDialog;
}

class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoginDialog(QWidget *parent = 0);
    ~LoginDialog();
    void setSQLWorker(SQLWorker* sqlWorker){this->sqlWorker = sqlWorker;}
    void setMW(MainWindow* mw){this->mw = mw;}

private slots:


    void on_loginButton_clicked();

    void on_pathButton_clicked();

private:
    QString connectionSettings;
    void saveSettings();
    void loadSettings();
    MainWindow* mw;
    SQLWorker* sqlWorker = NULL;
    Ui::LoginDialog *ui;
    bool loginSuccessful = false;
    QString dbString;
    QString acc;
    QString password;
};

#endif // LOGINDIALOG_H
