#include "MultipleChoiceQuestion.h"

MultipleChoiceQuestion::MultipleChoiceQuestion(int qID, const string& qText, int pGain, int pLose, const vector<string>& ch, const string& rAns)
    :Question(qID, qText, pGain, pLose), choices(ch), rightAnswer(rAns)
{
}

string MultipleChoiceQuestion::GetTypeName() const
{
    return "MultipleChoice";
}

void MultipleChoiceQuestion::ShowQuestion()
{
    cout << "Q" << questionID << ": " << questionText << "\n";
    for (int i = 0; i < choices.size(); ++i) {
        cout << "  " << choices[i] << "\n";
    }
}

bool MultipleChoiceQuestion::ValidateAnswer(const std::string& userAnswer)
{
    return (userAnswer == rightAnswer);
}
