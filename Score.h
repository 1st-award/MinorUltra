//
// Created by Admin on 2022-05-26.
//

#ifndef MINORULTRA_SCORE_H
#define MINORULTRA_SCORE_H


class Score {
public:
    Score();
    void addScore(bool defusingSuccess);
    int getScore();

private:
    int score;
};


#endif //MINORULTRA_SCORE_H
