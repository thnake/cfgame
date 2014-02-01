#include "aiplayer.h"
#include <qglobal.h>
#include <QTime>


aiPlayer::aiPlayer()
{

}

int aiPlayer::getStupidMove(int columns)
{
    return qrand() % columns;
}
