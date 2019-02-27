#ifndef CREATURE_H
#define CREATURE_H
#include <iostream>

const int MAX_X = 30;           // Lenght size of grid
const int MAX_Y = 30;           // WIdth size of grid
/*----------------------------------------------------------------
 *CLASS CREATURE
 *  A Creature can be a particular type (predator or prey in this assignment)
 *  Every creatures type can move, eat, reproduce and die
 *  Thus we make the creature class as broad as possible, allowing it to be
 *      used by particular kinds of creatures on the grid.
 *
 *  CREATURE IS THERFORE A PARENT CLASS FOR A DERIVED CREATURE
 *
 *  Yes, every creature has a speecial way of carrying out functions like moving and eating
 *  Creature class does not care.
 *  Creature class only points to particular types of creatures.
 *      and by doing so, calls their kind of eat, move ... etc.
 *
 *  delete creature and set pos to NULL
 ----------------------------------------------------------------*/

using namespace std;
class creature
{
public:

    creature();                 // sets all creatures to NULL
    virtual ~creature();        // calls the destructor
    virtual void Move(creature* thing[MAX_X][MAX_Y],char surroundings[MAX_X][MAX_Y]);            // Moves creatures to available position
    virtual void Reproduce(creature* thing[MAX_X][MAX_Y],char surroundings[MAX_X][MAX_Y]);       // Alive creature creates a new creature
    virtual void Eat();         // Creature eats if food available
    virtual void NewAge();      // increments age on grid
    virtual bool IsDead();      // destroys the creature. Creature id no longer on grid
    virtual int Type();         // returns creature type (predator / prey for example)
    virtual int GetXPos();      // returns location of creature on X axis
    virtual int GetYPos();      // returns location of creature on Y axis
    virtual int GetAge();       // reuturns age on grid
    virtual bool HasMoved();    // tells if creature has moved
    virtual int MealsHad();
    bool moved;

private:
    int posX;                   // X cordinate of creature
    int posY;                   // Y coordinate of creature
    int ticks;                  // current time on grid
    int type;                   //type of creature on grid
    int age;                    //age of creature
    int meals;                  // ho many meals eaten
};

#endif // CREATURE_H











