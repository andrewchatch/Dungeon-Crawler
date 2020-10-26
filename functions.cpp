//Andrew Hatch
//10-17-2020

#include <iostream>
#include <iomanip>
#include <unistd.h>
#include "functions.h"
#include "map.h"

using namespace std;

extern int map[20][20];
extern hero h1;
bool hasSword = false;

enum direction {north, south, east, west};

void startGame()
{
    cout << "Welcome to Dungeon Crawler, " << h1.name << "!" << endl;
    cout << "Try to make it to the exit without dying. Good luck!" << endl;
    sleep(2);


    int dir = 0;
    std::string input = "";

    int numItrs = 0;

    while(h1.state == alive)
    {
        if(h1.xpos == 19 && h1.ypos == 19)
        {
            isValid(assignDirection(input));
            cout << "You survived the dungeon! Congratulations, " << h1.name << "!" << endl;
            exit(EXIT_FAILURE);
        }

        clearScreen();

        displayMap();


        cout << "Which way do you want to move? (Enter north, south, east, west, or exit)" << endl;
        cin >> input;

        dir = assignDirection(input);

        if(isValid(dir))
        {
            h1.places.insert(h1.places.begin(),{h1.xpos,h1.ypos});
        }

        checkSpace();

    }
}

int getCurrentXPosition(hero h1)
{
    int *ptr = &h1.xpos;
    return *ptr;
}

int getCurrentYPosition(hero h1)
{
    int *ptr = &h1.ypos;
    return *ptr;
}

int assignDirection(std::string input)
{
    int num = 6;
    if(input == "north")
    {
        num = north;
    }
    else if(input == "south")
    {
        num = south;
    }
    else if(input == "west")
    {
        num = west;
    }
    else if(input == "east")
    {
        num = east;
    }
    else if(input == "exit")
    {
        num = 5;
    }
    else
    {
        cout << "Please enter a valid direction (north, south, east, west, or exit)" << endl;
        cin >> input;
        isValid(assignDirection(input));
    }

    return num;
}

bool isValid(int dir)
{
    bool isVal = true;
    std::string input = "";
    switch(dir)
    {
        case north:
            if(h1.xpos > 0)
            {
                h1.xpos--;
                isVal = true;
            }
            else
            {
                cout <<"You can't move that way. Enter another direction" << endl;
                cin >> input;
                isValid(assignDirection(input));
            }
            break;
        case south:
            if(h1.xpos < 19)
            {
                h1.xpos++;
                isVal = true;
            }
            else
            {
                cout << "You can't move that way. Enter another direction" << endl;
                cin >> input;
                isValid(assignDirection(input));
            }
            break;
        case east:
            if(h1.ypos < 19)
            {
                h1.ypos++;
                isVal = true;
            }
            else
            {
                cout << "You can't move that way. Enter another direction" << endl;
                cin >> input;
                isValid(assignDirection(input));
            }
            break;
        case west:
            if(h1.ypos > 0)
            {
                h1.ypos--;
                isVal = true;
            }
            else
            {
                cout << "You can't move that way. Enter another direction" << endl;
                cin >> input;
                isValid(assignDirection(input));
            }
            break;
        case 5:
            cout << "Thanks for playing!" << endl;
            exit(EXIT_FAILURE);
            break;
        default:
            cout << "";

    }

    return isVal;
}

bool vectorContains(vector<vector<int>> places, int j, int k)
{
    bool contains = false;
    for(int i = 0; i < places.size(); i++)
    {
        if(places.at(i).at(0) == j && places.at(i).at(1) == k)
        {
            contains = true;
        }
    }

    return contains;
}

void checkSpace()
{
    std::string ans = "";

    if(map[h1.xpos][h1.ypos] == Potion)
    {
        cout << "Congratulations! You found a health potion. Do you want to drink it?" << endl;
        cin >> ans;

        if(ans == "yes")
        {
            h1.hitPoints+= 10;

            if(h1.hitPoints > 50)
            {
                h1.hitPoints = 50;
            }

            cout << "You have replenished your health! You now have " << h1.hitPoints << " hit points." << endl;
            sleep(2);

        }
        else if(ans == "no")
        {
            cout << "Okay, it's your choice! Hopefully you don't die." << endl;
            sleep(2);

        }
        else
        {
            checkSpace();
        }
    }
    if(map[h1.xpos][h1.ypos] == Sword)
    {
        if(!hasSword)
        {
            printSword();
            cout << "Congratulations! You found a sword. Do you want to pick it up?" << endl;
            cin >> ans;

            if(ans == "yes")
            {
                h1.damage+=10;

                cout << "Cool! Your attacks will now do more damage" << endl;
                sleep(2);

                hasSword = true;
            }
            else if(ans == "no")
            {
                cout << "Yeah, you're just moving through a creepy dungeon. Why would you want a sword?" << endl;
                sleep(2);

            }
            else
            {
                checkSpace();
            }
        }
        else
        {
            cout << "You found another sword!" << endl;
            sleep(2);
        }

    }
    if(map[h1.xpos][h1.ypos] == Trap)
    {
        int x = rand() % 3;
        if(x == 0)
        {
            cout << "You were attacked by goblins and lost 10 hit points!" << endl;
            sleep(2);

            h1.hitPoints -= 10;
        }
        else if(x == 1)
        {
            cout << "You were bitten by a snake and lost 25 hit points!" << endl;
            sleep(2);

            h1.hitPoints -= 25;
        }
        else if(x == 2)
        {
            cout << "Oh no! You fell in a trap and died. Sorry, " << h1.name << "!" << endl;
            exit(EXIT_FAILURE);
        }
    }
    if(map[h1.xpos][h1.ypos] == Monster)
    {
        int monsterHitPoints = rand()%30 +40;
        int damage = 10;

        cout << "You encountered a monster! Get ready to fight" << endl;
        sleep(2);

        battle(monsterHitPoints);
    }

    if(h1.hitPoints < 0)
    {
        h1.state = dead;
        cout << "Oh no! You died." << endl;
        exit(EXIT_FAILURE);
    }
}

void battle(int monsterHitPoints)
{
	while (h1.state == alive && monsterHitPoints > 0)
	{

		int hitValue = 0;

		hitValue = h1.damage;
		monsterHitPoints -=hitValue;
        cout << "You dealt " << hitValue << " points of damage to the monster" << endl;

		if (monsterHitPoints > 0)
		{
			hitValue = rand() % 5 + 1;
			h1.hitPoints -=hitValue;
            cout << "The monster dealt " << hitValue << " points of damage." << endl;
		}

        if(h1.hitPoints <= 0)
        {
            h1.state == dead;
            cout << "You were killed by the monster" << endl;
            sleep(2);
            exit(EXIT_FAILURE);
        }
        if(monsterHitPoints <= 0)
        {
            cout << "You defeated the monster!" << endl;
            sleep(2);
            break;
        }

        cout << "You have " << h1.hitPoints << " hit points remaining." << endl;
        cout << "The monster has " << monsterHitPoints << " hit points remaining" << endl;
        cout << endl;
        sleep(1);
	}

}

void printSword()
{
    cout << setw(44) << "/>_________________________________" << endl;
    cout << "[########[]_________________________________>" << endl;
    cout << setw(11) << "\\>" << endl;

//         />_________________________________
//[########[]_________________________________>
//         \>
}

void clearScreen()
{
    system("clear");
}
