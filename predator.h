#ifndef PREDATOR_H
#define PREDATOR_H
#include <iostream>
#include "creature.h"
using namespace std;
/*-------------------------------------------------------------
 *CLASS PREDATOR
 *  Inherits from base class creature
 *  A predator moves on grid randomly but towards a prey if near by
 *
 *
 *
 -------------------------------------------------------------*/

class predator: public creature
{
public:
    predator(int i, int j);
    virtual void Move(creature* thing[MAX_Y][MAX_Y],char surroundings[MAX_Y][MAX_Y]);            // moves to next available tile
    virtual void Reproduce(creature* thing[MAX_Y][MAX_Y],char surroundings[MAX_Y][MAX_Y]);       // creates new
    virtual void Eat();             // eats prey, reseting time since last meal
    virtual void NewAge();          // increments age on grid
    virtual bool IsDead();          // returns true if predator has died
    virtual int Type();             // returns int type
    virtual int GetXPos();          // returns X position
    virtual int GetYPos();          // returns Y position
    virtual int GetAge();
    int MealsHad();
    bool HasMoved();
    bool moved;

private:
    //creature* c[][];
    int posX;               // X position of predator
    int posY;               // Y position of predator
    int type;               // Int type of predator.(0 is prey, 1 is predator)
    int meals;              // number of eaten preys
    int age;              // amount of time on grid
    int ticks;
};

#endif // PREDATOR_H
