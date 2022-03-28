#ifndef Petno_H
#define Petno_H
class Petno
{
public:
    void startGame();
    bool isFinished();
    bool exchange(int row, int column);
    int getItem(int i, int j) const;
    void move100();

private:
    int table [4][4];
    int empty_i = 3;
    int empty_j = 3;
};
#endif // Petno_H
