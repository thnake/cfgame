#include <QSqlError>
#include  <QSqlQuery>
#include <QDebug>
#include <QMapIterator>
#include <QString>
#include <QDataStream>
#include <QByteArray>
#include <QSqlTableModel>

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
    q->prepare("INSERT INTO game (name1,name2,columns,rows,winner,moves,difficulty,game,fullscreen)"
               "VALUES (:name1, :name2, :columns, :rows, :winner, :moves, :difficulty,:game,:fullscreen);");
    q->bindValue(":name1","'" + game->getName1() + "'");
    q->bindValue(":name2","'" + game->getName2() + "'");
    q->bindValue(":columns", game->fieldsx);
    q->bindValue(":rows", game->fieldsy);
    q->bindValue(":winner", game->getWinner());
    q->bindValue(":moves", game->getMoves());
    q->bindValue(":difficulty", game->getDifficulty());
    q->bindValue(":game", "'" + game->getGameState() + "'");
    q->bindValue(":fullscreen", int(game->getFullscreen()));

    QSqlTableModel model();
    model.setTable("game");

    if(!q->exec())
    {
        qDebug() << db.lastError().text();
        return false;
    }

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
    QSqlQuery drop("DROP TABLE if exists game;");
    drop.exec();
    QSqlQuery qHighscore("CREATE TABLE IF NOT EXISTS "
                    " game "
                    "(hspk INTEGER PRIMARY KEY AUTOINCREMENT, name1 varchar(12), name2 varchar(12),columns smallint, rows smallint,"
                         " winner smallint, moves smallint, difficulty smallint, game varchar(100), fullscreen smallint);");

    if (!qHighscore.exec())
    {
        qDebug() << "Table highscore not created";
    }

    return true;
}
