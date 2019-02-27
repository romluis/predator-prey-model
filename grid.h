#ifndef GRID_H
#define GRID_H
#include "creature.h"
#include "predator.h"
#include "prey.h"


/*------------------------------------------------------------------
 * CLASS GRID
 *  A Grid contains objects in grid positions
 *  Objects interact on grid and do not step out the grid boundereis
 *  Can template grid to hold other objects.
 *
 *  Will contain predator and preys in grid coordinate positions
 *  http://www.youtube.com/watch?v=fYhjI49DAOE
-------------------------------------------------------------------*/

class grid
{
public:
    grid();                       // Sets the x and y sizes of grid
    ~grid();                      // deletes all the ceatures
    void Update();                // resets the grid to update community
    void CheckSuroundings(int pos[2], char surrounding[MAX_X][MAX_Y]); // characters emediate surrounding
    void Refresh(char Pworld[MAX_X][MAX_Y]);                           // refreshes grid for display

private:

    char world[MAX_X][MAX_Y];       // char representation of world with creatures
    char surroundings[MAX_X][MAX_Y];// emediate character surroundings of a creature
    creature* thing[MAX_X][MAX_Y];  // creature triple pointer will create and delete creatures on grid
    int xmax;                       // length of grid
    int ymax;                       // width of grid

};

#endif // GRID_H
