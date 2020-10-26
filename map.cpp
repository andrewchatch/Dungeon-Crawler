//Andrew Hatch
//10-17-2020

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "map.h"
#include "functions.h"

using namespace std;

int map[20][20] = {0};

extern hero h1;

void createMap()
{

    map[0][0] = Entrance; //starting point

    map[20][20] = Exit; //end point

    srand(time(NULL));

    for(int i = 0; i < 110; i++)
    {
        int x = rand()%19;
        int y = rand()%19;
        if(map[x][y] == 0)
        {
            map[x][y] = (ITEM)rand()%4 + 2;
        }
    }
}

void displayMap()
{
    for(int i = 0; i < 20; i++)
    {
        for(int j = 0; j < 20; j++)
        {
            if(i == getCurrentXPosition(h1) && j == getCurrentYPosition(h1))
            {
                cout << setw(5) << "|_$_|";
            }
            else if(vectorContains(h1.places,i,j))
            {
                cout << setw(5) << "|_ _|";
            }
            else
            {
                cout << setw(5) << "|_?_|";
            }
        }
        cout << endl;
    }
}
