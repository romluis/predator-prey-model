#ifndef PREY_H
#define PREY_H
#include "creature.h"
#include <iostream>
using namespace std;
/*-------------------------------------------------------------
 *CLASS PREY
 *  Ineritts from base class creature
 *  A prey moves on grid randomly. Prey moves after predator
 *
 *
 *
 -------------------------------------------------------------*/

class prey: public creature
{
public:
    prey(int i, int j);
    virtual void Move(creature *thing[MAX_X][MAX_Y], char surroundings[MAX_X][MAX_Y]);            // moves to next available tile
    virtual void Reproduce(creature *thing[MAX_X][MAX_Y], char surroundings[MAX_X][MAX_Y]);       // creates new
    virtual void Eat();             // eats prey, reseting time since last meal
    virtual void NewAge();
    virtual bool IsDead();          // returns true if predator has died
    virtual int Type();             // returns int type
    virtual int GetXPos();          // returns the X pos of prey
    virtual int GetYPos();          // returns the Y pos of prrey
    virtual int GetAge();              // returns time on grid
    virtual bool HasMoved();
    int concieved();

private:

    int posX;               // X position of predator
    int posY;               // Y position of predator
    int type;               // returns type of creature'
    int numberOfBabies;      // returns numnber of births given by this creature
    int age;              // returns current time in grid
    int ticks;
    bool moved;
};
#endif // PREY_H
