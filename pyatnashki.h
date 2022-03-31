#ifndef PYATNASHKI_H
#define PYATNASHKI_H


class Pyatnashki
{
public:
    Pyatnashki();
    void start();
    void restart();
    int getX() const;
    int getY() const;
    void MoveNull(int i, int j);
    int getMoves() const;
    int getTile(int i, int j) const;
    bool gameIsWon() const;
private:
    int field[4][4];
    int copyfield[4][4];
    int solvedfield[4][4];
    int nullx, nully, moves;
};

#endif // PYATNASHKI_H
