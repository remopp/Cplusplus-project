#include "oldquizhandler.h"

oldquizhandler::oldquizhandler(const string& fname)
    :filename(fname)
{
}

vector<string> oldquizhandler::split(const string& str, char delimiter)
{
    vector<string> tokens;
    stringstream ss(str);
    string item;
    while (getline(ss, item, delimiter)) {
        tokens.push_back(item);
    }
    return tokens;
}

void oldquizhandler::saveQuiz(const string& quizName, const vector<int>& questionIDs)
{
    ofstream out(filename, ios::app);
    if (!out.is_open()) {
        cerr << "Could not open " << filename << " to save quiz.\n";
        return;
    }
    // Example line: "MyQuiz 0 1 2"
    out << "\n" << quizName;
    for (auto id : questionIDs) {
        out << " " << id;
    }
    out << "\n";
    out.close();
}

vector<int> oldquizhandler::getQuestionIDs(const string& quizName)
{
    vector<int> result;
    ifstream in(filename);
    if (!in.is_open()) {
        cerr << "Could not open " << filename << " to read quiz definitions.\n";
        return result;
    }

    string line;
    while (getline(in, line)) {
        if (line.empty()) continue;
        vector< string> parts = split(line, ' ');
        if (parts.size() < 2) continue;
        if (parts[0] == quizName) {
            for (size_t i = 1; i < parts.size(); i++) {
                result.push_back(stoi(parts[i]));
            }
            break;
        }
    }
    in.close();
    return result;
}

void oldquizhandler::DisplayQuizNames()
{
    ifstream in(filename);
    if (!in.is_open()) {
	cerr << "Could not open " << filename << " to read quiz definitions.\n";
	return;
	}
	string line;
    while (getline(in, line)) {
        //To make sure that the line is not empty
		if (line.empty()) continue;
		vector<string> parts = split(line, ' ');
        //to make sure that the quiz is not empty
		if (parts.size() < 2) continue;
		cout << parts[0] << endl;
	}
	in.close();
}
