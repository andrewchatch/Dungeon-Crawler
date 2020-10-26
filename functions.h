//Andrew Hatch
//10-17-2020

#include <vector>

#ifndef FUNCTIONS_H
#define FUNCTIONS_H

enum STATUS {dead, alive};

struct hero
{
    std::string name;
    STATUS state;
    int hitPoints;
    int damage;
    int xpos;
    int ypos;
    std::vector<std::vector<int>> places = {{0,0}};
};

int getCurrentXPosition(hero);
int getCurrentYPosition(hero);
int assignDirection(std::string);
bool isValid(int);
bool vectorContains(std::vector<std::vector<int>>,int,int);
void battle(int);
void clearScreen();
void printSword();
void checkSpace();
void startGame();

#endif
