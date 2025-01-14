#include "quizhandler.h"

vector<string> quizhandler::split(const string& str, char delimiter)
{
    vector<string> tokens;
    stringstream ss(str);
    string item;
    while (getline(ss, item, delimiter)) {
        tokens.push_back(item);
    }
    return tokens;
}

quizhandler::quizhandler(const string& fname)
    :filename(fname)
{
}

//dynamic memory allocation
quizhandler::~quizhandler()
{
    for (size_t i = 0; i < allQuestions.size(); ++i) {
        delete allQuestions[i];
    }
    allQuestions.clear();
}

void quizhandler::ReadQuestionsFromFile()
{
    // opening file
    ifstream file(filename);
    if (!file.is_open()) {
         cerr << "Error: could not open " << filename << "\n";
        return;
    }

     string line;
    while ( getline(file, line)) {
        if (line.empty()) continue;
        //split the line read by the split singe ";"
         vector< string> tokens = split(line, ';');

        // For math or yes/no, we expect 6 tokens
        // For multiple-choice, we expect 10 tokens
        if (tokens.size() < 6) {
             cerr << "Warning: line doesn't have enough fields => " << line << "\n";
            continue;
        }
        //set question id
        int qID =  stoi(tokens[0]);
        if (qID > maxQuestionID) {
            maxQuestionID = qID;
        }

        //check for the type
         string qType = tokens[1]; // "O", "M" or "H"

        if (qType == "O") {
            // Multiple Choice => expect 10 tokens
            if (tokens.size() < 10) {
                 cerr << "Not enough fields for multiple-choice => " << line << "\n";
                continue;
            }
             string questionText = tokens[2];
             vector< string> choices{ tokens[3], tokens[4], tokens[5], tokens[6] };
             string rightAns = tokens[7];
            int pGain =  stoi(tokens[8]);
            int pLose =  stoi(tokens[9]);

            auto* mcq = new MultipleChoiceQuestion(qID, questionText, pGain, pLose, choices, rightAns);
            allQuestions.push_back(mcq);
        }
        else if (qType == "M") {
            // Math => 6 tokens
            if (tokens.size() < 6) {
                 cerr << "Not enough fields for math => " << line << "\n";
                continue;
            }
             string questionText = tokens[2];
             string rightAns = tokens[3];
            int pGain =  stoi(tokens[4]);
            int pLose =  stoi(tokens[5]);

            auto* mq = new MathQuestion(qID, questionText, pGain, pLose, rightAns);
            allQuestions.push_back(mq);
        }
        else if (qType == "H") {
            // Yes/No => 6 tokens
            if (tokens.size() < 6) {
                 cerr << "Not enough fields for yes/no => " << line << "\n";
                continue;
            }
             string questionText = tokens[2];
             string rightAns = tokens[3];
            int pGain =  stoi(tokens[4]);
            int pLose =  stoi(tokens[5]);

            auto* ynq = new YesNoQuestion(qID, questionText, pGain, pLose, rightAns);
            allQuestions.push_back(ynq);
        }
        else {
             cerr << "Unknown question type => " << qType << " in line: " << line << "\n";
        }
    }

    file.close();
}

const vector<Question*>& quizhandler::GetAllQuestions() const
{
    return allQuestions;
}

Question* quizhandler::getQuestionByID(int questionID)
{
    for (size_t i = 0; i < allQuestions.size(); ++i) {
        if (allQuestions[i]->GetQuestionID() == questionID) {
            return allQuestions[i];
        }
    }
    return nullptr;
}

bool quizhandler::AddNewQuestionAndSave(char questionType, const string& questionText, const vector<string>& choices, const string& rightAnswer, int pGain, int pLose)
{
    // Assign new ID
    int newID = ++maxQuestionID;

    // Building the line to append
    ofstream outFile(filename, ios::app);
    if (!outFile.is_open()) {
         cerr << "Error opening " << filename << " to append question.\n";
        return false;
    }

    if (questionType == 'O') {
        // Multiple choice => 10 tokens
        // ID;O;questionText;choiceA;choiceB;choiceC;choiceD;rightAns;pGain;pLose
        if (choices.size() < 4) {
             cerr << "Not enough MC choices provided.\n";
            outFile.close();
            return false;
        }
        outFile << endl << newID << ";" << "O" << ";" << questionText << ";" << "A: " + choices[0] << ";" << "B: " + choices[1] << ";" << "C: " + choices[2] << ";" << "D: " + choices[3] << ";" << rightAnswer << ";" << pGain << ";" << pLose;

        auto* mcq = new MultipleChoiceQuestion(newID, questionText, pGain, pLose, choices, rightAnswer);
        allQuestions.push_back(mcq);
    }
    else if (questionType == 'M') {
        // Math => 6 tokens
        // ID;M;questionText;rightAnswer;pGain;pLose
        outFile <<  endl << newID << ";" << "M" << ";" << questionText << ";" << rightAnswer << ";" << pGain << ";" << pLose;

        auto* mq = new MathQuestion(newID, questionText, pGain, pLose, rightAnswer);
        allQuestions.push_back(mq);
    }
    else if (questionType == 'H') {
        // Yes/No => 6 tokens
        // ID;H;questionText;rightAnswer;pGain;pLose
        outFile <<  endl << newID << ";" << "H" << ";" << questionText << ";" << rightAnswer << ";" << pGain << ";" << pLose;

        auto* ynq = new YesNoQuestion(newID, questionText, pGain, pLose, rightAnswer);
        allQuestions.push_back(ynq);
    }
    else {
         cerr << "Invalid question type.\n";
        outFile.close();
        return false;
    }

    outFile.close();
    return true;
}
