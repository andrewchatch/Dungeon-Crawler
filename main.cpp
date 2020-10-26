//Dungeon Crawl main
//Andrew Hatch
//10-12-2020
//Code Quality: The user interface is easy to follow
//Comments explain how the code works
//Multiple files:I used a functions file and a map file
//Overall functionality: I build in protections to keep the user from breaking the game
//Enums for directions and items
//Extern for hero and int map array
//Struct for the hero
//Random number generator to determine where the items are placed

#include <iostream>
#include <iomanip>
#include "map.h"
#include "functions.h"

using namespace std;

hero h1;

int main()
{
    cout << "Please enter your name" << endl;
    cin >> h1.name;
    h1.hitPoints = 50;
    h1.damage = 5;
    h1.xpos = 0;
    h1.ypos = 0;
    h1.state = alive;


    createMap();

    startGame();

}
