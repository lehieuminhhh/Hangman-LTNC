#include <iostream>
#include <windows.h>
#include <conio.h>
#include <cstdlib>
using namespace std;

int main()
{
    int t = 5;
    char c;
    while (!_kbhit() && t>=0)
    {
        system("CLS");
        cout << t <<endl;
        t--;
        Sleep(1000);
    }
    if (t >= 0)
    {
        cin >> c;
        cout << "you inputed: " << c;
    } else
    {
        cout << "time up";
    }
    return 0;
}
