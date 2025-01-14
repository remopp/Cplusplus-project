#include "Quiz.h"

Quiz::Quiz()
	: points(0)
{
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
        cout << "question " << i+1 << " :";
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
        
        if (i < Questions.size() - 1) {
            cout << "Press Enter to continue to the next question...";
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Wait for Enter
            system("cls"); // Clear the terminal
        }
    }
    return points;
}




