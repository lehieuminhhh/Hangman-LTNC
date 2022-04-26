#ifndef _B0TCORE_H_
#define _B0TCORE_H_
#include <string>

void exportBadg(int& BadGuessCount);
void renderMonitor(int i, std::string hiddenWord = "");
void renderGMonitor(char c, std::string& hiddenWord);
std::string starting();
int makeGuess(char c, std::string& hiddenWord);
void resolveGuess(char guess, std::string& hiddenWord, int& badGuessCount, std::string& guessed);
char useHint(std::string& hiddenWord);
void printGameM3OverInfo(int win);
#endif // _B0TCORE_H_
