#ifndef OLDQUIZHANDLER_H
#define OLDQUIZHANDLER_H
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>
using namespace std;
class oldquizhandler {
private:
    string filename;
    vector<string> split(const string& str, char delimiter);
public:

    oldquizhandler(const string& fname = "quizzes.txt");

    void saveQuiz(const string& quizName, const vector<int>& questionIDs);
    // Example line: "MyQuiz 0 1 2" => returns [0,1,2]
    vector<int> getQuestionIDs(const  string& quizName);
    void DisplayQuizNames();
};









#endif // !OLDQUIZHANDLER_H

