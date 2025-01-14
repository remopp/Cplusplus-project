#include "MathQuestion.h"

MathQuestion::MathQuestion(int qID, const string& qText, int pGain, int pLose, const string& rAns)
    : Question(qID, qText, pGain, pLose), rightAnswer(rAns)
{
}

MathQuestion::~MathQuestion()
{
}

void MathQuestion::ShowQuestion()
{
    cout << Question::GetQuestionText() << endl;
    cout << "enter your answer: " << endl;
}

string MathQuestion::GetTypeName() const
{
    return "Math";
}

bool MathQuestion::ValidateAnswer(const string& userAnswer)
{
    return (userAnswer == rightAnswer);
}
