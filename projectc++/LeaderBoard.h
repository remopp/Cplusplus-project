#ifndef LEADERBOARD_H
#define LEADERBOARD_H
#include "player.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>

class LeaderBoard {
private:
    string filename;
    
    vector<string> playerNames;
    vector<string> quizNames;
    vector<int> scores;
    //sets playerNames , quizNames and scores
    void readAllRecords();
    //overwrites the whole file with playerNames, quizNames and scores
    void writeAllRecords();
public:
    LeaderBoard(const string& fname = "leaderboard.txt");
    void addPlayerEntry(const Player& player);
    void DisplayLeaderBoard(const string& quizName);

};





#endif // !LEADERBOARD_H

