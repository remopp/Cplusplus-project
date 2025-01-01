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

public:

    oldquizhandler(const string& fname = "quizzes.txt");

    vector<string> split(const string& str, char delimiter);

    void saveQuiz(const string& quizName, const vector<int>& questionIDs);
    // Example line: "MyQuiz 0 1 2" => returns [0,1,2]
    vector<int> getQuestionIDs(const  string& quizName);
};









#endif // !OLDQUIZHANDLER_H

