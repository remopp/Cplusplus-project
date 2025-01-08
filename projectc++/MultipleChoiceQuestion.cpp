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
    cout << "input: A, B, C or D" << endl;
    cout << "Q" << GetQuestionID() << ": " << GetQuestionText() << endl;
    cout << "  A: " << choices[0] << endl;
    cout << "  B: " << choices[1] << endl;
    cout << "  C: " << choices[2] << endl;
    cout << "  D: " << choices[3] << endl;

}

bool MultipleChoiceQuestion::ValidateAnswer(const string& userAnswer)
{
    
    string lowerUserAnswer = userAnswer;
    string lowerRightAnswer = rightAnswer;

    // Convert both strings to lowercase
    for (char& c : lowerUserAnswer) c = tolower(c);
    for (char& c : lowerRightAnswer) c = tolower(c);

    // Compare the lowercase strings
    return (lowerUserAnswer == lowerRightAnswer);
}
