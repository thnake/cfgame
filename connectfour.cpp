#include "connectfour.h"
#include <QVector>
#include <QtCore>
#include <QObject>

/// <summary>
/// Konstruktor der Klasse ConnectFour.
/// Die Instanz bildet die Regeln des Spiels Vier Gewinnt ab.
/// </summary>
ConnectFour::ConnectFour() : QObject()
{

}

/// <summary>
/// Feld für den gewählten Schwierigkeitsgrad.
/// </summary>
int ConnectFour::getDifficulty() const
{
    return difficulty;
}

/// <summary>
/// Liefert die Anzahl der bisherigen Züge zurück
/// </summary>
int  ConnectFour::getMoves()
{
    return  moves;
}

/// <summary>
/// Liefert die Spielernummer des letzten Zuges zurück.
/// </summary>
int ConnectFour::getLastPlayer()
{
    int res = 0;
    switch (currentPlayer) {
    case 1:
        res = 2;
        break;
    case 2:
        res = 1;
        break;
    }
    return res;
}

/// <summary>
/// Liefert den Namen des zweiten Spielers
/// </summary>
QString ConnectFour::getName2() const
{
    return name2;
}


/// <summary>
/// Liefert den Namen des ersten Spielers
/// </summary>
QString ConnectFour::getName1() const
{
    return name1;
}

/// <summary>
/// Liefert die Spielernummer des Siegers zurück
/// </summary>
int ConnectFour::getWinner()
{
    return winner;
}


/// <summary>
/// Konstruktor der Klasse ConnectFour.
/// Die Instanz bildet die Regeln des Spiels Vier Gewinnt ab.
/// </summary>
/// <param name="x">Spalten</param>
/// <param name="y">Zeileen</param>
/// <param name="player1Name">Name des ersten Spielers</param>
/// <param name="player2Name">Name des zweiten Spielers</param>
/// <param name="difficultyLevel">Schwierigkeitsgrad</param>
/// <param name="startingPlayer">Nummer des beginnenden Spielers</param>
ConnectFour::ConnectFour(int x, int y, QString player1Name, QString player2Name, int difficultyLevel, int startingPlayer): QObject()
{
    fieldsx = x;
    fieldsy = y;
    currentPlayer = 1;
    name1 = player1Name;
    name2 = player2Name;
    history = "";

    currentPlayer = startingPlayer;
    this->startingPlayer = startingPlayer;

    difficulty = difficultyLevel;

    moves = 0;


    for(int i = 0; i < x; i++)
    {
        QVector<int> row;
        for(int j = 0; j < y; j++)
        {
            row.push_back(0);
        }
        board.push_back(row);
    }

    directions = QVector<QVector<int> >();

    QVector<int> *dir = new QVector<int>();
    dir->push_back(0);
    dir->push_back(1);
    directions.push_back(*dir);

    dir = new QVector<int>();
    dir->push_back(1);
    dir->push_back(1);
    directions.push_back(*dir);

    dir = new QVector<int>();
    dir->push_back(1);
    dir->push_back(0);
    directions.push_back(*dir);

    dir = new QVector<int>();
    dir->push_back(-1);
    dir->push_back(1);
    directions.push_back(*dir);

    winner = 0;

}

/// <summary>
/// Liefert eine Zeichenkette, die den Spielverlauf darstellt
/// </summary>
/// <retuns>Zeichenkette mit dem Spielverlauf</retuns>
QString ConnectFour::getGameState()
{
    QString state = "";
    for(int j = 0; j < fieldsy; j++)
    {
        for(int i = 0; i < fieldsx; i++)
        {
            state += QString::number(board[i][j]);
        }
    }
   return state;
}

/// <summary>
/// Liefert die aktuelle Spielernummer zurück.
/// </summary>
int ConnectFour::getCurrentPlayer()
{
    return currentPlayer;
}

/// <summary>
/// Prüft, ob ein Zug gültig ist, oder nicht. Wird von der KI im einfachen Modus benötigt.
/// <param name="x">Gewählte Spalte für den Zug</param>
/// </summary>
bool ConnectFour::checkMove(int x)
{
    bool result = false;
    for(int i = 0; i < fieldsy; i++)
    {
        if(board[x][i] == 0)
        {
            result = true;
            break;
        }
    }
    return result;
}

/// <summary>
/// Liefert den Spielverlauf in Form einer Zeichenkette zurück.
/// </summary>
QString ConnectFour::getHistory() const
{
    return history;
}


/// <summary>
/// Bereitet das Laden eines Spielverlaufs vor.
/// </summary>
void ConnectFour::setHistoryToLoad(QString hl)
{
    this->historyToLoad = hl;
}




// position ist die startposition
// u ist der einheitsvektor, in dessen richtung wir sammeln
// sign ist das vorzeichen
int ConnectFour::getStartingPlayer() const
{
    return startingPlayer;
}

/// <summary>
/// Läuft ausgehend von einer gewünschten Position eine gewünschte Richtung ab und sammelt die Punkte
/// </summary>
/// <param name="position">Startpunkt der Suche</param>
/// <param name="u">Richtungsvektor, zur Suche</param>
/// <param name="sign">Schrittweite. Zum Rückwärtslaufen einen negativen wert übergeben</param>
int ConnectFour::collectPointsInDirection(QVector<int> position, QVector<int> u, int scale)
{
    int sum = 0;

    while(position[0] < fieldsx
          && position[1] < fieldsy
          && position[0] > -1
          && position[1] > -1
          && board[position[0]][position[1]] == currentPlayer)
    {
        sum++;
        position[0] += u[0] * scale; // in richtung des Einheitsvektors u
        position[1] += u[1] * scale;
    }

    return sum;
}

/// <summary>
/// Liefert die noch zu ladende Spielehistorie zurück
/// </summary>
QString ConnectFour::getHistoryToLoad() const
{
    return historyToLoad;
}


/// <summary>
/// Verschiebt einen Punkt entlang der Linien (diagonal, senkrecht, horizontal)
/// und summiert die Spielerchips auf.
/// </summary>
/// <param name="x">x-Wert des Punktes</param>
/// <param name="y">y-Wert des Punktes</param>
bool ConnectFour::checkVictory(int x, int y)
{
    //int* point = new int[2];
    QVector<int> *pos = new QVector<int>();

    pos->push_back(x);
    pos->push_back(y);
    bool victory = false;

    // u ist unitvector
    QVector<int> u;
    foreach (u, directions) {

        int sum = 0;
        sum += collectPointsInDirection(*pos,u, 1);
        sum += collectPointsInDirection(*pos,u, -1);
        sum--; // der startpunkt wurde doppelt gezählt


        if(sum>3) // Siegesbedingung: vier gewinnt
        {
            victory = true;
            this->winner = currentPlayer;
            break;
        }
    }

    return victory;

}

/// <summary>
/// Prüft, ob ein unentschieden vorliegt
/// </summary>
bool ConnectFour::checkDraw()
{
    return winner == 0 && history.length() == fieldsx*fieldsy;
}


/// <summary>
/// liefert die Zeile zurück, in der der Stein gelandet ist.
/// Prüft, ob der Zug siegreich war. Prüfen mit getWinner()
/// </summary>
/// <returns>Zeilennummer, in der der Stein gelandet ist</returns>
int ConnectFour::setStone(int x)
{

    if(board[x][fieldsy-1] != 0)
    {
        return -1;
    }

    int result = -1;
    for(int i = 0; i < fieldsy; i++){
        if(board[x][i] == 0)
        {
            result = i;
            board[x][i] = currentPlayer;
            checkVictory(x,i);
            moves++;
            history += QString::number(x);
            qDebug() << history;
            break;
        }
    }

    if(currentPlayer == 1)
    {
        currentPlayer = 2;
    }
    else
    {
        currentPlayer = 1;
    }

    return result;
}



