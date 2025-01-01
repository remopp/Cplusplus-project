#ifndef QUESTION_H
#define QUESTION_H
#include <string>
#include <iostream>
using namespace std;

class Question {
protected:
    int questionID;
    string questionText;
    int pointsToGain;
    int pointsToLose;

public:
    Question(int qID, const string& qText, int pGain, int pLose);

    virtual ~Question();

    int GetQuestionID() const;
    string GetQuestionText() const;
    int GetPointsToGain() const;
    int GetPointsToLose() const;

    virtual string GetTypeName() const = 0;

    virtual void ShowQuestion();

    virtual bool ValidateAnswer(const string& userAnswer) = 0;
};
#endif // !QUESTION_H