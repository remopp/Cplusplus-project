#include "YesNoQuestion.h"

YesNoQuestion::YesNoQuestion(int qID, const string& qText, int pGain, int pLose, const std::string& rAns)
    :Question(qID, qText, pGain, pLose), correctAnswer(rAns)
{
}

string YesNoQuestion::GetTypeName() const
{
    return "YesNo";
}

bool YesNoQuestion::ValidateAnswer(const string& userAnswer)
{
    return (userAnswer == correctAnswer);
}
