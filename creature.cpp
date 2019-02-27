#include "creature.h"

creature::creature()
{
    posX = 0;
    posY = 0;
    type = 0;
    moved = false;
}

creature::~creature()
{

}

void creature::Move(creature* thing[MAX_X][MAX_Y], char surroundings[MAX_X][MAX_Y])
{

}

void creature::Eat()
{

}

void creature::NewAge()
{
    ticks++;
}

void creature::Reproduce(creature* thing [MAX_X][MAX_Y], char surroundings[MAX_X][MAX_Y])
{

}

bool creature::IsDead()
{
    return false;
}

int creature::Type()
{
    return 0;
}

int creature::GetXPos()
{

    return 0;
}

int creature::GetYPos()
{
    return 0;
}
int creature::GetAge()
{
    return ticks;
}

bool creature::HasMoved()
{
    return true;
}
int creature::MealsHad()
{
    return meals;
}
