#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <algorithm>
#include <string.h>
#include <windows.h>
#include "draw.h"
using namespace std;

const vector <string> MONITOR = {
" _______________________\n"
"/   __________________  \\\n"
"|  /                  \\ |\n",//0
"| |                   | |\n"
"|  \\__________________/ |\n"
"|  <>         (|) (/)   |\n"
"\\______________________/\n"
"   \"--\"           \"--\"\n\n",

"| |                   | |\n"
"| |                   | |\n"
"| |                   | |\n",

"| |                   | |\n"
"| |     (>^.^)>       | |\n"
"| |                   | |\n",

"| |     HELLO ~       | |\n"
"| |                   | |\n"
"| |  I'M PROF.SHAUNA  | |\n",

"| |   I'M GOING TO    | |\n"
"| |                   | |\n"//5
"| | GUESS YOUR WORD :3| |\n",

"| | HOW MANY LETTERS  | |\n"
"| |    ARE THERE      | |\n"
"| |  IN YOUR WORD?    | |\n",

"| |                   | |\n"
"| |                   | |\n"
"| |  IS THERE ANY \"",

"| |                   | |\n"
"| |  WHERE IS IT?     | |\n"
"| |                   | |\n",

"| | I                 | |\n"
"| |   USE MY          | |\n"
"| |     HINT POWER!!  | |\n",

"| |  .  O             | |\n"
"| |    -              | |\n"//10
"| |       HMMM        | |\n",

"| |     >_<           | |\n"
"| |                   | |\n"
"| |         UH-OH     | |\n",

"| |  #   #            | |\n"
"| |   ^^^             | |\n"
"| |         *scarry*  | |\n",

"| |  =.=              | |\n"
"| |        ARE YOU    | |\n"
"| |      FOOLING ME?  | |\n",

"| |                   | |\n"
"| |   ^ ^             | |\n"
"| |           YAY     | |\n",

"| |    <3 <3          | |\n"
"| |                   | |\n"//15
"| |         YEAH      | |\n",

"| |                   | |\n"
"| |       EZ.         | |\n"
"| |                   | |\n",

"| |EZ    EZ    EZ     | |\n"
"| |   EZ    EZ    EZ  | |\n"
"| |EZ    EZ    EZ     | |\n",

"| |  {\\_/}            | |\n"
"| |  (O_O)            | |\n"
"| |                   | |\n"
};
const vector <string> plugAndScissors = {
"      ____\n"
" ____|    \\\n"
"(____|     `.____________________\n"
" ____|       _|__________________\n"
"(____|     .'\n"
"     |____/\n",
"                   0 0\n"
"                    X\n"
"                   / \\\n",
"                   0 0\n"
"                    X\n"
"      ____         / \\  \n"
" ____|    \\   \n"
"(____|     `._____________________\n"
" ____|       _|___________________\n"
"(____|     .'            \n"
"     |____/\n",
"\n                   0 0\n"
"      ____          X  \n"
" ____|    \\        / \\\n"
"(____|     `._____________________\n"
" ____|       _|___________________\n"
"(____|     .'            \n"
"     |____/\n",
"\n\n      ____         0 0  \n"
" ____|    \\         X\n"
"(____|     `.______/ \\____________\n"
" ____|       _|___________________\n"
"(____|     .'            \n"
"     |____/\n",
"\n\n\n      ____\n"
" ____|    \\        0 0\n"
"(____|     `._____  X   __________\n"
" ____|       _|___ / \\  __________\n"
"(____|     .'       *    \n"
"     |____/\n"
};
int *BGC;
void exportBadg(int& badGuessCount)
{
    BGC = &badGuessCount;
}

void renderMonitor(int i , string hiddenWord = "")
{
    clearScreen();
    cout << MONITOR[0] << MONITOR[i] << MONITOR[1];
    if (hiddenWord != "")
    {
        cout << endl << "Current word: " << hiddenWord << endl;
        cout << "Number of bad guess: " << *BGC << endl;
    }
}
void renderGMonitor(char c, string& hiddenWord)
{
    clearScreen();
    cout << MONITOR[0] << MONITOR[7] << c << "\" | |\n" << MONITOR[1];
    cout << endl << "Current word: " << hiddenWord << endl;
    cout << "Number of bad guess: " << *BGC << endl;
}

string starting()
{
    int i;
    for ( i = 3 ; i < 7 ; i++)
    {
        renderMonitor(i);
        Sleep(1000);
    }
    cout << "\nInput number of letters in your word: ";
    cin >> i;
    return string(i,'-');
}

int makeGuess(char c,string& hiddenWord)
{
    string ans = "";
    renderGMonitor(c, hiddenWord);
    cout << "Type yes or no: ";
    do
    {
        cin >> ans;
    } while (ans != "yes" && ans != "no");
    return ans == "yes" ? 1 : 0;
}
void resolveGuess(char guess, string& hiddenWord, int& badGuessCount, string& guessed)
{
    int correct, temp , i;
    if(makeGuess(guess, hiddenWord))
    {
        renderMonitor(rand() % 3 + 14, hiddenWord);
        cout << "So how many \"" << guess << "\" in the word? ";
        cin >> correct;
        for ( i = 0 ; i < correct ; i++ )
        {
            renderMonitor(8, hiddenWord);
            cout << "Type position of \"" << guess << "\":  ";
            cin >> temp;
            hiddenWord[temp-1] = guess;
        }
    } else
    {
        badGuessCount++;
        renderMonitor(rand() % 3 + 10, hiddenWord);
        Sleep(750);
    }
    guessed += guess;
}
char useHint(string& hiddenWord)
{
    renderMonitor(3, hiddenWord);
    char c;
    cout << "Gimme a hint plz: ";
    cin >> c;
    return c;
}
void printGameM3OverInfo(int win)
{
    int i, j;
    if (win)
    {
        renderMonitor(17);
        cout << "I win!\n";
        Sleep(3000);
    } else
    {
        renderMonitor(18);
        cout << "Im lose!\n";
        for (i = 5 ; i > 0 ; i-- )
        {
            clearScreen();
            for (j = 0 ; j < 5-i ; j++)
            {
                cout << endl;
            }
            cout <<plugAndScissors[1];
            for (j = 0 ; j < i ; j++ )
            {
                cout << endl;
            }
            cout <<plugAndScissors[0];
            Sleep(200);
        }
        for ( i = 2 ; i < 6 ; i++ )
        {
            clearScreen();
            cout <<"\n\n\n\n\n\n";
            cout <<plugAndScissors[i];
            Sleep(200);
        }
    }
}
