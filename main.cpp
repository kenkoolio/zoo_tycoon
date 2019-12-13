
/*********************************************************************
** Program name: main.cpp
** Author: Huy Nguyen <nguyehu6@oregonstate.edu>
** Date: Apr 25, 2019 at 8:22 PM
** Description: Main is the driver function for the Zoo Tycoon Game.
 *              It instantiates the Zoo class, and runs the game via
 *              Zoo's start function.
*********************************************************************/


#include "Zoo.hpp"

int main()
{
    //Create zoo instance
    Zoo zoo;

    //Start the game
    zoo.start();

    return 0;
}