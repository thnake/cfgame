#include "aiplayer.h"
#include <qglobal.h>
#include <QTime>


aiPlayer::aiPlayer(int difficulty)
{
    this->difficulty = difficulty;
}

aiPlayer::aiPlayer()
{
    difficulty = 1;
}

int aiPlayer::getStupidMove(int columns)
{
    qsrand(QTime::currentTime().msec());
    return qrand() % columns;
}
int aiPlayer::getDifficulty() const
{
    return difficulty;
}

void aiPlayer::setDifficulty(int value)
{
    difficulty = value;
}

int aiPlayer::getMove(int columns)
{
    int res = 0;
    switch (difficulty)
    {

        case 0:
            res = getStupidMove(columns);
            break;

        default:
            res = getStupidMove(columns);
            break;
    }
    return res;

}

