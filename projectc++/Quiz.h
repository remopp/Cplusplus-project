#ifndef QUIZ_H
#define QUIZ_H
#include "Question.h"
#include "player.h"
#include <vector>

class Quiz {
private:
    std::vector<Question*> Questions;
    Player player;
    int points;

public:
    Quiz();

    void SetPlayer(const Player& p);

    void SetQuestions(const vector<Question*>& qs);

    int RunQuestions();

    int GetFinalScore() const;
};
#endif // !QUIZ_H

