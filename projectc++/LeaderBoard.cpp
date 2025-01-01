#include "LeaderBoard.h"

void LeaderBoard::readAllRecords()
{
    // clears vectores
    playerNames.clear();
    quizNames.clear();
    scores.clear();

    ifstream in(filename);
    if (!in.is_open()) {
        // If file doesn't exist or can't open, no problem:
        // we just stay empty.
        return;
    }

    string line;
    while (getline(in, line)) {
        if (line.empty()) continue;

        // parse "playerName,quizName,score"
         stringstream ss(line);
         string pName, qName, scStr;
        if ( getline(ss, pName, ',') &&
             getline(ss, qName, ',') &&
             getline(ss, scStr, ','))
        {
            // convert score from string to int
            int sc =  stoi(scStr);

            // store in vectors
            playerNames.push_back(pName);
            quizNames.push_back(qName);
            scores.push_back(sc);
        }
    }
    in.close();
}

void LeaderBoard::writeAllRecords()
{
    ofstream out(filename, ios::trunc);
    if (!out.is_open()) {
        cerr << "Could not open " << filename << " to rewrite the leaderboard.\n";
        return;
    }
    // each line: "playerName,quizName,score"
    for (size_t i = 0; i < playerNames.size(); i++) {
        out << playerNames[i] << "," << quizNames[i] << "," << scores[i] << "\n";
    }
    out.close();
}

LeaderBoard::LeaderBoard(const string& fname)
	:filename(fname)
{
}

void LeaderBoard::addPlayerEntry(const Player& player)
{
    // 1) Load existing data
    readAllRecords();

    bool found = false;
    for (size_t i = 0; i < playerNames.size(); i++) {
        // check if we have a match of playerName + quizName
        if (playerNames[i] == player.GetName() &&
            quizNames[i] == player.GetQuizName())
        {
            // found => check if new score is higher
            if (player.GetScore() > scores[i]) {
                scores[i] = player.GetScore();
                cout << "Updated high score for " << playerNames[i] << " on quiz " << quizNames[i] << " to " << scores[i] << "\n";
            }
            else {
                cout << "Existing high score is higher or equal. Not updating.\n";
            }
            found = true;
            break;
        }
    }

    // 2) If not found, we add a new line
    if (!found) {
        playerNames.push_back(player.GetName());
        quizNames.push_back(player.GetQuizName());
        scores.push_back(player.GetScore());
        cout << "New high score record added for " << player.GetName() << " on quiz " << player.GetQuizName() << " with score " << player.GetScore() << "\n";
    }

    // 3) Save everything back to file
    writeAllRecords();
}

void LeaderBoard::DisplayLeaderBoard(const  string& quizName)
{
    readAllRecords();
    bool foundAny = false;
    for (size_t i = 0; i < playerNames.size(); i++) {
        if (quizNames[i] == quizName) {
            foundAny = true;
            cout << "Player: " << playerNames[i] << ", High Score: " << scores[i] << ", Quiz: " << quizNames[i] << "\n";
        }
    }
    if (!foundAny) {
        cout << "No scores found for quiz \"" << quizName << "\".\n";
    }
}
