#ifndef PLAYER_H
#define PLAYER_H

#include <string>
using namespace std;

class Player {
private:
    string name;
    string quizName;
    int score;

public:
    Player(const string& name = "", const string& quizName = "", int score = 0);
    virtual ~Player();
    string GetName() const;
    string GetQuizName() const;
    int GetScore() const;
    void SetScore(int newScore);
};
#endif // !PLAYER_H