#ifndef YESNOQUESTION_H
#define YESNOQUESTION_H
#include "Question.h"

class YesNoQuestion : public Question {
private:
    string correctAnswer;

public:
    YesNoQuestion(int qID, const string& qText, int pGain, int pLose, const std::string& rAns);

    string GetTypeName() const override;

    bool ValidateAnswer(const std::string& userAnswer) override;
};

#endif 