#include "connectfour.h"
#include <QVector>
#include <QtCore>
#include <QObject>

ConnectFour::ConnectFour() : QObject()
{

}

int ConnectFour::getDifficulty() const
{
    return difficulty;
}

int  ConnectFour::getMoves()
{
    return  moves;
}

QString ConnectFour::getName2() const
{
    return name2;
}

QString ConnectFour::getName1() const
{
    return name1;
}

int ConnectFour::getWinner()
{
    return winner;
}

ConnectFour::ConnectFour(int x, int y, QString player1Name, QString player2Name, int difficultyLevel): QObject()
{
    fieldsx = x;
    fieldsy = y;
    currentPlayer = 1;
    name1 = player1Name;
    name2 = player2Name;
    history = "";


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

void ConnectFour::setGameState(QString state){

    for(int j = 0; j < fieldsy; j++)
    {
        for(int i = 0; i < fieldsx; i++)
        {
            board[i][j] =  state[fieldsx * j + i].digitValue();
            if(board[i][j] != 0)
            {
                moves++;
            }
        }
    }
}

int ConnectFour::getCurrentPlayer()
{
    return currentPlayer;
}

bool ConnectFour::checkMove(int x)
{
    bool result = false;
    for(int i = 0; i < fieldsy; i++)
    {
        if(board[x][fieldsy] == 0)
        {
            result = true;
            break;
        }
    }
    return result;
}

QString ConnectFour::getHistory() const
{
    return history;
}


void ConnectFour::setHistoryToLoad(QString hl)
{
    this->historyToLoad = hl;
}




// position ist die startposition
// u ist der einheitsvektor, in dessen richtung wir sammeln
// sign ist das vorzeichen
int ConnectFour::collectPointsInDirection(QVector<int> position, QVector<int> u, int sign)
{
    int sum = 0;

    while(position[0] < fieldsx
          && position[1] < fieldsy
          && position[0] > -1
          && position[1] > -1
          && board[position[0]][position[1]] == currentPlayer)
    {
        sum++;
        position[0] += u[0] * sign; // in richtung des Einheitsvektors u
        position[1] += u[1] * sign;
    }

    return sum;
}
QString ConnectFour::getHistoryToLoad() const
{
    return historyToLoad;
}



// Verschiebt einen Punkt entlang der Linien (diagonal, senkrecht, horizontal)
// und summiert die Spielerchips auf.
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

bool ConnectFour::checkDraw()
{
    return winner == 0 && history.length() == fieldsx*fieldsy;
}


// liefert die Zeile zurück, in der der Stein gelandet ist.
// Prüft, ob der Zug siegreich war. Prüfen mit getWinner()
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



