#ifndef __DRAW_H__
#define __DRAW_H__
#include <string>

std::string chooseTopic();
int chooseGameMode(std::string& fileName);
void exportVariables(int& gameMode, int& badGuessCount, std::string& guessedWord,  std::string& fileName);
std::string getHangPicture();
void clearScreen();
void printPlane(const char& guess , int correct);
void renderGame(std::string badGuess = "");
void printGameOverInfo(const std::string& word);

#endif // __DRAW_H__
