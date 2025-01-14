#ifndef YESNOQUESTION_H
#define YESNOQUESTION_H
#include "Question.h"

class YesNoQuestion : public Question {
private:
    string correctAnswer;

public:
    YesNoQuestion(int qID, const string& qText, int pGain, int pLose, const string& rAns);
    virtual ~YesNoQuestion();

    string GetTypeName() const override;
    virtual void ShowQuestion() override;
    bool ValidateAnswer(const string& userAnswer) override;
};

#endif 