#include "Question.h"

Question::Question(int qID, const string& qText, int pGain, int pLose)
    :questionID(qID), questionText(qText), pointsToGain(pGain), pointsToLose(pLose)
{
}

Question::~Question()
{
}

int Question::GetQuestionID() const
{
    return questionID;
}

string Question::GetQuestionText() const
{
    return questionText;
}

int Question::GetPointsToGain() const
{
    return pointsToGain;
}

int Question::GetPointsToLose() const
{
    return pointsToLose;
}

void Question::ShowQuestion()
{
    cout << "Q" << questionID << ": " << questionText << endl;
}

