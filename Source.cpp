#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath> 
#include <stdio.h> 
#include <fstream>
#include<vector>
#include<map>
#include<string>
#include<unordered_map>
#include<algorithm>
using namespace std;

struct Quiz
{
public:

    unordered_map<int, vector<string>> problem; //int--difficult level; vector = list of questions
    unordered_map<int, vector<string>> answer;



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

    string userInput(int x, int y)
    {
        string letter = "null";
        if (x > 183 && x <= 308 && y > 501 && y <= 623) {
            //DO SOMETHING
            letter = "A";
        }
        else if (x > 488 && x <= 617 && y > 500 && y <= 623) {
            //DO SOMETHING
            letter = "B";
        }
        else if (x > 183 && x <= 308 && y > 645 && y <= 772) {
            //DO SOMETHING
            letter = "C";
        }
        else if (x > 488 && x <= 617 && y > 645 && y <= 772) {
            //DO SOMETHING
            letter = "D";
        }
        return letter;
    }
};



int main()
{
    srand(time(NULL));
    sf::RenderWindow window(sf::VideoMode(800, 800), "SFML works!");
    sf::RectangleShape shape(sf::Vector2f(800, 800));       
    shape.setFillColor(sf::Color(240, 248, 255));

    sf::Texture ATexture;
    ATexture.loadFromFile("images/A.png");
    sf::Sprite ASprite(ATexture);
   ASprite.setPosition(183,500);

   sf::Texture BTexture;
   BTexture.loadFromFile("images/B.png");
   sf::Sprite BSprite(BTexture);
   BSprite.setPosition(488, 500);

   sf::Texture CTexture;
   CTexture.loadFromFile("images/C.png");
   sf::Sprite CSprite(CTexture);
   CSprite.setPosition(183, 650);

   sf::Texture DTexture;
   DTexture.loadFromFile("images/D.png");
   sf::Sprite DSprite(DTexture);
   DSprite.setPosition(488, 650);


   sf::Texture BGTexture;
   BGTexture.loadFromFile("images/quizbowl.png");
   sf::Sprite BGSprite(BGTexture);
   BGSprite.setPosition(0, 0);

   sf::Texture SBTexture;  //start button
   SBTexture.loadFromFile("images/startButton.png");
   sf::Sprite SBSprite(SBTexture);
   SBSprite.setPosition(630, 680);

   sf::Texture AMTexture;  //Anime
   AMTexture.loadFromFile("images/Anime.png");
   sf::Sprite AMSprite(AMTexture);
   AMSprite.setPosition(0, 100); 


   sf::Texture CSTexture;  //CS
   CSTexture.loadFromFile("images/cs.png");
   sf::Sprite CSSprite(CSTexture);
   CSSprite.setPosition(0, 325);

   sf::Texture VGTexture;  //Video game
   VGTexture.loadFromFile("images/videoGame.png");
   sf::Sprite VGSprite(VGTexture);
   VGSprite.setPosition(0, 550);

   sf::Texture GOTexture;  //Game over
   GOTexture.loadFromFile("images/GameOver.png");
   sf::Sprite GOSprite(GOTexture);
   GOSprite.setPosition(0, 0);





   Quiz obj;
   int level = 1;
   int temp;
   sf::Font font;
   font.loadFromFile("arial.ttf");
   sf::Text text("",font);
   text.setCharacterSize(25);
   text.setStyle(sf::Text::Bold);
   text.setFillColor(sf::Color::Black);
   text.setPosition(20, 20);
   
   int correctAnswer = 0;;
   int count = 0;
   bool ifRight = true;
   int questionCount = 1;
   int wrongCount = 0;
   bool ifstart = false;
   int page = 0;
   int finalResult = 0;




   while (window.isOpen())
   {
       window.clear();
       window.draw(shape);

       
       if (page == 0) {

           window.draw(BGSprite);
           window.draw(SBSprite);
       }
       else if (page == 1) {
           sf::Text word("Choose Categories", font);
           word.setCharacterSize(40);
           word.setStyle(sf::Text::Bold);
           word.setFillColor(sf::Color::Black);
           word.setPosition(200, 20);
           window.draw(word);

           word.setString("Anime");
           word.setPosition(620, 175);
           window.draw(word);

           word.setString("CS");
           word.setPosition(620, 400);
           window.draw(word);

           word.setString("Game");
           word.setPosition(620, 625);
           window.draw(word);

           window.draw(AMSprite);
           window.draw(CSSprite);
           window.draw(VGSprite);
       }
       else if (page == 2)
       {
           window.draw(ASprite);
           window.draw(BSprite);
           window.draw(CSprite);
           window.draw(DSprite);
           window.draw(text);
       }
       else if (page == 3) {
           window.draw(GOSprite);
           string xx = "Score: " + to_string(finalResult);
           text.setString(xx);
           text.setPosition(380, 600);
           text.setFillColor(sf::Color::White);
           window.draw(text);
       }

       sf::Event event;
       while (window.pollEvent(event))
       {
           window.display();
           if (event.type == sf::Event::MouseButtonPressed) {
               if (event.key.code == sf::Mouse::Left) {
                   sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
                 
                   if (page == 0 && mousePosition.x > 630 && mousePosition.x <= 780 && mousePosition.y > 680 && mousePosition.y <= 780)
                   {
                       page = 1;

                   }
                   else if (page == 1 && mousePosition.x > 0 && mousePosition.x <= 600 && mousePosition.y > 100 && mousePosition.y <= 300)
                   {
                       page = 2;
                       obj.openFile("Anime_Question.csv");
                       //load anime;
                       temp = rand() % obj.problem[level].size(); // random 
                       text.setString(obj.problem[level][temp]);
                       text.setPosition(20, 20);
                       
                   }

                   else if (page == 1 && mousePosition.x > 0 && mousePosition.x <= 600 && mousePosition.y > 325 && mousePosition.y <= 525)
                   {
                       page = 2;
                       obj.openFile("CS_Question.csv");
                       //load CS
                       temp = rand() % obj.problem[level].size(); // random 
                       text.setString(obj.problem[level][temp]);
                       text.setPosition(20, 20);
                   }

                   else if (page == 1 && mousePosition.x > 0 && mousePosition.x <= 600 && mousePosition.y > 550 && mousePosition.y <= 750)
                   {
                       page = 2;
                       obj.openFile("Video_Game_Question.csv");
                       //load video game;
                       temp = rand() % obj.problem[level].size(); // random 
                       text.setString(obj.problem[level][temp]);
                       text.setPosition(20, 20);
                   }
                   
                   
                   window.display();
                   string answerChoice = obj.userInput(mousePosition.x, mousePosition.y);
                   if ((answerChoice == "A" || answerChoice == "B" || answerChoice == "C" || answerChoice == "D") && questionCount <= 10)
                   {
                       string tempAnswer = obj.answer[level][temp];


                       obj.problem[level].erase(obj.problem[level].begin() + temp);
                       obj.answer[level].erase(obj.answer[level].begin() + temp);

                       if (answerChoice == tempAnswer) {
                       //do something 
                           
                           correctAnswer++;
                           count++;
                           ifRight = true;
                           obj.printComment(ifRight);
                           finalResult = finalResult + level;
                           if (count == 2)
                           {
                               wrongCount = 0;
                               level++;
                               count = 0;
                           }
                       }
                       else if(answerChoice != tempAnswer){
                       //do something
                           wrongCount++;
                           ifRight = false;
                           obj.printComment(ifRight);
                           if (wrongCount == 4) {
                               level++;
                              count = 0;
                               wrongCount = 0;
                           }
                       }
                       questionCount++;

                       temp = rand() % obj.problem[level].size(); // random 
                       text.setString(obj.problem[level][temp]);
                       text.setPosition(20, 20);
                   }
               }
           }
           if (questionCount>10) {
               page = 3;

           }
            if (event.type == sf::Event::Closed)
                window.close();
        }
    }
    return 0;
}