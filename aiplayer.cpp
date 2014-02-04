#include "aiplayer.h"
#include <qglobal.h>
#include <QTime>

/// <summary>
/// Setzt den Schwierigkeitslevel. von 0 - 3
/// </summary>
aiPlayer::aiPlayer()
{
    qsrand(QTime::currentTime().msec());
    this->difficulty = 1;
    this->cfgame = NULL;
    necessaryPointsForWinning = 20;
    Horizon = 0;
    totalDepth = 0;
}


/// <summary>
/// Liefert einen zufällig generierten Zug zurück. Der Zug bechtet keine ungültigen Züge
/// </summary>
/// <param name="columns">Anzahl der Spalten, die zur Auswahl stehen</param>
/// <returns>Wert der gewählten Spalte</returns>
int aiPlayer::getRandomMove(int columns)
{
    return qrand() % columns;
}

int aiPlayer::PlayerIdentifier()
{
    return cfgame->getCurrentPlayer();
}

int aiPlayer::OtherPlayerIdentifier()
{
    return cfgame->getLastPlayer();
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

void aiPlayer::setGame(ConnectFour *cfgame)
{
    this->cfgame = cfgame;
    Horizon = cfgame->fieldsx * cfgame->fieldsy;

    boardHeight =  cfgame->fieldsy;
    boardWidth = cfgame->fieldsx;
}


/// <summary>
/// Führt einen Zug entsprechend des gewählten Schwierigskeitsgrades aus.
/// </summary>
/// <param name="columns">Anzahl der Spalten, die zur Verfügung stehen</param>
/// <returns>Gewählte Spalte</returns>
int aiPlayer::getMove(int columns)
{

   // QVector<QVector<int> > board = cfgame->board;

   // int alpha = INT_MIN;
   // int beta = INT_MAX;

   // return Maximize(cfgame->board,0, alpha, beta);


    int res = 0;
    switch (difficulty)
    {

        case 0:
            res = getRandomMove(columns);
            break;

        default:
            res = getRandomMove(columns);
            break;
    }
    return res;


}
/*

//alpha is the highest realistically achievable win.
//anything equal or below alpha is useless, as we wouldn't get a higher achievable win from it.
//alpha is therefore the lower border

//beta is the highest loss
//
int aiPlayer::Maximize(QVector<QVector<int> > &board, int turn, int &alpha, int &beta)
{
    if (turn > Horizon) //we go not further than the horizon. No winner here
    {
        return 0;
    }

    if (turn > totalDepth)
        totalDepth = turn;


    QVector<int> values(cfgame->fieldsx);

    for (int column = 0; column < cfgame->fieldsx; column++)
    {
        if (board[column][boardHeight - 1] != 0) //top column is full!
        {
            values[column] = INT_MIN; //assign a value that is lower than everything else, so it won't be chosen
            continue;
        }

        for(int row = boardHeight - 1; row >= 0; --row)
        {
            if(board[column][row] == 0)
            {
                //++totalCalls;
                //evaluate worth doesn't change the field at the according row/coumn, instead just checks its surroundings
                int worth = cfgame->evaluateMove(column, row); //calculate how much the node is worth
                if (worth >= necessaryPointsForWinning && turn > 0) //we have a winning, so this is a node (end state for the current tree)
                {
                    //values[column] = EvaluateWorth(row, column, PlayerIdentifier()); //calculate how much the node is worth
                    return worth;
                }
                else
                {
                    //we're not going to copy the board for further move, instead we do and afterwards undo it
                    board[column][row] = PlayerIdentifier();
                    int value = Minimize(board, turn+1, alpha, beta); //go to next level and minimize the value
                    board[column][row] = 0; //undo move

                    if (value > worth)
                        values[column] = value;
                    else
                        values[column] = worth; //heuristical value

                    if (values[column] > alpha) //new highest value
                        alpha = values[column]; //alpha = highest value
                }

                break;
            }

            //the upper level is maximizing, we are minimizing -> as soon as our calculated value is beneath the
            //parents lowest highest value, it won't choose this possibility anyway and therefore we can cut off
            //further calculation and just return this value as minimum (it could be even lesser than this minumum,
            //but it doesn't matter as its below the parents value in any case
            if (values[column] >= beta)
            {
                if (turn > 0) //don't cut below base node, because we want all the information to detect the best move
                    return values[column]; //cut off here
            }
        }

    }

    if (turn > 0)
        return alpha; //return highest value
    else
    {
        int highestValue = values[0];
        int column = 0;
        for (unsigned int i = 1; i < values.size(); i++)
        {
            if (values[i] > highestValue)
            {
                highestValue = values[i];
                column = i;
            }
        }
        return column;
    }
}


int aiPlayer::Minimize(QVector<QVector<int> > &board, int turn, int &alpha, int &beta)
{
    if (turn > Horizon) //we go not further than the horizon. No winner here
    {
        return 0;
    }

    if (turn > totalDepth)
        totalDepth = turn;

    for (int column = 0; column < boardWidth; column++)
    {
        if (board[column][boardHeight - 1] != 0) //top column is full!
        {
            continue;
        }

        for(int row = boardHeight - 1; row >= 0; --row)
        {
            if(board[row][column] == 0)
            {
                //++totalCalls;
                int worth = cfgame->evaluateMove(row, column);
                if (worth >= necessaryPointsForWinning) //we have a winning condition
                {
                    //values[column] =  -EvaluateWorth(row, column, OtherPlayerIdentifier()); //it's a leave node and it has the value -1, because the other Player wins with this constellation!
                    return -worth; //it's a leave node and it has the value -1, because the other Player wins with this constellation!
                }
                else
                {
                    //we're not going to copy the board for further move, instead we do and afterwards undo it
                    board[column][row] = OtherPlayerIdentifier();
                    int value = Maximize(board, turn+1, alpha, beta); //go to next level and minimize the value
                    board[column][row] = 0; //undo move

                    if (value < beta)
                        beta = value;
                    else if (worth < beta)
                        beta = worth;
                }
                break;
            }
        }

        //the upper level is maximizing, we are minimizing -> as soon as our calculated beta (minimum) is beneath the
        //parents lowest highest value, it won't choose this possibility anyway and therefore we can cut off
        //further calculation and just return this value as minimum (it could be even lesser than this minumum,
        //but it doesn't matter as its below the parents value in any case
        if (beta <= alpha)
            return beta; //cut off here
    }

    return beta; //return lowest value
}
*/
