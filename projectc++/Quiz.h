#ifndef QUIZ_H
#define QUIZ_H
#include "Question.h"
#include <vector>
using namespace std;
class Quiz {
private:
    vector<Question*> Questions;
    int points;

public:
    Quiz();

    void SetQuestions(const vector<Question*>& qs);

    int RunQuestions();
};
#endif // !QUIZ_H

