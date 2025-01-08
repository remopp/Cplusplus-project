#ifndef MATHQUESTION_H
#define MATHQUESTION_H
#include "Question.h"

class MathQuestion : public Question {
private:
    string rightAnswer;

public:
    MathQuestion(int qID,const string& qText, int pGain,int pLose,const string& rAns);
    virtual ~MathQuestion();
    string GetTypeName() const override;

    bool ValidateAnswer(const string& userAnswer) override;
};

#endif // !MATHQUESTION_H

