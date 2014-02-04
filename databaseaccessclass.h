#include <QString>
#include <QtSql/QSqlDatabase>
#include <QTableView>
#include "connectfour.h"

#ifndef DATABASEACCESSCLASS_H
#define DATABASEACCESSCLASS_H



/// <summary>
/// Klasse zum Speichern des Spielzustands in der Datenbank. Benutzt eine SQLite Datenbank.
/// </summary>
class DataBaseAccessClass
{
public:
    DataBaseAccessClass();
    bool connect();
    bool saveGame(ConnectFour *cf);
    QString getLastExecutedQuery( QSqlQuery query);
    void loadGames(QTableView* tv);

private:
    QSqlDatabase db;



};

#endif // DATABASEACCESSCLASS_H
