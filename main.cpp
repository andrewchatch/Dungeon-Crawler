//Dungeon Crawl main
//Andrew Hatch
//10-12-2020

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
