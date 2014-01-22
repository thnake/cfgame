#include <QString>
#include <QtSql/QSqlDatabase>
#include "connectfour.h"

#ifndef DATABASEACCESSCLASS_H
#define DATABASEACCESSCLASS_H

class DataBaseAccessClass
{
public:
    DataBaseAccessClass();
    bool connect();
    bool saveGame(ConnectFour *cf);
    QString getLastExecutedQuery( QSqlQuery query);

private:
    QSqlDatabase db;



};

#endif // DATABASEACCESSCLASS_H
