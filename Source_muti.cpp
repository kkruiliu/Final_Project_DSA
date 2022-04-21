#include <iostream>
#include <cmath> 
#include <stdio.h> 
#include <fstream>
#include<vector>
#include<map>
#include<string>
#include<algorithm>

using namespace std;
struct Quiz
{
public:

    map<int, vector<string>> problem; //int--difficult level; vector = list of questions
    map<int, vector<string>> answer;
    
  

    // int- difficult level; vector = list of answer 
    void openFile(string name) {
        ifstream sample(name);
        string question;
        string answerChoice;
        string line;
 
        if (sample.is_open()) {

            string level;
            while (getline(sample, level, '#'))
            {
   
                string question_;
                string answerChios;
  
                getline(sample, question_, '#');
                getline(sample, answerChios, '#');
                
                problem[stoi(level)].push_back(question_);
                answer[stoi(level)].push_back(answerChios);

            }
        }
    }

    void printComment(bool ifRight)
    {
        string Right[10] = { "Good Job!", "Great Job!", "Amazing!", "Nice work!","Excellent","Wow!",
        "Congratulations!", "Outstanding work!", "Awesome!","Fantastic!" };
        string Wrong[5] = { "Nice try!", "You're Bad", "Wrong Answer", "OOPS", "Study more" };

        if (ifRight)
        {
            cout << Right[rand() % 10] << endl;
        }
        else
        {
            cout << Wrong[rand() % 5] << endl;
        }
    }
    void printResult(vector<vector<string>>& anime, vector<vector<string>>& CS, vector<vector<string>>& game)
    {
        sort(anime.begin(), anime.end());
        sort(CS.begin(), CS.end());
        sort(game.begin(), game.end());
        if (anime.size() != 0)
        cout << "Anime Scores:" << endl;
        for (int i = 0; i < anime.size(); i++)
        {
            for (int j = 0; j <anime[0].size(); j++)
            {
                if (j == 0)
                cout << anime[i][j] << " ";
                else
                cout << stoi(anime[i][j]) * 10 << "%" << " ";
            }
            cout << endl;
        }
        if (CS.size() != 0)
            cout << endl << "Computer Science Scores:" << endl;
        for (int i = 0; i < CS.size(); i++)
        {
            for (int j = 0; j < CS[0].size(); j++)
            {
                if (j == 0)
                    cout << CS[i][j] << " ";
                else
                    cout << stoi(CS[i][j]) * 10 << "%" << " ";
            }
            cout << endl;
        }
        if (game.size() != 0);
        cout << endl << "Video Game Scores:" << endl;
        for (int i = 0; i < game.size(); i++)
        {
            for (int j = 0; j < game[0].size(); j++)
            {
                if (j == 0)
                    cout << game[i][j] << " ";
                else
                    cout << stoi(game[i][j]) * 10 << "%" << " ";
            }
            cout << endl;
        }
    }


};


int main()
{
    vector<vector<string>> anime; // stored the scores
    vector<vector<string>> CS;
    vector<vector<string>> game;
    srand(time(NULL));
    Quiz obj;
  
    int numPlayer;
    cout << "Enter the number of players (>=1): " << endl;
    cin >> numPlayer;
    string playerName;
    //multi-player mode
    
    //getline(cin, numPlayer);
    
    for (int i = 0; i < numPlayer; i++)
    {
        cin.ignore();
        cout << "Enter the name of the current player: " << endl;
        getline(cin,playerName);
    
    //Math, UF facts, coding
    cout << "Choose the category: " << endl;
    cout << "1. Anime\n2. Computer Science\n3. Video Games" << endl;
    int userInput1;
    cin >> userInput1;
    while (userInput1 < 1 || userInput1 > 3)
    {
        cout << "Invalid Response" << endl;
        cout << "Choose the category: " << endl;
        cout << "1. Anime\n2. Computer Science\n3. Video Games" << endl;
        cin >> userInput1;
    }
    if (userInput1 == 1)
    {
        obj.openFile("Anime_Question.csv");

    }
    else if (userInput1 == 2)
    {
        obj.openFile("Computer_Science_question.csv");
    }
    else if (userInput1 == 3)
    {
        obj.openFile("game_question.csv");
    }
    int correctAnswer = 0;  // keep the total number of correct answers
    int count = 0;   // keep track streak of same difficulty;
    int level = 1;
    int temp;
    int wrongCount = 0;
    bool ifRight;
    int questionCount = 1;
    char userInput2;
    while (level <= 5 && questionCount <= 10) {

        while ((wrongCount == 4))
        {
            cout << "Would you like to quit this quiz? y for yes, n for no" << endl;
            cin >> userInput2;
            if (userInput2 == 'y')
            {
                cout << "See you again!";
                return -1;
            }
            else if (userInput2 == 'n') 
            {
                level++;
                count = 0;
                wrongCount = 0;
                break;
            }
            else {
                cout << "Invalid Response" << endl;
            }
        }
        temp = rand() % obj.problem[level].size(); // random 
        

        string input;
        cout << "Difficulty Level: " << level << endl;
        cout << "Question #: " << questionCount << endl;
        cout << obj.problem[level][temp] << endl;
        cin >> input;
        if (input == obj.answer[level][temp])            //have a correct answer
        {
            correctAnswer++;
            count++;
            ifRight = true;
            obj.printComment(ifRight);

            if (count == 2)
            {
                wrongCount = 0;
                level++;
                count = 0;
            }
        }
        else
        {
            ifRight = false;
            obj.printComment(ifRight);
            wrongCount++; 

        }
        questionCount++;
        obj.problem[level].erase(obj.problem[level].begin() + temp);
        obj.answer[level].erase(obj.answer[level].begin() + temp);
      
    }
    if (userInput1 == 1)
    {
        vector<string> temp;
        temp.push_back(playerName);
        temp.push_back(to_string(correctAnswer));
        anime.push_back(temp);
    }
    else if (userInput1 == 2)
    {
        vector<string> temp;
        temp.push_back(playerName);
        temp.push_back(to_string(correctAnswer));
        CS.push_back(temp);
    }
    else if (userInput1 == 3)
    {
        vector<string> temp;
        temp.push_back(playerName);
        temp.push_back(to_string(correctAnswer));
        game.push_back(temp);
    }
        cout << "\nFinal Result: " << correctAnswer << "/" << 10 << endl;
        cout << endl;
    }
    obj.printResult(anime, CS, game);
}

