#include "aiplayer.h"
#include <qglobal.h>
#include <QTime>

/// <summary>
/// Setzt den Schwierigkeitslevel. von 0 - 3
/// </summary>
aiPlayer::aiPlayer(int difficulty)
{
    this->difficulty = difficulty;
}

/// <summary>
/// Liefert eine Instanz auf eine aiPlayer Klasse
/// </summary>
aiPlayer::aiPlayer()
{
    difficulty = 1;
}


/// <summary>
/// Liefert einen zufällig generierten Zug zurück. Der Zug bechtet keine ungültigen Züge
/// </summary>
/// <param name="columns">Anzahl der Spalten, die zur Auswahl stehen</param>
/// <returns>Wert der gewählten Spalte</returns>
int aiPlayer::getStupidMove(int columns)
{
    qsrand(QTime::currentTime().msec());
    return qrand() % columns;
}

/// <summary>
/// Liefert den Schwierigkeitsgrad der KI
/// </summary>
int aiPlayer::getDifficulty() const
{
    return difficulty;
}

/// <summary>
/// Setzt den Schwierigkeitsgrad der KI
/// </summary>
void aiPlayer::setDifficulty(int value)
{
    difficulty = value;
}


/// <summary>
/// Führt einen Zug entsprechend des gewählten Schwierigskeitsgrades aus.
/// </summary>
/// <param name="columns">Anzahl der Spalten, die zur Verfügung stehen</param>
/// <returns>Gewählte Spalte</returns>
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

