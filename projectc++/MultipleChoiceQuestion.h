#ifndef MULTIPLECHOICEQUESTION_H
#define MULTIPLECHOICEQUESTION_H
#include "Question.h"
#include <vector>

class MultipleChoiceQuestion : public Question {
private:
    // We'll store each choice exactly as read: e.g. "A,santa"
    vector<string> choices;
    string rightAnswer; // e.g. "A", "B", "C", or "D"

public:
    MultipleChoiceQuestion(int qID,const string& qText,int pGain,int pLose,const vector<string>& ch,const string& rAns);
    virtual ~MultipleChoiceQuestion();
    string GetTypeName() const override;

    void ShowQuestion() override;

    bool ValidateAnswer(const string& userAnswer) override;
};




#endif // !MULTIPLECHOICEQUESTION_H
