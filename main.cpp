#include <iostream>
#include "grid.h"

using namespace std;

int main()
{

    grid* world = new grid;

    int i = 0;
    while(i<400)
    {
        world->Update();
        i++;
    }
    return 0;
}





