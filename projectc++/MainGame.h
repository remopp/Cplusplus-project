#ifndef MAINGAME_H
#define MAINGAME_H
#include "Question.h"
#include "quizhandler.h"
#include "oldquizhandler.h"
#include "LeaderBoard.h"
#include "Quiz.h"
#include <random>
#include <cstdlib>
class MainGame {
private:
    quizhandler qHandler;
    oldquizhandler oldQHandler;
    LeaderBoard leaderBoard;

    // Helper to read "yes/no" from user
    bool AskYesNo(const string& prompt);
    string validateinput(bool wantspace);
public:
    MainGame();

    void Start();

    // -----------------------------------------------------
    // 1. Debug: list all loaded questions
    // -----------------------------------------------------
    void DebugListQuestions();

    // -----------------------------------------------------
    // 2. Select and Play an Existing Quiz
    // -----------------------------------------------------
    void SelectQuiz();

    // -----------------------------------------------------
    // 3. Show Leaderboard
    // -----------------------------------------------------
    void LoadLeaderBoard();

    // -----------------------------------------------------
    // 4. CreateQuizRandom()
    //    Lets user choose how many questions total, toggles types,
    //    and picks them randomly from the question pool.
    // -----------------------------------------------------
    void CreateQuizRandom();

    // -----------------------------------------------------
    // 5. Add a New Question (interactively)
    // -----------------------------------------------------
    void AddQuestion();
};

#endif // !MAINGAME_H

