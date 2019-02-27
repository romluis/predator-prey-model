#include "grid.h"
#include <time.h>
#include <ctime>
#include <cstdlib>
#include <iostream>
/*---------------------------------------------------
 *
 *
 *
 ----------------------------------------------------*/

grid::grid()
{
    srand((unsigned)time(0));
    xmax = MAX_X;                       // set x coordinates for grid
    ymax = MAX_Y;                       // set y coordinates for grid
    int randVar;

    for(int i = 0; i< xmax; i++)        // Initailizes all grid elemens to NULL
    {                                   // sets all grid representation to empty spaces
        for(int j = 0; j< ymax; j++)
        {
            thing[i][j] = NULL;
            world[i][j] = ' ';
        }
    }

    //---------TEST CREATURE POS---------------
    for(int i = 0; i<xmax; i++)
    {
        for(int j = 0; j<ymax; j++)
        {
            randVar = rand()%10;

            if(randVar == 1)
            {
                thing[i][j] = new prey(i,j);
            }
            else if(randVar == 2)
            {
                thing[i][j] = new predator(i,j);
            }
        }
    }

    //---------END TEST VALUES-------------

}

grid::~grid()
{

    for(int i = 0; i<xmax ; i++)
    {
        for(int j = 0; j<ymax ; j++)
        {
            if(thing[i][j]!=NULL)
                delete thing[i][j];
        }
    }
}


/*---------------------------------------------------
 *
 *
 *
 ----------------------------------------------------*/
void grid::Update()
{
    int pos[2], i , j;

    Refresh(world);                                         // Refreshes the world
    for(i = 0; i< xmax; i++)                                // for the rows of the grid
    {
        for(j = 0; j< ymax; j++)                            // and for the column of the grid
        {
            if(thing[i][j] != NULL && thing[i][j]->Type() == 1 && thing[i][j]->moved == false)  // check to see if the spot is not NULL and see if creature is prey
            {                                                                                   // Prey moves first
                pos[0]=i;                                                                       // set the current position of creature in an array
                pos[1]=j;
                CheckSuroundings(pos,surroundings);                         // let it look at at its immediate surroundings.
                thing[i][j]->Move(thing,surroundings);                                      //Pass the surroundings to the move function, thing eats in move func
                if(thing[i][j]!=NULL && thing[i][j]->IsDead() == true)                      // increment age of creature
                {
                    delete thing[i][j];
                    thing[i][j]= NULL;
                }
            }

        }
    }
    // move the prey next
    for(i = 0; i< xmax; i++)                                            // for the rows of the grid
    {
        for(j = 0; j< ymax; j++)                                        // and for the column of the grid
        {
            if(thing[i][j] != NULL && thing[i][j]->Type() == 0 && thing[i][j]->moved == false)
            {
                pos[0]=i;                                                                       // set the current position of creature in an array
                pos[1]=j;
                CheckSuroundings(pos,surroundings);                         // let it look at at its immediate surroundings.
                thing[i][j]->Move(thing,surroundings);                                          //Pass the surroundings to the move function, thing eats in move func
            }
        }
    }
    //Updates the grid characters emediately after move
    for(i = 0; i< xmax; i++)                                            // for the rows of the grid
    {
        for(j = 0; j< ymax; j++)                                        // and for the column of the grid
        {
            if(thing[i][j] == NULL)
            {
                world[i][j] = ' ';
            }
            else if(thing[i][j]!=NULL && thing[i][j]->Type() == 1)
            {
                world[i][j] = '@';
            }
            else if(thing[i][j]!=NULL && thing[i][j]->Type() == 0)
            {
                world[i][j] = '*';
            }
        }
    }
    // resets moved to false so that i can move again
    for(i = 0; i< xmax; i++)                            // for the rows of the grid
    {
        for(j = 0; j< ymax; j++)                        // and for the column of the grid
        {
            if(thing[i][j]!=NULL)
            thing[i][j]->moved = false;
        }
    }
}
/*---------------------------------------------------
 *
 *
 *
 ----------------------------------------------------*/

void grid::CheckSuroundings(int pos[2], char surrounding[MAX_X][MAX_Y])// only make 8 X 8 subgrid idiot
{
//    lets make surrounding private since its part of the grid
    for(int i=0; i<xmax; i++) //initialize all positions to 'f' to represent an unavailable spot
    {
        for(int j=0 ; j<ymax; j++)
        {
            surrounding[i][j]='f';// make surrounding private to grid
        }
    }

    //pos[0] is x coordinate, pos[1] is y coordinate
    //CHECK CORNER POSITIONS
    int x = pos[0];
    int y = pos[1];

    if(x == 0 && y == 0) //top left corner peice
    {
        surrounding[pos[0]+1][pos[1]] = '$';// set bottom pos true
        surrounding[pos[0]][pos[1]+1] = '$';// set right pos true
        surrounding[pos[0]+1][pos[1]+1] = '$'; //set diagonal true
    }

    else if(pos[0]== 0 && pos[1]== (ymax-1) )// top right corner piece
    {
        surrounding[pos[0]][pos[1]-1] = '$';// set left to true
        surrounding[pos[0]+1][pos[1]] = '$';// set bottom to true
        surrounding[pos[0]+1][pos[1]-1] = '$';// set bottom left
    }
    else if(pos[0]== (xmax-1) && pos[1]== 0)// bottom left corner
    {
        surrounding[pos[0]-1][pos[1]]= '$';// set top position to true
        surrounding[pos[0]][pos[1]+1]= '$';// set right pos to true
        surrounding[pos[0]-1][pos[1]+1] = '$';//set top right true
    }
    else if(pos[0]== (xmax-1) && pos[1]== (ymax-1))// bottom right corner
    {
        surrounding[pos[0]][pos[1]-1]= '$';// set left pos true
        surrounding[pos[0]-1][pos[1]]= '$';// set top pos true
        surrounding[pos[0]-1][pos[1]-1] = '$'; // set top left true
    }

    //CHECK EDGES
    else if(pos[0]==0) //top edge
    {
        surrounding[pos[0]][pos[1]+1]= '$';//right pos true
        surrounding[pos[0]][pos[1]-1]= '$';//left pos true
        surrounding[pos[0]+1][pos[1]]= '$';//down pos true

        surrounding[pos[0]+1][pos[1]-1] = '$';//bottom left pos true
        surrounding[pos[0]+1][pos[1]+1] = '$';//bottom right pos true

    }
    else if(pos[0]==(xmax)-1)// bottom edge
    {
        surrounding[pos[0]][pos[1]+1]= '$';//right pos true
        surrounding[pos[0]][pos[1]-1]= '$';//left pos true
        surrounding[pos[0]-1][pos[1]]= '$';//up pos true

        surrounding[pos[0]-1][pos[1]-1] = '$';//top left
        surrounding[pos[0]-1][pos[1]+1] = '$';//top right
    }
    else if(pos[1]==0)// left edge
    {
        surrounding[pos[0]+1][pos[1]]= '$';//down pos true
        surrounding[pos[0]-1][pos[1]]= '$';//up pos true
        surrounding[pos[0]][pos[1]+1]= '$';//right pos true

        surrounding[pos[0]-1][pos[1]+1] = '$';//top  right
        surrounding[pos[0]+1][pos[1]+1] = '$';//bottom right
    }
    else if(pos[1]==(ymax)-1)// right edge
    {
        surrounding[pos[0]+1][pos[1]]= '$';//down pos true
        surrounding[pos[0]-1][pos[1]]= '$';//up pos true
        surrounding[pos[0]][pos[1]-1]= '$';//left pos true

        surrounding[pos[0]+1][pos[1]-1] = '$';//bottom left
        surrounding[pos[0]-1][pos[1]-1] = '$';//top left
    }
    else// not at any corner or edge, all spots open
    {
        surrounding[pos[0]+1][pos[1]]= '$';//down pos true
        surrounding[pos[0]-1][pos[1]]= '$';//up pos true
        surrounding[pos[0]][pos[1]-1]= '$';//left pos true
        surrounding[pos[0]][pos[1]+1]= '$';//right pos true

        surrounding[pos[0]+1][pos[1]-1] = '$';//bottom left
        surrounding[pos[0]+1][pos[1]+1] = '$';//bottom right
        surrounding[pos[0]-1][pos[1]+1] = '$';//top rihgt
        surrounding[pos[0]-1][pos[1]-1] = '$';//top left
    }
}

/*---------------------------------------------------
 *
 *
 *
 ----------------------------------------------------*/

void grid::Refresh(char Pworld[MAX_X][MAX_Y])
{
    for(int i = 0; i< xmax; i++)
    {
        for(int j = 0; j< ymax; j++)
        {
            cout <<Pworld[i][j];
        }
        cout<<endl;
    }
    system("CLS");
}














