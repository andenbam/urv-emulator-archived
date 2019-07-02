#ifndef SQLWORKER_H
#define SQLWORKER_H
#include <QDateTime>
#include <QtSql/qsqldatabase.h>
#include <QSqlTableModel>
class SQLWorker
{
public:

    SQLWorker(){}
    QString getDBName();
    bool tryConnectTo(QString& DBPath);
    int tryLogIn(QString un, QString p);
    QStringList getWorkersNames();
    QStringList getDoorsNames();
    QString     getDoorlockName(int id);
    QVector<int>    getDoorsIds();
    QVector<int>    getVisitsIds();
    int             getDoorsMaxId();
    QSqlTableModel* getDoorlocksTable();
    QSqlTableModel* getVisitsTable();
    void            openBase();
    QVector<int>    getWorkersIds();
    QVector<QStringList> getDoorlocks();
    bool            ifIdExists(int id, QString tableName, QString idColumnName);
    void            insertDoorlock(int id, QString doorname, int lock_type);
    void            updateDoorlock(int id, QString doorname, int lock_type);
    void            dropDoorlock(int id);

    int             getDoorlockType(int doorlockId);
    void addVisit(int workerId, int doorlockId, QDateTime dateTime);
    void dropVisit(int visitId);



private:
    QSqlDatabase getDB(QString DBPath);
    QString lastDBPath = "no";
};

#endif // SQLWORKER_H
