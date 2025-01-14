#include "YesNoQuestion.h"

YesNoQuestion::YesNoQuestion(int qID, const string& qText, int pGain, int pLose, const std::string& rAns)
    :Question(qID, qText, pGain, pLose), correctAnswer(rAns)
{
}
YesNoQuestion::~YesNoQuestion()
{


}
string YesNoQuestion::GetTypeName() const
{
    return "YesNo";
}

void YesNoQuestion::ShowQuestion()
{
    cout << Question::GetQuestionText() << endl;
    cout << "input yes or no" << endl;

}


bool YesNoQuestion::ValidateAnswer(const string& userAnswer)
{
    string lowerUserAnswer = userAnswer;
    for (char& c : lowerUserAnswer) c = tolower(c); 
    if (lowerUserAnswer == "y" || lowerUserAnswer == "yes")
    {
        return ("yes" == correctAnswer);
    }
    else if(lowerUserAnswer == "n" || lowerUserAnswer == "no")
    {
        return ("no" == correctAnswer);
    }
    return(false);
}
