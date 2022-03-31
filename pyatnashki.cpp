#include "pyatnashki.h"
#include <QRandomGenerator>

Pyatnashki::Pyatnashki()
{
    start();
}

void Pyatnashki::start() {
    moves = 0;
    QRandomGenerator *randomx = QRandomGenerator::global();
    QRandomGenerator *randomy = QRandomGenerator::global();
    int tilenum = 1;
    do {
        for (auto i = 0; i < 4; i++){
            for (auto j = 0; j < 4; j++){
                field[i][j] = tilenum;
                solvedfield[i][j] = tilenum;
                tilenum++;
            }
        }
        solvedfield[3][3] = 0;
        field[3][3] = 0;
        nullx = 3;
        nully = 3;
        while(moves < 300){
            int y = randomy->bounded(-1,2);
            int x = randomx->bounded(-1,2);
            MoveNull(nully + y, nullx + x);
        }
        for (auto i = 0; i < 4; i++){
            for (auto j = 0; j < 4; j++){
                copyfield[i][j] = field[i][j];
            }
        }
    }
    while (gameIsWon());
    moves = 0;
}

void Pyatnashki::restart(){
    for (auto i = 0; i < 4; i++){
        for (auto j = 0; j < 4; j++){
            field[i][j] = copyfield[i][j];
            if (field[i][j] == 0){
                nully = i;
                nullx = j;
            }
        }
    }
    moves = 0;
}

int Pyatnashki::getX() const{
    return nullx;
}

int Pyatnashki::getY() const{
    return nully;
}

int Pyatnashki::getTile(int i, int j) const{
    return field[i][j];
}

void Pyatnashki::MoveNull(int i, int j){
    if (i > 3 || i < 0 || j < 0 || j > 3) return;
    if((abs(nullx-j) == 1 && abs(nully-i) == 0) || (abs(nullx-j) == 0 && abs(nully-i) == 1)){
        moves++;
        int num = field[i][j];
        field[i][j] = field[nully][nullx];
        field[nully][nullx] = num;
        nully = i;
        nullx = j;
    }
}

int Pyatnashki::getMoves() const {
    return moves;
}

bool Pyatnashki::gameIsWon() const {
    for (auto i = 0; i < 4; i++){
        for (auto j = 0; j < 4; j++){
            if (field[i][j] != solvedfield[i][j]){
                return false;
            }
        }
    }
    return true;
}
