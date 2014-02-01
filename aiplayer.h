#ifndef AIPLAYER_H
#define AIPLAYER_H

class aiPlayer
{
public:
    aiPlayer(int difficulty);
    aiPlayer();
    int getStupidMove(int column);
    int difficulty;

    int getDifficulty() const;
    void setDifficulty(int value);
    int getMove(int column);

};

#endif // AIPLAYER_H
