
/*********************************************************************
** Program name: MyRandom.cpp
** Author: Huy Nguyen <nguyehu6@oregonstate.edu>
** Date: Apr 07, 2019 at 4:59 PM
** Description: Class implementation file for MyRandom class. MyRandom
 *              is a helper class with static functions that utilize
 *              srand() and rand() to generate random numbers. It can
 *              seed the number generator, as well as generate a
 *              random integer within a specified range.
*********************************************************************/


#include "MyRandom.hpp"

/********************************************************************
** Function: seed globally seeds random number generator with
 *           srand(). This is a static class function.
** Params:  unsigned int the_seed - unsigned int used to seed srand()
 *          default = time(0)
** Returns: void
*********************************************************************/
void MyRandom::seed(unsigned int the_seed)
{
    srand(the_seed);
}


/********************************************************************
** Function: randomInteger generates a random integer within provided
 *           range. This is a static class function.
** Params:  int range_start - lowest valid value in range of random
 *          integer.
 *          int range_end - highest valid value in range of random
 *          integer.
** Returns: int - the randomly chosen integer in specified range.
 * Citation: Equation from "Starting Out With C++ - Early Objects"
 *           9th ed. Gaddis, et al. Page 135
*********************************************************************/
int MyRandom::randomInteger(int range_start, int range_end)
{
    return (rand() % (range_end - range_start + 1)) + range_start;
}