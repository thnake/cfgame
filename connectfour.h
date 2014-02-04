#include <QVector>
#include <QString>
#include <QObject>



#ifndef CONNECTFOUR_H
#define CONNECTFOUR_H

/// <summary>
/// VierGewinnt-Logik enthaltende Klasse. Hält den zustand des Spielbrettes und
/// kennt die Regeln des Spiels. Seine Felder werden in der SQLite DB persistiert.
/// </summary>
class ConnectFour : public QObject
{


private:
    int winner;
    QString name1;
    QString name2;
    int startingPlayer;
    bool fullscreen;
    int moves;
    int difficulty;
    int collectPointsInDirection(QVector<int> position, QVector<int> u, int sign);
    QString historyToLoad;


public:
    ConnectFour();
    ConnectFour(int x, int y, QString player1Name, QString player2Name, int difficultyLevel, int startingPlayer);
    int setStone(int x);
    bool checkVictory(int x, int y);
    int evaluateMove(int x, int y);
    bool checkDraw();
    QString getGameState();
    void setGameState(QString state);
    int getCurrentPlayer();
    bool checkMove(int x);

    QVector<QVector<int> > board;
    int fieldsx;
    int fieldsy;
    int currentPlayer;
    int necessaryPointsForWinning;
    QString history;
    QVector<QVector<int> > directions;

    QString getName1() const;
    QString getName2() const;
    bool getHeuristic() const;
    int getDifficulty() const;
    int getWinner();
    int  getMoves();
    int getLastPlayer();

    QString getHistory() const;
    QString getHistoryToLoad() const;
    void setHistoryToLoad(QString hl);
    int getStartingPlayer() const;



};

#endif // CONNECTFOUR_H
