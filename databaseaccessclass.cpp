#include <QSqlError>
#include  <QSqlQuery>
#include <QDebug>
#include <QMapIterator>
#include <QString>
#include <QDataStream>
#include <QByteArray>

#include "QVariant.h"
#include "databaseaccessclass.h"
#include "qmessagebox.h"
#include "connectfour.h"



QString DataBaseAccessClass::getLastExecutedQuery( QSqlQuery query)
{
 QString str = query.lastQuery();
 QMapIterator<QString, QVariant> it(query.boundValues());
 while (it.hasNext())
 {
  it.next();
  str.replace(it.key(),it.value().toString());
 }
 return str;
}

DataBaseAccessClass::DataBaseAccessClass()
{
    connect();
}


bool DataBaseAccessClass::saveGame(ConnectFour *game)
{
    QByteArray ba;
    QDataStream s(&ba, QIODevice::WriteOnly);

    QSqlQuery *q = new QSqlQuery();
    q->prepare("delete from savegame;");
    q->exec();
    q->prepare("INSERT INTO game (name1,name2,winner,moves,heuristic,difficulty,game)"
               "VALUES (:name1, :name2, :winner, :moves, :heuristic, :difficulty,:game);");
    q->bindValue(":name1","'" + game->getName1() + "'");
    q->bindValue(":name2","'" + game->getName2() + "'");
    q->bindValue(":winner", game->getWinner());
    q->bindValue(":moves", game->getMoves());
    q->bindValue(":heuristic", game->getHeuristic());
    q->bindValue(":difficulty", game->getDifficulty());
    q->bindValue(":game", "'" + game->getGameState() + "'");


    if(!q->exec())
    {
        QMessageBox::critical(0, QObject::tr("Database Error"),  db.lastError().text());
        return false;
    }

    //qDebug() << game->getGameState();
    qDebug() << getLastExecutedQuery(*q);
    return true;
}

bool DataBaseAccessClass::connect()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setHostName("localhost");
    db.setDatabaseName("connectfour.sqlite");
    db.setUserName("user");
    db.setPassword("pass");

    if (!db.open()) {
        QMessageBox::critical(0, QObject::tr("Database Error"),  db.lastError().text());
        return false;
    }

    // tabelle erstellen

    QSqlQuery drop("DROP TABLE if exists highscore;");
    drop.exec();
    QSqlQuery qHighscore("CREATE TABLE IF NOT EXISTS "
                    " game "
                    "(hspk INTEGER PRIMARY KEY AUTOINCREMENT, name1 varchar(12), name2 varchar(12),"
                         " winner smallint, moves smallint, heuristic smallint, difficulty smallint, game varchar(100));");


    if (!qHighscore.exec())
    {
        qDebug() << "Table highscore not created";
    }


    return true;
}
