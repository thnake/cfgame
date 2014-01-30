#include <QVector>
#include <QString>
#include <QObject>



#ifndef CONNECTFOUR_H
#define CONNECTFOUR_H

class ConnectFour : public QObject
{


private:
    int winner;
    QString name1;
    QString name2;

    bool fullscreen;
    int moves;
    int difficulty;
    int collectPointsInDirection(QVector<int> position, QVector<int> u, int sign);
    QString historyToLoad;


public:
    ConnectFour();
    ConnectFour(int x, int y, QString player1Name, QString player2Name, int difficultyLevel);
    int setStone(int x);
    bool checkVictory(int x, int y);
    QString getGameState();
    void setGameState(QString state);
    int getCurrentPlayer();

    QVector<QVector<int> > board;
    int fieldsx;
    int fieldsy;
    int currentPlayer;
    QString history;
    QVector<QVector<int> > directions;

    QString getName1() const;
    QString getName2() const;
    bool getHeuristic() const;
    int getDifficulty() const;
    int getWinner();
    int  getMoves();

    QString getHistory() const;
    QString getHistoryToLoad() const;
     void setHistoryToLoad(QString hl);
};

#endif // CONNECTFOUR_H
