#include "sqlworker.h"
#include <QtSql/qsqlquery.h>
#include <QVariant>
#include <QFile>
#include <QVector>

QString SQLWorker::getDBName(){

    return lastDBPath;
}

bool SQLWorker::tryConnectTo(QString& DBPath){

    if (DBPath != "") this->lastDBPath = DBPath;

    QSqlDatabase db = QSqlDatabase::database();
    if( db.isValid() ){
        db.setDatabaseName(DBPath);
        if (!QFile::exists(DBPath))
            return false;

        return true;
    }

    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(DBPath);
    if (!QFile::exists(DBPath))
        return false;
    bool a = db.open();

    db.close();
    if (!a) return a;
    return true;
}

QSqlDatabase SQLWorker::getDB(QString DBPath){
    QSqlDatabase db = QSqlDatabase::database();
    if( !db.isValid()){
        QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    }
    db.setDatabaseName(DBPath);
    db.open();
    return db;
}

int SQLWorker::tryLogIn(QString un, QString p){

    int res = 0;

    QSqlDatabase db = getDB(lastDBPath);
    QSqlQuery query;
    query.prepare("SELECT prior FROM users WHERE username = :un AND password = :pw");
    query.bindValue(":un", un);
    query.bindValue(":pw", p);
    query.exec();
    while(query.next()){
        res = query.value(0).toInt();
    }
    query.clear();
    db.close();

    return res;
}

QStringList SQLWorker::getDoorsNames(){
    QStringList vector;
    QSqlDatabase db = getDB(lastDBPath);
    QSqlQuery query;
    query.exec("SELECT door_name FROM doorlocks");
    while(query.next()){
        vector += query.value(0).toString();
    }
    query.clear();
    db.close();
    return vector;
}

QStringList SQLWorker::getWorkersNames(){
    QStringList vector;
    QSqlDatabase db = getDB(lastDBPath);
    QSqlQuery query;
    query.exec("SELECT name FROM workers");
    while(query.next()){
        vector += query.value(0).toString();
    }
    query.clear();
    db.close();
    return vector;
}

void SQLWorker::openBase(){
    QSqlDatabase db = getDB(lastDBPath);
}

QVector<QStringList> SQLWorker::getDoorlocks(){
    QVector<QStringList> vector;
    QSqlDatabase db = getDB(lastDBPath);
    QSqlQuery query;
    query.exec("SELECT * FROM doorlocks");
    while(query.next()){
        QStringList list;
        for (int i = 0; i < 3; i++)
            list.push_back(query.value(i).toString());

        vector.push_back(list);
    }
    query.clear();
    db.close();
    return vector;
}

int SQLWorker::getDoorsMaxId(){
    QSqlDatabase db = getDB(lastDBPath);
    QSqlQuery query;
    query.exec("SELECT MAX(doorlock_id) FROM doorlocks");
    if (!query.next())
        return 0;
    int a = query.value(0).toInt();
    query.clear();
    db.close();
    return a;
}

QSqlTableModel* SQLWorker::getDoorlocksTable(){
    QSqlTableModel *model = new QSqlTableModel;
    model->setTable("doorlocks");
    model->setEditStrategy(QSqlTableModel::OnFieldChange);
    model->select();
    model->setHeaderData(0, Qt::Horizontal,"doorlock_id");
    model->setHeaderData(1,Qt::Horizontal, "door_name");
    model->setHeaderData(2,Qt::Horizontal, "lock_type");
    return model;

}

QString SQLWorker::getDoorlockName(int id){
    QString name;
    QSqlDatabase db = getDB(lastDBPath);
    QSqlQuery query;
    query.exec("SELECT door_name FROM doorlocks WHERE doorlock_id = " + QString::number(id));
    query.next();
    name = query.value(0).toString();
    query.clear();
    db.close();
    return name;
}

QSqlTableModel* SQLWorker::getVisitsTable(){
    QSqlDatabase db = getDB(lastDBPath);
    QSqlTableModel *model = new QSqlTableModel;
    model->setTable("visits");
    model->setEditStrategy(QSqlTableModel::OnFieldChange);
    model->select();
    model->setHeaderData(0, Qt::Horizontal,"worker_id");
    model->setHeaderData(1,Qt::Horizontal, "doorlock_id");
    model->setHeaderData(2,Qt::Horizontal, "visit_time");
    model->setHeaderData(3,Qt::Horizontal, "visit_date");
    db.close();
    return model;
}

bool SQLWorker::ifIdExists(int id, QString tableName, QString idColumnName){
    QSqlDatabase db = getDB(lastDBPath);
    QSqlQuery query;
    query.exec("SELECT * FROM " + tableName + " WHERE " + idColumnName + " = " + QString::number(id));
    bool a = query.next();
    query.clear();
    db.close();
    return a;
}

void SQLWorker::insertDoorlock(int id, QString doorname, int lock_type){
    QSqlDatabase db = getDB(lastDBPath);
    QSqlQuery query;
    query.exec("INSERT INTO doorlocks VALUES( " + QString::number(id) + ", '" + doorname + "', " + QString::number(lock_type) + ")");
    query.next();
    query.clear();
    db.close();
}

void SQLWorker::updateDoorlock(int id, QString doorname, int lock_type){
    QSqlDatabase db = getDB(lastDBPath);
    QSqlQuery query;
    query.exec("UPDATE doorlocks SET door_name = '" + doorname + "' WHERE doorlock_id = " + QString::number(id));
    query.next();
    query.clear();
    query.exec("UPDATE doorlocks SET lock_type = " + QString::number(lock_type) + " WHERE doorlock_id = " + QString::number(id));
    query.next();
    query.clear();
    db.close();
}

void SQLWorker::dropDoorlock(int id){
    QSqlDatabase db = getDB(lastDBPath);
    QSqlQuery query;
    query.exec("DELETE FROM doorlocks WHERE doorlock_id = " + QString::number(id));
    query.next();
    query.clear();
    db.close();
}

QVector<int> SQLWorker::getWorkersIds(){
    QVector<int> vector;
    QSqlDatabase db = getDB(lastDBPath);
    QSqlQuery query;
    query.exec("SELECT worker_id FROM workers");
    while(query.next()){
        vector += query.value(0).toInt();
    }
    query.clear();
    db.close();
    return vector;
}

int SQLWorker::getDoorlockType(int doorlockId){

    QSqlDatabase db = getDB(lastDBPath);
    QSqlQuery query;
    query.exec("SELECT lock_type FROM doorlocks WHERE doorlock_id = " + QString::number(doorlockId));
    query.next();
    int n = query.value(0).toInt();
    query.clear();
    db.close();
    return n;
}

//secondary

QVector<int> SQLWorker::getVisitsIds(){
    QVector<int> vector;
    QSqlDatabase db = getDB(lastDBPath);
    QSqlQuery query;
    query.exec("SELECT visit_id FROM doorlocks");
    while(query.next()){
        vector += query.value(0).toInt();
    }
    query.clear();
    db.close();
    return vector;
}

void SQLWorker::addVisit(int workerId, int doorlockId, QDateTime dateTime){

    QSqlDatabase db = getDB(lastDBPath);
    QSqlQuery query;
    query.exec("INSERT INTO visits VALUES("
               + QString::number(workerId) + ", "
               + QString::number(doorlockId) + ", '"
               + dateTime.time().toString("hh:mm:ss.zzz")
               + "' , '"
               + dateTime.date().toString("yyyy-MM-dd")
               + "');");
    query.next();
    query.clear();
    db.close();
}

QVector<int> SQLWorker::getDoorsIds(){
    QVector<int> vector;
    QSqlDatabase db = getDB(lastDBPath);
    QSqlQuery query;
    query.exec("SELECT doorlock_id FROM doorlocks");
    while(query.next()){
        vector += query.value(0).toInt();
    }
    query.clear();
    db.close();
    return vector;
}
