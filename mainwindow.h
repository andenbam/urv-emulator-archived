#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "sqlworker.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    bool isConnected();
    void setConnected(bool value);
    void quit();
    void connectTo();
    void setSQLWorker(SQLWorker* sqlWorker);

private slots:
    void on_manualVisitsButton_clicked();

    void on_autoVisitsButton_clicked();

    void on_doorManagerButton_clicked();

private:
    bool connected = false;
    SQLWorker* sqlWorker = NULL;
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
