#include "Quiz.h"

Quiz::Quiz()
	: points(0)
{
}

void Quiz::SetPlayer(const Player& p)
{
    player = p;
}

void Quiz::SetQuestions(const vector<Question*>& qs)
{
    Questions = qs;
}

int Quiz::RunQuestions()
{
    points = 0;
    for (size_t i = 0; i < Questions.size(); ++i) {
        Question* q = Questions[i];
        q->ShowQuestion();

        string userAnswer;
        getline(cin, userAnswer);

        bool correct = q->ValidateAnswer(userAnswer);
        if (correct) {
            points += q->GetPointsToGain();
            cout << "Correct! +" << q->GetPointsToGain() << " points\n";
        }
        else {
            points -= q->GetPointsToLose();
            cout << "Wrong! -" << q->GetPointsToLose() << " points\n";
        }
        cout << "Current points: " << points << "\n\n";
    }
    return points;
}

int Quiz::GetFinalScore() const
{
    return points;
}



