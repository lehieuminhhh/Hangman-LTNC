#include <iostream>
#include <cstdlib>
#include <vector>
//#include <thread>
//#include <chrono>
//#include <unistd.h>
#include <windows.h>

using namespace std;

int *GameMode, *BadGuessCount;
string *FileName, *GuessedWord;
void clearScreen()
{
#ifdef _WIN32
    system("cls");
#elif __linux__
    system("clear");
#endif // _WIN32
}

string chooseTopic()
{
    char i;
    clearScreen();
    string s = {
"     _   _\n"
"    | | | | __ _ _ __   __ _ _ __ ___   __ _ _ __\n"
"    | |_| |/ _` | '_ \\ / _` | '_ ` _ \\ / _` | '_ \\\n"
"    |  _  | (_| | | | | (_| | | | | | | (_| | | | |\n"
"    |_| |_|\\__,_|_| |_|\\__, |_| |_| |_|\\__,_|_| |_|\n"
"                       |___/\n\n\n"};
    cout << s;
    cout << "1.Art\n2.Daily life\n3.Humanity\n4.Jobs and work\n5.Nature\n6.Relationship\n7.Status - level\n8.Telephone - letter - media\n9.Things around\n";
    cout << "Choose Topic you want to play by enter a number 1~9:\n\t(Any other key is back to mainscreen) ";
    cin >> i; fflush(stdin);
    switch(i)
    {
        case '1': return "Topic Art.txt";
        case '2': return "Topic Dailylife.txt";
        case '3': return "Topic Humanity.txt";
        case '4': return "Topic Jobs and work.txt";
        case '5': return "Topic Nature.txt";
        case '6': return "Topic Relationship.txt";
        case '7': return "Topic Status - level.txt";
        case '8': return "Topic Telephone - letter - media.txt";
        case '9': return "Topic Things around.txt";
        default: return "Turn Back";
    }
}

int chooseGameMode(string& fileName)
{
    char i;
    while (true)
    {
        string s = {
"     _   _\n"
"    | | | | __ _ _ __   __ _ _ __ ___   __ _ _ __\n"
"    | |_| |/ _` | '_ \\ / _` | '_ ` _ \\ / _` | '_ \\\n"
"    |  _  | (_| | | | | (_| | | | | | | (_| | | | |\n"
"    |_| |_|\\__,_|_| |_|\\__, |_| |_| |_|\\__,_|_| |_|\n"
"                       |___/\n\n\n"};
        clearScreen();
        cout << s ;
        cout << "1. Normal Mode (7 bad guess allowed)\n2. Hard Mode   (5 bad guess allowed)\n3. Reversed Role Mode\n4. Exit Game\n";
        cout << "Choose game mode by enter a valid key: ";
        cin >> i; fflush(stdin);
        switch(i)
        {
            case '1': case '2':
            {
                fileName = chooseTopic(); fflush(stdin);
                if (fileName == "Turn Back")
                {
                    continue;
                } else return i-48;
            }
            case '3': case '4': return i-48;
            default:
            {
                cout << "Please enter a valid key!";
                Sleep(2000);
                continue;
            }
        }
    }
}

void exportVariables (int& gameMode, int&badGuessCount, string& guessedWord, string& fileName)
{
    GameMode = &gameMode;
    BadGuessCount = &badGuessCount;
    GuessedWord = &guessedWord;
    FileName = &fileName;
}

string getHangPicture()
{
    string picture[] = {"",
"   ------------\n"
"   |           \n"
"   |           \n"
"   |           \n"
"   |           \n"
"   |           \n"
"   |           \n"
"   |           \n"
"   |           \n"
"-------        ",
"   ------------\n"
"   |          |\n"
"   |          O\n"
"   |           \n"
"   |           \n"
"   |           \n"
"   |           \n"
"   |           \n"
"   |           \n"
"-------        ",
"   ------------\n"
"   |          |\n"
"   |          O\n"
"   |          |\n"
"   |           \n"
"   |           \n"
"   |           \n"
"   |           \n"
"   |           \n"
"-------        ",
"   ------------\n"
"   |          |\n"
"   |          O\n"
"   |         /|\n"
"   |           \n"
"   |           \n"
"   |           \n"
"   |           \n"
"   |           \n"
"-------        ",
"   ------------\n"
"   |          |\n"
"   |          O\n"
"   |         /|\\\n"
"   |           \n"
"   |           \n"
"   |           \n"
"   |           \n"
"   |           \n"
"-------        ",
"   ------------\n"
"   |          |\n"
"   |          O\n"
"   |         /|\\\n"
"   |         / \n"
"   |           \n"
"   |           \n"
"   |           \n"
"   |           \n"
"-------        ",
"   ------------\n"
"   |          |\n"
"   |          O\n"
"   |         /|\\\n"
"   |         / \\\n"
"   |           \n"
"   |           \n"
"   |           \n"
"   |           \n"
"-------        ",

};
    if (*GameMode == 2)
    {
        return *BadGuessCount == 0 ? picture[0] : picture[*BadGuessCount+2];
    }
    return picture[*BadGuessCount];
}

const vector<string> plane = {
"                               _\n",
" _______________________    -=\\`\\\n",
"|                       |\\ ____\\_\\______\n",
"",
"|_______________________|   `~~~~~/ /~~`\n",
"                              -==/ /\n",
"                                '-'\n"};
void printPlane (const char& guess, int correct)
{
    int i , j , k ;
    for (i = 0 ; i < 25 ; i++ )
    {
        clearScreen();
        cout << "\n\n\n";
        for ( j = 0 ; j < 7 ; j++ )
        {
            for (k = 0 ; k < i ; k++ )
            {
                cout <<" ";
            }
            if(j != 3)
            {
                cout << plane[j];
            } else
            {
                if (correct == 1)
                {
                    cout <<"| THERE IS A LETTER " << guess <<"   |-=\\c`\"\"\"\"\"\"\" \"`)\n";
                } else if (correct == 0)
                {
                    cout <<"|          OOPS         |-=\\c`\"\"\"\"\"\"\" \"`)\n";
                } else if (correct == -1)
                {
                    cout <<"|      TIME UP!         |-=\\c`\"\"\"\"\"\"\" \"`)\n";
                } else
                {
                    cout <<"| THERE ARE " << correct << " LETTER " << guess << "  |-=\\c`\"\"\"\"\"\"\" \"`)\n";
                }
            }
        }
    }
}

void renderGame(string badGuess = "" )
{
    clearScreen();
    cout << *FileName << endl;
    cout << "Current guess = " << *GuessedWord << endl;
    cout << "You have made bad " << *BadGuessCount << " guess(es)"
         << (badGuess.empty() ? "" : ": ") << badGuess << endl
         << getHangPicture() << endl;
}

const vector<string> HANGED = {
"   ------------\n"
"   |         /\n"
"   |        O\n"
"   |       /|\\\n"
"   |       / \\\n"
"   |         \n"
"   |         \n"
"   |         \n"
"   |         \n"
"-------        ",
"   ------------\n"
"   |          |\n"
"   |          O\n"
"   |         /|\\\n"
"   |         / \\\n"
"   |           \n"
"   |           \n"
"   |           \n"
"   |           \n"
"-------        ",
"   ------------\n"
"   |           \\\n"
"   |            O\n"
"   |           /|\\\n"
"   |           / \\\n"
"   |             \n"
"   |             \n"
"   |             \n"
"   |             \n"
"-------        ",
"   ------------\n"
"   |          |\n"
"   |          O\n"
"   |         /|\\\n"
"   |         / \\\n"
"   |           \n"
"   |           \n"
"   |           \n"
"   |           \n"
"-------        "
};

const vector<string> SURVIVED = {
"   ------------\n"
"   |         |\n"
"   |         O\n"
"   |        /|\\\n"
"   |        / \\\n"
"   |         \n"
"   |         \n"
"   |         \n"
"   |         \n"
"-------        ",
"   ------------\n"
"   |         |\n"
"   |         * \n"
"   |        \\O/\n"
"   |         |\n"
"   |        / \\\n"
"   |         \n"
"   |         \n"
"   |         \n"
"-------        ",
"   ------------\n"
"   |         |\n"
"   |         *\n"
"   |          \n"
"   |        \\O/\n"
"   |         |\n"
"   |        / \\\n"
"   |         \n"
"   |         \n"
"-------        ",
"   ------------\n"
"   |         |\n"
"   |          \n"
"   |          \n"
"   |          \n"
"   |        \\O/\n"
"   |         |\n"
"   |        / \\\n"
"   |         \n"
"-------        ",
"   ------------\n"
"   |         |\n"
"   |          \n"
"   |          \n"
"   |          \n"
"   |          \n"
"   |        \\O/\n"
"   |         |\n"
"   |        / \\\n"
"-------        ",
"   ------------\n"
"   |         |\n"
"   |          \n"
"   |          \n"
"   |          \n"
"   |          \n"
"   |          \n"
"   |        \\O/\n"
"   |         |\n"
"-------     / \\\n",
"   ------------\n"
"   |         |\n"
"   |          \n"
"   |          \n"
"   |          \n"
"   |          \n"
"   |          \n"
"   |         O\n"
"   |        /|\\\n"
"-------     / \\\n",
"   ------------\n"
"   |         |\n"
"   |          \n"
"   |          \n"
"   |          \n"
"   |          \n"
"   |        \\O/\n"
"   |         |\n"
"   |        / \\\n"
"-------        "
};

void printGameOverInfo(const string& word)
{
    renderGame();
    if (*GuessedWord != word)
    {
        int n = 0;
        while (n<12)
        {
            clearScreen();
            cout << "Game Over!!! You are hanged" << endl
                 << "The correct word is " << word << endl;
            cout << HANGED[n % HANGED.size()];
            n++;
            //std::this_thread::sleep_for (std::chrono::milliseconds(100));
            Sleep(150);
        }
    } else
    {   int n = 0;
        while (n<16)
        {
            clearScreen();
            cout << "The correct word is " << word << endl;
            cout << "Congrats!!! You are free" << endl;
            n < 6 ? cout << SURVIVED[n] : n % 2 ? cout << SURVIVED[6] : cout << SURVIVED[7];
            n++;
            //std::this_thread::sleep_for (std::chrono::milliseconds(100));
            Sleep(150);
        }
    }
}
