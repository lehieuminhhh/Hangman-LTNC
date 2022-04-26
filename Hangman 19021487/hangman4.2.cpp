#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <vector>
#include <algorithm>
#include <conio.h>
#include <windows.h>
#include <string.h>
#include "utility.h"
#include "draw.h"

using namespace std;
struct Statistic
{
    int win = 0;
    int lose = 0;
};

char readAGuess(string& badGuess, int& hintLeft ,const string& guessedWord , const string& word)
{
    string guess;
    float time = 10;
    while (!_kbhit() && time>=0)
    {

        renderGame(badGuess);
        if (hintLeft > 0)
        {
            cout << "Type 'hint' to get a hint, you have " << hintLeft << " hint(s) left\n";
        }
        cout << "You have " << int(time+0.5) << " second(s) left for enter your next guess: ";
        time -= 0.5;
        Sleep(500);
    }
    if (time < 0)
    {
        renderGame(badGuess);
        fflush(stdin);
        return '*';
    }
    cin >> guess;
    if (guess == "hint" && hintLeft > 0)
    {
        int i;
        cout << "Type the letter you want to reveal: ";
        do
        {
            cin >> i;
        } while (guessedWord[i-1] != '-');
        guess = word[i-1];
        hintLeft--;
    }
    return guess[0];
}

void update(string& guessedWord, const string& word,const char& guess)
{
    int correct = 0;
    int n = guessedWord.length();
    for (int i = 0; i < n; i++)
    {
        if (word[i] == guess)
        {
            guessedWord[i] = guess;
            correct++;
        }
    }
    printPlane(guess, correct);
}

int main(int argc, char* argv[])
{
    string fileName;
    srand(time(0));
    struct Statistic stat;
    int gameMode;
    while (true)
    {
        gameMode = chooseGameMode(fileName);
        int badGuessCount = 0;
        const int MAX_BAD_GUESS = (gameMode == 1||gameMode == 3) ? 7 : 5;
        if (gameMode == 4)
        {
            cout << "\nGoodBye\n";
            return 0;
        }
        if (gameMode == 3)
        {
            #include "botCore.h"
            string hiddenWord = starting();
            int hintLeft = (int)(hiddenWord.length()/2);
            string guessed = "";
            char guess;
            exportBadg(badGuessCount);
            resolveGuess ('u', hiddenWord, badGuessCount, guessed);
            resolveGuess ('e', hiddenWord, badGuessCount, guessed);
            resolveGuess ('o', hiddenWord, badGuessCount, guessed);
            resolveGuess ('a', hiddenWord, badGuessCount, guessed);
            resolveGuess ('i', hiddenWord, badGuessCount, guessed);

            do
            {
                if (hintLeft > 0)
                {
                    guess = useHint(hiddenWord);
                    hintLeft--;
                } else
                {
                    do
                    {
                        guess = rand() % 26 + 97;
                    } while (contains(guessed, guess));
                }
                resolveGuess (guess, hiddenWord, badGuessCount, guessed);
            } while (badGuessCount < MAX_BAD_GUESS && (contains(hiddenWord,'-')));
            printGameM3OverInfo(badGuessCount<MAX_BAD_GUESS ? 1 : 0);
        } else
        {
            string word = chooseWord(fileName);
            fileName.erase(fileName.end()-4, fileName.end());
            string guessedWord = string(word.length(), '-');
            int hintLeft =(int)(word.length()/2);
            string badGuess;
            exportVariables(gameMode , badGuessCount, guessedWord, fileName);

            do
            {
                //renderGame(badGuess);
                char guess = readAGuess(badGuess, hintLeft , guessedWord , word);
                if (guess == '*')
                {
                    badGuessCount++;
                    printPlane(guess, -1);
                } else if (contains(word, guess))
                {
                    update(guessedWord, word, guess);
                } else
                {
                    badGuessCount++;
                    badGuess += guess;
                    badGuess += " ";
                    printPlane(guess, 0);
                }
            } while (badGuessCount < MAX_BAD_GUESS && guessedWord != word);

            printGameOverInfo(word);
        }
        if (badGuessCount < MAX_BAD_GUESS)
        {
            gameMode == 3 ? stat.lose ++ : stat.win++;
        } else
        {
            gameMode == 3 ? stat.win++ : stat.lose++;
        }
        fflush(stdin);
        cout << "\nYou played " << stat.win + stat.lose << " times, win " << stat.win << " - lose " <<stat.lose << endl;
        cout << "Do you want more (Y/N) ? ";
        string answer;
        //cin.ignore(1);
        getline(cin, answer);
        if (answer != "Y" && answer != "y")
        {
            cout << "\nGoodBye\n";
            break;
        }
    }
    return 0;
}
