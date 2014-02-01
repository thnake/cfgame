#include "aiplayer.h"
#include <qglobal.h>
#include <QTime>


aiPlayer::aiPlayer()
{

}

int aiPlayer::getStupidMove(int column)
{
    return qrand() % column;
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

