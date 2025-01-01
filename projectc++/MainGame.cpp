#include "MainGame.h"

bool MainGame::AskYesNo(const string& prompt)
{
    while (true) {
        cout << prompt;
        string answer;
        getline(cin, answer);
        for (auto& c : answer) c = tolower(c);

        if (answer == "yes" || answer == "y") {
            return true;
        }
        else if (answer == "no" || answer == "n") {
            return false;
        }
        else {
            cout << "Please enter 'yes' or 'no'.\n";
        }
    }
}

MainGame::MainGame()
    : qHandler("questions.txt"),oldQHandler("quizzes.txt"),leaderBoard("leaderboard.txt")
{
    // Load questions from file at startup
    qHandler.ReadQuestionsFromFile();
}

void MainGame::Start()
{
    while (true) {
        cout << "\n===== Main Menu =====\n";
        cout << "1. List All Questions (Debug)\n";
        cout << "2. Play an Existing Quiz\n";
        cout << "3. Show Leaderboard\n";
        cout << "4. Create a New Quiz (Random)\n";
        cout << "5. Add a New Question\n";
        cout << "6. Exit\n";
        cout << "Choice: ";

        int choice;
        cin >> choice;
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (choice == 1) {
            DebugListQuestions();
        }
        else if (choice == 2) {
            SelectQuiz();
        }
        else if (choice == 3) {
            LoadLeaderBoard();
        }
        else if (choice == 4) {
            CreateQuizRandom();
        }
        else if (choice == 5) {
            AddQuestion();
        }
        else {
            break;
        }
    }
}

void MainGame::DebugListQuestions()
{
    const auto& allQ = qHandler.GetAllQuestions();
    if (allQ.empty()) {
        cout << "No questions loaded.\n";
        return;
    }
    for (auto* q : allQ) {
        cout << "[ID=" << q->GetQuestionID()<< "] (" << q->GetTypeName() << ") " << q->GetQuestionText() << "\n";
    }
}

void MainGame::SelectQuiz()
{
    cout << "Enter quiz name: ";
    string quizName;
    getline(std::cin, quizName);

    vector<int> questionIDs = oldQHandler.getQuestionIDs(quizName);
    if (questionIDs.empty()) {
        cout << "No quiz found with that name or empty question list.\n";
        return;
    }

    Quiz quiz;
    cout << "Enter your name: ";
    string playerName;
    getline(std::cin, playerName);

    Player p(playerName, quizName);
    quiz.SetPlayer(p);

    vector<Question*> chosenQuestions;
    for (int id : questionIDs) {
        Question* q = qHandler.getQuestionByID(id);
        if (q) {
            chosenQuestions.push_back(q);
        }
        else {
            cout << "Warning: question ID " << id << " not found.\n";
        }
    }
    quiz.SetQuestions(chosenQuestions);

    int finalScore = quiz.RunQuestions();
    cout << "Your final score is: " << finalScore << "\n";

    p.SetScore(finalScore);
    leaderBoard.addPlayerEntry(p);
}

void MainGame::LoadLeaderBoard()
{
    cout << "Enter quiz name for leaderboard: ";
    string quizName;
    getline(cin, quizName);
    leaderBoard.DisplayLeaderBoard(quizName);
}

void MainGame::CreateQuizRandom()
{
    // 1) Ask total number of questions
    cout << "How many total questions do you want in this quiz? ";
    int totalWanted;
    cin >> totalWanted;
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    // 2) Ask which types
    bool wantYesNo = AskYesNo("Include Yes/No questions? (yes/no): ");
    bool wantMath = AskYesNo("Include Math questions? (yes/no): ");
    bool wantMC = AskYesNo("Include Multiple Choice questions? (yes/no): ");

    int typesChosen = 0;
    if (wantYesNo) typesChosen++;
    if (wantMath)  typesChosen++;
    if (wantMC)    typesChosen++;

    if (typesChosen == 0) {
        cout << "You must select at least one question type!\n";
        return;
    }
    if (totalWanted < typesChosen) {
        cout << "You asked for " << totalWanted << " total questions but selected " << typesChosen << " types. Each type must get at least 1 question!\n";
        return;
    }

    // 3) Gather question pools
    vector<Question*> yesNoPool;
    vector<Question*> mathPool;
    vector<Question*> mcPool;

    const auto& allQ = qHandler.GetAllQuestions();
    for (auto* q : allQ) {
        string t = q->GetTypeName();
        if (t == "YesNo") {
            yesNoPool.push_back(q);
        }
        else if (t == "Math") {
            mathPool.push_back(q);
        }
        else if (t == "MultipleChoice") {
            mcPool.push_back(q);
        }
    }

    // Which types actually have questions?
    bool hasYesNo = (yesNoPool.size() > 0 && wantYesNo);
    bool hasMath = (mathPool.size() > 0 && wantMath);
    bool hasMC = (mcPool.size() > 0 && wantMC);

    int actualTypes = 0;
    if (hasYesNo) actualTypes++;
    if (hasMath)  actualTypes++;
    if (hasMC)    actualTypes++;

    if (actualTypes == 0) {
        cout << "No available questions for the selected types. Aborting.\n";
        return;
    }
    if (totalWanted < actualTypes) {
        cout << "You asked for " << totalWanted << " but have " << actualTypes << " chosen types (need at least 1 each). Aborting.\n";
        return;
    }

    // 4) Distribute
    int leftover = totalWanted - actualTypes;
    int yesNoCount = 0, mathCount = 0, mcCount = 0;
    if (hasYesNo) yesNoCount = 1;
    if (hasMath)  mathCount = 1;
    if (hasMC)    mcCount = 1;

    default_random_engine rng(static_cast<unsigned>(std::time(nullptr)));
    for (int i = 0; i < leftover; i++) {
        vector<int> validSlots;
        if (hasYesNo) validSlots.push_back(0);
        if (hasMath)  validSlots.push_back(1);
        if (hasMC)    validSlots.push_back(2);

        if (!validSlots.empty()) {
            uniform_int_distribution<int> dist(0, (int)validSlots.size() - 1);
            int chosenIndex = validSlots[dist(rng)];
            if (chosenIndex == 0) yesNoCount++;
            else if (chosenIndex == 1) mathCount++;
            else if (chosenIndex == 2) mcCount++;
        }
    }

    // Shuffle and pick
    shuffle(yesNoPool.begin(), yesNoPool.end(), rng);
    shuffle(mathPool.begin(), mathPool.end(), rng);
    shuffle(mcPool.begin(), mcPool.end(), rng);

    if (yesNoCount > (int)yesNoPool.size()) yesNoCount = (int)yesNoPool.size();
    if (mathCount > (int)mathPool.size())  mathCount = (int)mathPool.size();
    if (mcCount > (int)mcPool.size())    mcCount = (int)mcPool.size();

    vector<int> selectedIDs;
    for (int i = 0; i < yesNoCount; i++) {
        selectedIDs.push_back(yesNoPool[i]->GetQuestionID());
    }
    for (int i = 0; i < mathCount; i++) {
        selectedIDs.push_back(mathPool[i]->GetQuestionID());
    }
    for (int i = 0; i < mcCount; i++) {
        selectedIDs.push_back(mcPool[i]->GetQuestionID());
    }

    if (selectedIDs.empty()) {
        cout << "No questions selected. Aborting.\n";
        return;
    }

    // 5) Prompt for quiz name, save
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    cout << "Enter a name for your new quiz: ";
    string quizName;
    getline(std::cin, quizName);

    oldQHandler.saveQuiz(quizName, selectedIDs);
    cout << "\nCreated quiz '" << quizName << "' with " << selectedIDs.size() << " question(s)!\n";
}

void MainGame::AddQuestion()
{
    cout << "\n=== Add a New Question to the Question Pool ===\n";
    cout << "Select question type:\n";
    cout << "  1) Yes/No\n";
    cout << "  2) Math\n";
    cout << "  3) Multiple Choice\n";
    int typeChoice;
    cin >> typeChoice;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    char qType;
    if (typeChoice == 1) qType = 'H';   // yes/no
    else if (typeChoice == 2) qType = 'M'; // math
    else if (typeChoice == 3) qType = 'O'; // multiple choice
    else {
        cout << "Invalid type.\n";
        return;
    }

    cout << "Enter the question text: ";
    string questionText;
    getline(cin, questionText);

    vector<string> choices;  // only used if multiple choice
    string rightAnswer;

    if (qType == 'O') {
        // multiple choice => prompt for 4 lines
        choices.resize(4);
        cout << "Enter option A (e.g. A,santa): ";
        getline(cin, choices[0]);
        cout << "Enter option B: ";
        getline(cin, choices[1]);
        cout << "Enter option C: ";
        getline(cin, choices[2]);
        cout << "Enter option D: ";
        getline(cin, choices[3]);

        cout << "Which option is correct? (A/B/C/D): ";
        getline(cin, rightAnswer);
    }
    else if (qType == 'M') {
        // math => single right answer (string/number)
        cout << "Enter the correct numeric/string answer: ";
        getline(cin, rightAnswer);
    }
    else if (qType == 'H') {
        // yes/no => e.g. "yes" or "no"
        cout << "Enter the correct answer (yes/no): ";
        getline(cin, rightAnswer);
    }

    cout << "Points to GAIN if correct: ";
    int pGain;
    cin >> pGain;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "Points to LOSE if incorrect: ";
    int pLose;
    cin >> pLose;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    bool success = qHandler.AddNewQuestionAndSave(qType, questionText,choices, rightAnswer,pGain, pLose);
    if (success) {
        cout << "Question added successfully!\n";
    }
    else {
        cout << "Failed to add question.\n";
    }
}

