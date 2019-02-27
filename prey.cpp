#include "prey.h"
#include <time.h>
#include <ctime>
#include <cstdlib>


prey::prey(int i, int j)
{
  posX = i;
  posY = j;
  type = 0;
  numberOfBabies = 0;
  age = 0;
  ticks = 0;
  moved = false;
}
///*----------------------------------------------------------------------------------------------*
// * void prey::Move()                                                                            *
// *      Move function is responsible for placing the organism                                   *
// *       at a new grid location if the position is available(NULL),else it remains in place     *
// *      A prey moves one space that is adjacent to its current pos                              *
// *      If there is a predator in an adjacent space, It moves away from it                      *
// *      For every move, tick is implemented                                                     *
// *                                                                                              *
// *      Changes private vars:{ posX, posY, ticks }                                              *
// -----------------------------------------------------------------------------------------------*/

void prey::Move(creature *thing[MAX_X][MAX_Y], char surroundings[MAX_X][MAX_Y])
{
     NewAge();
    int XrandomCordinate[8];// array of possible x coord
    int YrandomCordinate[8];// array of possible y coord
    int count = 0;// counter for possible moves
    srand((unsigned)time(0));

    for(int i=0; i<MAX_X; i++) //initialize all positions to 'f' to represent an unavailable spot
    {
        for(int j=0 ; j<MAX_Y; j++)
        {
            if(surroundings[i][j]=='$' && thing[i][j]== NULL) // space is available
            {
                XrandomCordinate[count] = i;
                YrandomCordinate[count] = j;
                count ++;
            }
        }
    }
    if(count!=0)
    {
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

    if(age == 3)
    {
        Reproduce(thing,surroundings);
        age = 0;
    }
}
///*----------------------------------------------------------------------------------------------*
///*----------------------------------------------------------------------------------------------*
void prey::Eat()
{
    ticks = 0;
}
///*----------------------------------------------------------------------------------------------*
///*----------------------------------------------------------------------------------------------*
void prey::Reproduce(creature *thing[MAX_Y][MAX_Y], char surroundings[MAX_Y][MAX_Y])
{
    for(int i = 0; i<MAX_Y; i++)
    {
        for(int j = 0; j<MAX_Y; j++)
        {
            if(surroundings[i][j] == '$' && thing[i][j] == NULL)
            {
                thing[i][j] = new prey(i,j);
                i = MAX_Y;
                j = MAX_Y;
            }
        }
    }
    numberOfBabies++;
}
///*----------------------------------------------------------------------------------------------*
///*----------------------------------------------------------------------------------------------*
bool prey::IsDead()
{
    return false;
}
///*----------------------------------------------------------------------------------------------*
///*----------------------------------------------------------------------------------------------*
int prey::Type()
{
    //cout<<"PREY TYPE"<<endl;
    return type;
}
///*----------------------------------------------------------------------------------------------*
///*----------------------------------------------------------------------------------------------*
int prey::GetXPos()
{
    //cout<<"PREY XPOS"<<endl;
    return posX;
}
///*----------------------------------------------------------------------------------------------*
///*----------------------------------------------------------------------------------------------*
int prey::GetYPos()
{
    //cout<<"PREY YPOS"<<endl;
    return posY;
}
///*----------------------------------------------------------------------------------------------*
///*----------------------------------------------------------------------------------------------*
int prey::GetAge()
{
    //cout<<"PREY AGE"<<endl;
    return age;
}
///*----------------------------------------------------------------------------------------------*
///*----------------------------------------------------------------------------------------------*
void prey::NewAge()
{
    age++;
}
///*----------------------------------------------------------------------------------------------*
///*----------------------------------------------------------------------------------------------*
bool prey::HasMoved()
{
   return moved;
}
