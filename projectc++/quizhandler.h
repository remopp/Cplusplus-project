#ifndef QUIZHANDLER_H
#define QUIZHANDLER_H
#include "Question.h"
#include "MultipleChoiceQuestion.h"
#include "MathQuestion.h"
#include "YesNoQuestion.h"
#include <fstream>
#include <sstream>      
class quizhandler {
private:
    string filename;
    vector<Question*> allQuestions;
    int maxQuestionID = -1; 
    vector<string> split(const string& str, char delimiter);
public:

    

    quizhandler(const string& fname = "questions.txt");

    ~quizhandler();

    void ReadQuestionsFromFile();

    const  vector<Question*>& GetAllQuestions() const;

    Question* getQuestionByID(int questionID);

    bool AddNewQuestionAndSave(char questionType, const  string& questionText, const  vector< string>& choices, const  string& rightAnswer, int pGain, int pLose);
};
#endif // !QUIZHANDLER_H
