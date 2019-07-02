#include "messagedropper.h"
#include <QMessageBox>
#include <QAbstractButton>
MessageDropper::MessageDropper()
{

}


void MessageDropper::DropError(){

    QMessageBox box;
    box.setText("WTF");
    box.setWindowTitle("It's an Error");
    box.setStandardButtons(QMessageBox::Ok);
    box.setStyleSheet("QLabel{min-width: 150px;}");
    box.exec();
}

void MessageDropper::DropThis(QString title, QString msg){
    QMessageBox box;
    box.setText(msg);
    box.setWindowTitle(title);
    box.setStandardButtons(QMessageBox::Ok);
    box.setStyleSheet("QLabel{min-width: 150px;}");
    box.exec();
}

bool MessageDropper::DropAsk(QString title, QString msg){
    if (QMessageBox::Yes == QMessageBox(QMessageBox::Information, title, msg, QMessageBox::Yes|QMessageBox::No).exec())
    {

        return true;
    }
    return false;

}

