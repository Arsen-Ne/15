#include "Petno.h"
#include <QRandomGenerator>

void Petno::startGame()
{
    int number = 1;
    for (int i = 0; i < 4; i++) {
        for(int j = 0; j < 4; j++) {
            table[i][j] = number;
            number++;
        }
    }
    empty_i = 3;
    empty_j = 3;
    move100();
}

int Petno::getItem(int i, int j) const
{
    return table[i][j];
}

bool Petno::exchange(int row, int column)
{
    int tmp;
    if ((row == empty_i && abs(column-empty_j) == 1) || (column == empty_j && abs(row-empty_i) == 1)) {
        tmp = table[row][column];
        table[row][column] = table[empty_i][empty_j];
        table[empty_i][empty_j]=tmp;
        empty_i = row;
        empty_j = column;
        return true;
    }
    return false;
}

bool Petno::isFinished()
{
    int number = 1;
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
        {
           if (table[i][j] == number) {
               number++;
           } else {
               return false;
           }
         }
    return true;
}

void Petno::move100()
{
    int moves = 0;
    int num;
    int new_i;
    int new_j;

    QRandomGenerator *rnd = QRandomGenerator::global();

    while (moves < 100) {
        num = rnd->bounded(4);
        if(moves > 92) {
            num = 2;
            if(empty_i == 3) {
                num = 1;
                 if(empty_j == 3) {
                    num = 0;
                 }
            }
        }

        new_i = empty_i;
        new_j = empty_j;
        switch (num) {
        case 0: // move up
            new_i--;
            break;
        case 1: // move right
            new_j++;
            break;
        case 2: // move down
            new_i++;
            break;
        case 3: // move left
            new_j--;
            break;
        }
        if (new_i < 0  || new_i > 3 || new_j < 0 || new_j > 3) {
            continue;
        }
        if (exchange(new_i, new_j)) {
            moves++;
        }

    }
}
