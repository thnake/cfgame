#ifndef AIPLAYER_H
#define AIPLAYER_H

#include <connectfour.h>

/// <summary>
/// Computergegner für das Spiel. MinMax/Alpha-Beta-Implementierung ist unfertig.
/// möglich sind nur zufällige Züge.
/// </summary>
class aiPlayer
{
private:
    ConnectFour *cfgame;
    int difficulty;
    int necessaryPointsForWinning;
    int Horizon;
    int totalDepth;
    int boardHeight;
    int boardWidth;
public:
    aiPlayer();
    int Maximize(QVector<QVector<int> > &board, int turn, int &alpha, int &beta);
    int Minimize(QVector<QVector<int> > &board, int turn, int &alpha, int &beta);

    int getRandomMove(int colum);

    int PlayerIdentifier();
    int OtherPlayerIdentifier();
    int getDifficulty() const;
    void setDifficulty(int value);
    void setGame(ConnectFour *cfgame);
    int getMove(int column);



};

#endif // AIPLAYER_H
