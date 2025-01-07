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
    : qHandler("C://Users/moaj23/Source/Repos/remopp/Cplusplus-project/projectc++/questions.txt"),oldQHandler("C://Users/moaj23/Source/Repos/remopp/Cplusplus-project/projectc++/quizzes.txt"),leaderBoard("C://Users/moaj23/Source/Repos/remopp/Cplusplus-project/projectc++/leaderboard.txt")
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
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (choice == 1) {
            system("cls");
            DebugListQuestions();
        }
        else if (choice == 2) {
            system("cls");
            SelectQuiz();
        }
        else if (choice == 3) {
            system("cls");
            LoadLeaderBoard();
        }
        else if (choice == 4) {
            system("cls");
            CreateQuizRandom();
        }
        else if (choice == 5) {
            system("cls");
            AddQuestion();
        }
        else if(choice == 6) {
            break;
        }
        else if (cin.fail()){
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            system("cls");
            cout << "invalid input!!";
        }
        else
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            system("cls");
            cout << "invalid input!!";
        }
    }
}

void MainGame::DebugListQuestions()
{
    //auto is used if the variable type is unknown
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
    while (true)
    {
        cin >> totalWanted;
        if(cin.fail() || totalWanted <= 0)
        {
            //clear error
            cin.clear();
            //Ignores invalid input
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "invalid input!!";

        }
        else
        {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            break;
        }
    }


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
    //here the program warnes the user if there is no questions of a chosen type
    if (totalWanted < actualTypes) {
        cout << "You asked for " << totalWanted << " but have " << actualTypes << " chosen types (need at least 1 each). Aborting.\n";
        return;
    }

    // 4) Distribute

    //if the user wants more questions than the amout of types that they chose then the program will distrebdute the leftover amount wanted randomly bitween the types
    //for example user wants yesno questions and math questiosn and the amout of questions they want is 3 the program will chose one math and yesno question then the left over is 1 so the program will chose a random yesno or math question
    int leftover = totalWanted - actualTypes;
    int yesNoCount = 0, mathCount = 0, mcCount = 0;
    //here is ensures that each question type selected gets atleast one questions
    if (hasYesNo) yesNoCount = 1;
    if (hasMath)  mathCount = 1;
    if (hasMC)    mcCount = 1;

    //create the random number generator with the time to generate the seed so its random every time the user makes a quiz
    default_random_engine rng(static_cast<unsigned>(time(nullptr)));
    for (int i = 0; i < leftover; i++) {
        
        vector<int> validSlots;
        // here it addes all the posible types to the vector validSlots (0 = yesno, 1 = math, 2 = multiple choice)
        if (hasYesNo) validSlots.push_back(0);
        if (hasMath)  validSlots.push_back(1);
        if (hasMC)    validSlots.push_back(2);

        if (!validSlots.empty()) {
            //here it randomly selects a type from the posible type from the validSlots vector and addes one to the number of questions from that type (so that type will have one more question of that type)
            uniform_int_distribution<int> dist(0, (int)validSlots.size() - 1);
            int chosenIndex = validSlots[dist(rng)];
            if (chosenIndex == 0) yesNoCount++;
            else if (chosenIndex == 1) mathCount++;
            else if (chosenIndex == 2) mcCount++;
        }
    }

    // here the code shuffles the questions pool
    shuffle(yesNoPool.begin(), yesNoPool.end(), rng);
    shuffle(mathPool.begin(), mathPool.end(), rng);
    shuffle(mcPool.begin(), mcPool.end(), rng);

    //here the program prevents chosing more questions of a certin type than avalible
    if (yesNoCount > (int)yesNoPool.size()) yesNoCount = (int)yesNoPool.size();
    if (mathCount > (int)mathPool.size())  mathCount = (int)mathPool.size();
    if (mcCount > (int)mcPool.size())    mcCount = (int)mcPool.size();
    
    //here the code trise to substetut the missing questions from the code above with another question from a difrent chosen type
    int totalSelected = yesNoCount + mathCount + mcCount;
    while (totalSelected < totalWanted) {
        if (hasYesNo && yesNoCount < (int)yesNoPool.size()) {
            cout << "added extra yesno!!" << endl;
            yesNoCount++;
        }
        else if (hasMath && mathCount < (int)mathPool.size()) {
            cout << "added extra math!!" << endl;
            mathCount++;
        }
        else if (hasMC && mcCount < (int)mcPool.size()) {
            cout << "added extra MC!!" << endl;
            mcCount++;
        }
        else {
            break; // No more questions available
        }
        totalSelected = yesNoCount + mathCount + mcCount;
    }

    //here it just pushesback all the questions in to the total question pool of the quiz
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
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Enter a name for your new quiz: ";
    string quizName;
    bool validname = false;

    while (!validname) {
        getline(cin, quizName);

        // Check if the name contains any invalid characters
        bool hasInvalidChar = false;
        for (char c : quizName) {
            if (c == ' ' || c == ';') {
                hasInvalidChar = true;
                break;
            }
        }

        if (hasInvalidChar) {
            system("cls");
            cout << "Invalid name for the quiz! Do not use spaces or ';' in the name. Please try again: ";
        }
        else if (quizName.empty()) {
            system("cls");
            cout << "Quiz name cannot be empty. Please try again: ";
        }
        else {
            validname = true; // Name is valid
        }
    }

    oldQHandler.saveQuiz(quizName, selectedIDs);
    system("cls");
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
        system("cls");
        cout << "Question added successfully!\n";
    }
    else {
        system("cls");
        cout << "Failed to add question.\n";
    }
}

