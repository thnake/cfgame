#include <QVector>
#include <QString>
#include <QObject>



#ifndef CONNECTFOUR_H
#define CONNECTFOUR_H

class ConnectFour : QObject
{
private:
    ConnectFour();
    int winner;
    QString name1;
    QString name2;

    bool fullscreen;
    int moves;
    int difficulty;
    int collectPointsInDirection(QVector<int> position, QVector<int> u, int sign);

public:
    ConnectFour(int x, int y, QString player1Name, QString player2Name, int difficultyLevel, bool showFullscreen);
    int setStone(int x);
    bool checkVictory(int x, int y);
    QString getGameState();

    QVector<QVector<int> > board;
    int fieldsx;
    int fieldsy;
    int currentPlayer;
    QVector<QVector<int> > directions;

    QString getName1() const;
    QString getName2() const;
    bool getHeuristic() const;
    int getDifficulty() const;
    int getWinner();
    int  getMoves();



    bool getFullscreen() const;

};

#endif // CONNECTFOUR_H
