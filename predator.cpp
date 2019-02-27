#include "predator.h"
#include <time.h>
#include <ctime>
#include <cstdlib>

predator::predator(int i, int j)
{
    posX = i;
    posY = j;
    type = 1;
    meals = 0;
    age = 0;
    ticks = 0;
    moved = false;
}

/*--------------------------------------------
 *  PREDATOR MOVE
 *      Takes in a creature pointer.
 *
 *
 *
 *
 --------------------------------------------*/


void predator::Move(creature *thing[MAX_Y][MAX_Y], char surroundings[MAX_Y][MAX_Y])// want to change surrunding to emmediate surrounding
{      
    ticks++;                                            // Increment ticks for predator(will reset if eats)
    NewAge();                                           // Predator has new age
    int XrandomCordinate[8];                            // array of possible x coord
    int YrandomCordinate[8];                            // array of possible y coord
    int count = 0;                                      // counter for possible moves


    for(int i=0; i<MAX_Y; i++)                          // First check if predator can eat
    {
        for(int j=0 ; j<MAX_Y; j++)
        {
                                                        // Check surroundings to see if predator can eat
            if(surroundings[i][j]=='$' && thing[i][j] != NULL && thing[i][j]->Type() != type) // a potential valid spot to eat
            {
                    Eat();                              // if so the increment meals eaten
                    ticks = 0;                          // reset ticks to zero since it ate
                    delete thing[i][j];                 // deletes the prey

                    thing[i][j] = thing[posX][posY];    // redirect predator to a new position
                    thing[posX][posY] = NULL;           // previous position is set to NULL and is thus available

                    posX = i;                           // predator has new x y cordinates
                    posY = j;
                    thing[posX][posY]->moved = true;    // set this predators move state to true

                    i = MAX_Y;                          // hard stop the loop
                    j = MAX_Y;                          // change the loop conditions so that it stops after eat or something like that
             }
          }
        }


                                                        // If predator did not eat, then it did not move
                                                        // check to see if not dead
    if(thing[posX][posY]->moved == false && IsDead()!= true) // since he didnt move before, then he didnt eat
    {
        for(int i=0; i<MAX_Y; i++)                         // if not starved then move the predator
        {
            for(int j=0 ; j<MAX_Y; j++)
            {

                if(surroundings[i][j] == '$' && thing[i][j] == NULL)// look for an available spot
                {
                    XrandomCordinate[count] = i;
                    YrandomCordinate[count] = j;
                    count ++;
                }
            }
        }
    }

    if(count!=0)
    {
        srand((unsigned)time(0));
        int x = XrandomCordinate[rand()%count];
        int y = YrandomCordinate[rand()%count];

        while(x == posX && y == posY)// check to see if random cordinates are not original coordinates
        {
            x = XrandomCordinate[rand()%count];
            y = YrandomCordinate[rand()%count];
        }

        thing[x][y] = thing[posX][posY];
        thing[posX][posY] = NULL;
        surroundings[posX][posY] = '$';

        posX = x;
        posY = y;
        thing[posX][posY]->moved = true;
    }


    if(age == 4 && IsDead() != true) // check to see if predator can breed
    {
        Reproduce(thing, surroundings);
        age = 0; //reset age to 0 again ;)
    }
}

void predator::Eat()
{
   meals++;
}

void predator::NewAge()
{
    age++;
}


void predator::Reproduce(creature *thing[MAX_Y][MAX_Y], char surroundings[MAX_Y][MAX_Y])
{
    for(int i=0; i<MAX_Y; i++)
    {
        for(int j=0 ; j<MAX_Y; j++)
        {
            if(surroundings[i][j]=='$' && thing[i][j] == NULL) // a potential valid spot to breed
            {
                thing[i][j] = new predator(i,j);    // give birth to the little shit
                i = MAX_Y;                             // hard stop the loop
                j = MAX_Y;
             }
          }
     }
}

bool predator::IsDead()
{
    if(ticks == 3)
    {
        return true;
    }
    else
    {
        return false;
    }
}
int predator::Type()
{
    return type;
}
int predator::GetXPos()
{
    return posX;
}

int predator::GetYPos()
{

    return posY;
}

int predator::GetAge()
{
    return age;
}
int predator::MealsHad()
{
    return meals;
}

bool predator::HasMoved()
{

    return moved;
}
